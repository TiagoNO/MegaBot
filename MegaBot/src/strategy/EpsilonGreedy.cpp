#include "EpsilonGreedy.h"
#include <BWAPI.h>
#include "../utils/tinyxml2.h"
#include "../utils/Logging.h"
#include "StrategySelector.h"

using namespace tinyxml2;
using namespace BWAPI;

EpsilonGreedy::EpsilonGreedy(void) : StrategySelector() {
}


EpsilonGreedy::~EpsilonGreedy(void) {
}

/**
 * Performs epsilon-greedy selection of strategy
 */ 
void EpsilonGreedy::onStart() {

	srand(time(NULL));

	Logging::getInstance()->log(
        "EpsilonGreedy parameters: alpha=%.2f; epsilon=%.2f.",
        Configuration::getInstance()->alpha,
        Configuration::getInstance()->epsilon
    );

    //float lucky = (rand() % 1000) / 1000.f;
    double lucky = (rand() / (double)(RAND_MAX + 1));
    double epsilon = Configuration::getInstance()->epsilon; //alias for easy reading
    if (lucky < epsilon) {
		Logging::getInstance()->log(
            "Choosing randomly: (%.3f < %.3f)", lucky, epsilon
        );
        currentStrategy = probabilistic();
    }
    else {
        Logging::getInstance()->log(
            "Choosing greedily: (%.3f > %.3f)", lucky, epsilon
        );

        //file to read is MegaBot-vs-enemy.xml
        string inputFile = Configuration::getInstance()->enemyInformationInputFile();

        tinyxml2::XMLDocument doc;
        XMLError errorInput = doc.LoadFile(inputFile.c_str());

        if (errorInput == XMLError::XML_NO_ERROR) {
            //BWAPI::Player* enemy = Broodwar->enemy();
            string enemy_name = Broodwar->enemy()->getName();
            XMLElement* rootNode = doc.FirstChildElement("scores");

            if (rootNode != NULL) {
                XMLElement* candidate = rootNode->FirstChildElement();
                string best_name;
                float best_score = -1.0f;

                map<string, float> scoresMap;
				scoresMap[StrategySelector::NUSBot] = 0;
                scoresMap[StrategySelector::SKYNET] = 0;
                scoresMap[StrategySelector::XELNAGA] = 0;

                while (candidate != NULL) {
                    float score = -FLT_MAX;
                    candidate->QueryFloatText(&score);

                    scoresMap[candidate->Name()] = score;
                    candidate = candidate->NextSiblingElement();
                }

                for (std::map<string, float>::iterator it = scoresMap.begin(); it != scoresMap.end(); ++it) {
                    if (it->second > best_score) {
                        best_name = it->first;
                        best_score = it->second;
                    }
                }

                if (best_name.empty()) {
                    Logging::getInstance()->log("Best strategy could not be determined. Choosing randomly");
					currentStrategy = randomUniform();
                }
                else {
                    currentStrategy = portfolio[best_name];
                }
            }
            else {
                Logging::getInstance()->log("Enemy information not found, choosing strategy randomly");
                currentStrategy = randomUniform();
            }
        }
        else { //prints error
            Logging::getInstance()->log(
                "Error while parsing strategy file '%s'. Error: '%s'",
                Configuration::getInstance()->strategyFile.c_str(),
                doc.ErrorName()
                );
            currentStrategy = randomUniform();
        }
	}
}

void EpsilonGreedy::onFrame() {
    return; //does nothing, because epsilon-greedy does not change strategy during the match

	/*
	int thisFrame = Broodwar->getFrameCount();
    myBehaviorName = StrategySelector::getInstance()->getStrategy();

    MatchData::getInstance()->registerMyBehaviorName(myBehaviorName);
    currentBehavior = behaviors[myBehaviorName];
    currentBehavior->onFrame();
    logger->log("%s on!", myBehaviorName.c_str());

    if (Broodwar->elapsedTime() / 60 >= 81) {	//leave stalled game
        Broodwar->leaveGame();
        return;
    }

    currentBehavior->onFrame();
	
    //draws some text
    Broodwar->drawTextScreen(240, 20, "\x0F MegaBot v1.0.2");
    Broodwar->drawTextScreen(240, 35, "\x0F Strategy: %s", myBehaviorName.c_str());
    //Broodwar->drawTextScreen(5, 25, "\x0F Enemy behavior: %s", enemyBehaviorName.c_str());
    Broodwar->drawTextScreen(240, 45, "\x0F Enemy: %s", Broodwar->enemy()->getName().c_str());
    Broodwar->drawTextScreen(240, 60, "Frame count %d.", thisFrame);
    Broodwar->drawTextScreen(240, 75, "Seconds: %d.", Broodwar->elapsedTime());
	*/
}

AIModule* EpsilonGreedy::randomUniform() {
	//code from: http://stackoverflow.com/a/158865/1251716
	map<string,AIModule*>::iterator iter = portfolio.begin();
	std::advance(iter, rand() % portfolio.size());

	return (*iter).second;
}

void EpsilonGreedy::discountCrashes() {
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
            crashesMap[StrategySelector::NUSBot] = 0;
            crashesMap[StrategySelector::SKYNET] = 0;
            crashesMap[StrategySelector::XELNAGA] = 0;

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
                    scoresMap[StrategySelector::NUSBot] = 0;
                    scoresMap[StrategySelector::SKYNET] = 0;
                    scoresMap[StrategySelector::XELNAGA] = 0;

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

