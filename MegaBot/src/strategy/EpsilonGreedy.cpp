#include "EpsilonGreedy.h"
#include <BWAPI.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include "../utils/tinyxml2.h"
#include "../utils/Logging.h"
#include "MetaStrategy.h"
#include "../data/MatchData.h"

using namespace tinyxml2;
using namespace BWAPI;

EpsilonGreedy::EpsilonGreedy(void) : EpsilonGreedyOnce() {
	name = "Epsilon-greedy (multistage)";
	srand(time(NULL));
}


EpsilonGreedy::~EpsilonGreedy(void) {
}


void EpsilonGreedy::onFrame() {
	if (Broodwar->getFrameCount() >= lastFrameChecked + 4286) { // every 3 minutes picks a new behavior
		Logging::getInstance()->log(
			"Selecting behavior (in minute %d)", Broodwar->elapsedTime() / 60
		);
		chooseNewBehavior(currentStrategy);
		MatchData::getInstance()->registerMyBehaviorName(getCurrentStrategyName().c_str());
	}
}

void EpsilonGreedy::chooseNewBehavior(BWAPI::AIModule* currentStrategy) {
	using namespace tinyxml2;

	XMLElement* rootNode;
	XMLElement* myBehvNode;
	XMLElement* frameNode;
	XMLElement* queryNode;

	string inputFile = Configuration::getInstance()->enemyInformationInputFile();
	string outputFile = Configuration::getInstance()->enemyInformationOutputFile();

	tinyxml2::XMLDocument doc;
	XMLError input_result = doc.LoadFile(inputFile.c_str());

	// if file was not found, we create a node and fill information in it
	if (input_result == XML_ERROR_FILE_NOT_FOUND) {
		rootNode = doc.NewElement("scores");
		doc.InsertFirstChild(rootNode);
	}
	// if another error occurred, we're in trouble =/
	else if (input_result != XML_NO_ERROR) {

		Logging::getInstance()->log(
			"Error while parsing file '%s'. Won't switch behavior. Error: '%s'",
			inputFile,
			doc.ErrorName()
		);
		return;
	}
	else { //no error, goes after root node
		rootNode = doc.FirstChildElement("scores");
		if (rootNode == NULL) {
			rootNode = doc.NewElement("scores");
			doc.InsertFirstChild(rootNode);
		}
	}

	frameNode = rootNode->FirstChildElement("frame");
	// traverses frame nodes until finds one corresponding to the current frame
	// (or gets null to create a new one)
	while (frameNode != NULL) {
		if (frameNode->Attribute("value") != NULL && frameNode->IntAttribute("value") == Broodwar->getFrameCount()) {
			// found a node corresponding to the current frame
			Logging::getInstance()->log(
				"Found scores at frame %d", frameNode->IntAttribute("value")
			);
			break;
		}
		frameNode = frameNode->NextSiblingElement("frame");
	}
	if (frameNode == NULL) {
		// node with current frame not found, create a new one
		frameNode = doc.NewElement("frame");
		frameNode->SetAttribute("value", Broodwar->getFrameCount());
		rootNode->InsertEndChild(frameNode);

		// selects a strategy at random and initializes its value as zero
		forceStrategy("random");
		myBehvNode = doc.NewElement(getCurrentStrategyName().c_str());
		myBehvNode->SetAttribute("value", 0);
		frameNode->InsertFirstChild(myBehvNode);
	}
	
	// checks for behavior scores
	myBehvNode = frameNode->FirstChildElement();
	if (myBehvNode == NULL) {
		// if the frame node has no child, select a random behavior
		// and initializes its value with zero
		// TODO: must initialize values of all behaviors to zero,
		// this would mitigate issue [1] bellow
		forceStrategy("random");
		myBehvNode = doc.NewElement(getCurrentStrategyName().c_str());
		myBehvNode->SetAttribute("value", 0);
		frameNode->InsertFirstChild(myBehvNode);
	}
	else {
		// frame node has children, select amongst the highest scores
		// TODO: there is no epsilon here!
		// [1] TODO: potential problem: what if the node has only one child?
		float bigger = -1.0f;
		string BotName = "Skynet";
		float score = -FLT_MAX;
		while (myBehvNode != NULL) {
			if (bigger < myBehvNode->FloatAttribute("value")) {
				bigger = myBehvNode->FloatAttribute("value");
				BotName = myBehvNode->Name();
			}
			myBehvNode = myBehvNode->NextSiblingElement();
		}
		forceStrategy(BotName);
	}
	
	lastFrameChecked = Broodwar->getFrameCount();
	doc.SaveFile(outputFile.c_str());
	doc.SaveFile(inputFile.c_str());
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

