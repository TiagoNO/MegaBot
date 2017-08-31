#include "EpsilonGreedy.h"
#include <BWAPI.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include "../utils/tinyxml2.h"
#include "../utils/Logging.h"
#include "MetaStrategy.h"

using namespace tinyxml2;
using namespace BWAPI;

EpsilonGreedy::EpsilonGreedy(void) : EpsilonGreedyOnce() {
	name = "Epsilon-greedy (multistage)";
	srand(time(NULL));
}


EpsilonGreedy::~EpsilonGreedy(void) {
}


void EpsilonGreedy::onFrame() {
	return; //TODO
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

