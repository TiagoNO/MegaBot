#include "EpsilonGreedyOnce.h"
#include <BWAPI.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include "../utils/tinyxml2.h"
#include "../utils/Logging.h"
#include "MetaStrategy.h"

using namespace tinyxml2;
using namespace BWAPI;

EpsilonGreedyOnce::EpsilonGreedyOnce(void) : MetaStrategy() {
	name = "Epsilon-greedy (once)";
	srand(time(NULL));
}


EpsilonGreedyOnce::~EpsilonGreedyOnce(void) {
}

/**
 * Performs epsilon-greedy selection of strategy
 */ 
void EpsilonGreedyOnce::onStart() {

	boost::random::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    boost::random::uniform_real_distribution<> dist(0.0, 1.0);

	Logging::getInstance()->log(
        "EpsilonGreedyOnce parameters: alpha=%.2f; epsilon=%.2f.",
        Configuration::getInstance()->alpha,
        Configuration::getInstance()->epsilon
    );

    //float lucky = (rand() % 1000) / 1000.f;
    double lucky =  dist(gen); //(rand() / (double)(RAND_MAX + 1));
    double epsilon = Configuration::getInstance()->epsilon; //alias for easy reading
    if (lucky < epsilon) {
		Logging::getInstance()->log(
            "Choosing randomly: (%.3f < %.3f)", lucky, epsilon);
		name += " - random choice";
		currentStrategy = randomUniformBegin();
	}
    else {
        Logging::getInstance()->log(
            "Choosing greedily: (%.3f > %.3f)", lucky, epsilon
        );
		name += " - greedy choice";

        //file to read is MegaBot-vs-enemy.xml
        string inputFile = Configuration::getInstance()->enemyInformationInputFile();

        tinyxml2::XMLDocument doc;
        XMLError errorInput = doc.LoadFile(inputFile.c_str());

        if (errorInput == XMLError::XML_NO_ERROR) {
            //BWAPI::Player* enemy = Broodwar->enemy();
            string enemy_name = Broodwar->enemy()->getName();
            XMLElement* rootNode = doc.FirstChildElement("scores");
			XMLElement* frameNode;

            if (rootNode != NULL) {
				frameNode = rootNode->FirstChildElement("frame");
				if(frameNode == NULL){
					currentStrategy = randomUniformBegin();
					frameNode->SetAttribute("value",0);
				}
				else {
					XMLElement* candidate = frameNode->FirstChildElement();
					string best_name;
					float best_score = -1.0f;

					map<string, float> scoresMap;
					scoresMap[MetaStrategy::NUSBot] = 0;
					scoresMap[MetaStrategy::SKYNET] = 0;
					scoresMap[MetaStrategy::XELNAGA] = 0;

					while (candidate != NULL) {
						float score = -FLT_MAX;
						candidate->QueryFloatText(&score);
						if(candidate->Name() != "Expand" && candidate->Name() != "Explore" && candidate->Name() != "PackAndAttack")
						{
							scoresMap[candidate->Name()] = score;
						}
						candidate = candidate->NextSiblingElement();
					}

					for (std::map<string, float>::iterator it = scoresMap.begin(); it != scoresMap.end(); ++it) {
						if (it->second > best_score && it->first.c_str() != "Expand" && it->first.c_str() != "Explore" && it->first.c_str() != "PackAndAttack") {
							best_name = it->first;
							best_score = it->second;
						}
					}

					if (best_name.empty()) {
						Logging::getInstance()->log(
							"Best strategy could not be determined. Choosing randomly"
						);
						name += " failed. Best score not found";
						currentStrategy = randomUniformBegin();
					}
					else {
						currentStrategy = portfolio[best_name];
					}
				}
            }
            else {
                Logging::getInstance()->log(
					"Enemy information not found, choosing strategy randomly"
				);
				name += " failed. Enemy info not found";
				currentStrategy = randomUniformBegin();
	        }
        }
        else { //prints error
            Logging::getInstance()->log(
                "Error while parsing scores file '%s': '%s'. Choosing randomly.",
                inputFile.c_str(),
                doc.ErrorName()
            );
			name += " failed. File not found?";
			currentStrategy = randomUniformBegin();
        }
	}
	Logging::getInstance()->log(
		"%s: onStart() - executed in EpsilonGreedyOnce::onStart", getCurrentStrategyName().c_str()
	);
	//TODO: maybe the call below is unecessary: all behaviors have been initializes, right?
	currentStrategy->onStart();
}

void EpsilonGreedyOnce::onFrame() {
    return; //EpsilonGreedyOnce does not change strategy during the match
}

void EpsilonGreedyOnce::discountCrashes() {
    using namespace tinyxml2;

    //file to read is MegaBot-vs-enemy.xml
    string inputFile = Configuration::getInstance()->enemyInformationInputFile();
    string outputFile = Configuration::getInstance()->enemyInformationOutputFile();
    string crashFile = Configuration::getInstance()->crashInformationInputFile();

    tinyxml2::XMLDocument doc;
    XMLError errorInputCrash = doc.LoadFile(crashFile.c_str());

    tinyxml2::XMLDocument doc2;
    XMLError errorInput = doc2.LoadFile(inputFile.c_str());

    if (errorInputCrash == XMLError::XML_NO_ERROR) {
        XMLElement* rootNode = doc.FirstChildElement("crashes");
        if (rootNode != NULL) {
            XMLElement* behavior = rootNode->FirstChildElement();

            map<string, float> crashesMap;
            crashesMap[MetaStrategy::NUSBot] = 0;
            crashesMap[MetaStrategy::SKYNET] = 0;
            crashesMap[MetaStrategy::XELNAGA] = 0;

            while (behavior != NULL) {
                float score = -FLT_MAX;
                behavior->QueryFloatText(&score);
                crashesMap[behavior->Name()] = score;
                behavior = behavior->NextSiblingElement();
            }

            if (errorInput == XMLError::XML_NO_ERROR) {
                XMLElement* inputRootNode = doc2.FirstChildElement("scores");

                if (inputRootNode != NULL) {
                    XMLElement* input_behavior = inputRootNode->FirstChildElement();

                    map<string, float> scoresMap;
                    scoresMap[MetaStrategy::NUSBot] = 0;
                    scoresMap[MetaStrategy::SKYNET] = 0;
                    scoresMap[MetaStrategy::XELNAGA] = 0;

                    while (input_behavior != NULL) {
                        float score = -FLT_MAX;
                        float alpha = Configuration::getInstance()->alpha;

                        input_behavior->QueryFloatText(&score);
                        if (score > 0 && input_behavior == behavior) {
                            for (int i = crashesMap[input_behavior->Name()]; i > 0; i--)
                                score = (1 - alpha)*score + alpha * (-1);

                        }
                        scoresMap[input_behavior->Name()] = score;
                        input_behavior->SetText(score);
                        input_behavior = input_behavior->NextSiblingElement();
                    }
                }
                doc2.SaveFile(outputFile.c_str());
            }
            else { //prints error
				Logging::getInstance()->log(
                    "Error while parsing input file '%s'. Error: '%s'",
                    Configuration::getInstance()->enemyInformationInputFile().c_str(),
                    doc2.ErrorName()
                );
            }
        }
    }
    else { //prints error
        Logging::getInstance()->log(
            "Error while parsing crash file '%s'. Error: '%s'",
            Configuration::getInstance()->crashInformationInputFile().c_str(),
            doc.ErrorName()
        );
    }
}

