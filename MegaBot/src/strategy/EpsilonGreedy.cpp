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
		MatchData::getInstance()->updateframeCrashFile();
		Logging::getInstance()->log("Updating Crash File");
	}
	if(Broodwar->getFrameCount() == 0)
	{
		registerFirstBehavior(currentStrategy);
		Logging::getInstance()->log("Checking if there was a crash last game...");
		discountCrashes();
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


	if(Broodwar->getFrameCount() == 0) // if we are in the first frame, we have to choose one of the three main berraviors
	{
		frameNode = rootNode->FirstChildElement("frame");
		if(frameNode == NULL)
		{
			frameNode = doc.NewElement("frame");
			frameNode->SetAttribute("value",0);
			rootNode->InsertFirstChild(frameNode);

			// selects a strategy at random and initializes its value as (one/zero)
			map<string, BWAPI::AIModule*>::iterator behv;
			for(behv = portfolio.begin(); behv != portfolio.end(); behv++)
			{
				if((*behv).second != portfolio["Expand"] && (*behv).second != portfolio["Explore"] && (*behv).second != portfolio["PackAndAttack"])
				{
					myBehvNode = doc.NewElement((*behv).first.c_str());
					myBehvNode->SetText(0);
					frameNode->InsertFirstChild(myBehvNode);
				}
			}
			currentStrategy = randomUniformBegin();
		}
		else
		{
			myBehvNode = frameNode->FirstChildElement();
			if(myBehvNode == NULL)
			{
				// selects a strategy at random and initializes its value as (one/zero)
				map<string, BWAPI::AIModule*>::iterator behv;
				for(behv = portfolio.begin(); behv != portfolio.end(); behv++)
				{
					if((*behv).second != portfolio["Expand"] && (*behv).second != portfolio["Explore"] && (*behv).second != portfolio["PackAndAttack"])
					{
						myBehvNode = doc.NewElement((*behv).first.c_str()); 
						myBehvNode->SetText(0);
						frameNode->InsertFirstChild(myBehvNode);
					}
				}
				currentStrategy = randomUniformBegin();
			}
			else
			{
				boost::random::mt19937 gen(static_cast<unsigned int>(std::time(0)));
				boost::random::uniform_real_distribution<> dist(0.0, 1.0);
				double lucky =  dist(gen); //(rand() / (double)(RAND_MAX + 1));
				double epsilon = Configuration::getInstance()->epsilon; //alias for easy reading
				if(lucky < epsilon) {
					currentStrategy = randomUniformBegin();
				}
				else
				{
					float bigger = -1.0f;
					string BotName = "Skynet";
					float score = -FLT_MAX;
					while (myBehvNode != NULL) 
					{
						Logging::getInstance()->log("Max behavior value %i and actual behavior value %i",bigger,myBehvNode->FloatAttribute("value"));
						if (bigger < myBehvNode->FloatAttribute("value")) 
						{
							bigger = myBehvNode->FloatAttribute("value");
							BotName = myBehvNode->Name();
						}
						myBehvNode = myBehvNode->NextSiblingElement();
					}
					if(BotName.empty())
					{
						currentStrategy = randomUniformBegin();
					}
					else
					{
						forceStrategy(BotName);
					}
				}
			}
		}
	}
	else // if we are in the middle of the game, we have to see what is the best choise for this moment of the game
	{
		frameNode = rootNode->FirstChildElement("frame");
		while(frameNode != NULL)
		{
			if(frameNode->IntAttribute("value") == Broodwar->getFrameCount())
			{
				Logging::getInstance()->log("Found scores at frame %d", frameNode->IntAttribute("value"));
				break;
			}
			frameNode = frameNode->NextSiblingElement("frame");
		}
		if(frameNode == NULL) // if it is the first time we reached that frame against this enemy
		{
			frameNode = doc.NewElement("frame");
			frameNode->SetAttribute("value",Broodwar->getFrameCount());
			rootNode->InsertEndChild(frameNode);

			// selects a strategy at random and initializes its value as (one/zero)
			map<string, BWAPI::AIModule*>::iterator behv;
			for(behv = portfolio.begin(); behv != portfolio.end(); behv++)
			{
				myBehvNode = doc.NewElement((*behv).first.c_str()); 
				myBehvNode->SetText(0);
				frameNode->InsertFirstChild(myBehvNode);
			}
			forceStrategy("random");
		}
		else // if this frame is in the file, we look for the best choise
		{
			myBehvNode = frameNode->FirstChildElement();
			if(myBehvNode == NULL) // if there was an error in some point while writing things in the file, we can still fix it!
			{
				// selects a strategy at random and initializes its value as (one/zero)
				map<string, BWAPI::AIModule*>::iterator behv;
				for(behv = portfolio.begin(); behv != portfolio.end(); behv++)
				{
					myBehvNode = doc.NewElement((*behv).first.c_str()); 
					myBehvNode->SetText(0);
					frameNode->InsertFirstChild(myBehvNode);
				}
				forceStrategy("random");
			}
			else // if there was no error and the berraviors were written, lets decide our next move!
			{				
				// frame node has children, select amongst the highest scores
				boost::random::mt19937 gen(static_cast<unsigned int>(std::time(0)));
				boost::random::uniform_real_distribution<> dist(0.0, 1.0);
				double lucky =  dist(gen); //(rand() / (double)(RAND_MAX + 1));
				double epsilon = Configuration::getInstance()->epsilon; //alias for easy reading
				if(lucky < epsilon) {
					forceStrategy("random");
				}
				else
				{
					float bigger = -1.0f;
					string BotName;
					float score;
					while (myBehvNode != NULL) 
					{
						myBehvNode->QueryFloatText(&score);
						Logging::getInstance()->log("Max behavior value %f and actual behavior value %f",bigger,score);
						if (bigger < score) 
						{
							bigger = score;
							BotName = myBehvNode->Name();
						}
						myBehvNode = myBehvNode->NextSiblingElement();
					}
					if(BotName.empty())
					{
						forceStrategy("random");
					}
					else
					{
						forceStrategy(BotName);
					}
				}
			}
		}
	}
	lastFrameChecked = Broodwar->getFrameCount();
	doc.SaveFile(outputFile.c_str());
	doc.SaveFile(inputFile.c_str());
}

void EpsilonGreedy::registerFirstBehavior(BWAPI::AIModule* currentStrategy)
{
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
	if(frameNode == NULL)
	{
		frameNode = doc.NewElement("frame");
		frameNode->SetAttribute("value",0);
		rootNode->InsertFirstChild(frameNode);
	}

	myBehvNode = frameNode->FirstChildElement();
	if(myBehvNode == NULL)
	{
		map<string, BWAPI::AIModule*>::iterator behv;
		for(behv = portfolio.begin(); behv != portfolio.end(); behv++)
		{
			if((*behv).second != portfolio["Expand"] && (*behv).second != portfolio["Explore"] && (*behv).second != portfolio["PackAndAttack"])
			{
				myBehvNode = doc.NewElement((*behv).first.c_str());
				myBehvNode->SetText(0);
				frameNode->InsertFirstChild(myBehvNode);
			}
		}	
	}
	doc.SaveFile(outputFile.c_str());
	doc.SaveFile(inputFile.c_str());
}

void EpsilonGreedy::discountCrashes() {
	using namespace tinyxml2;

	//file to read is MegaBot-vs-enemy.xml
	string inputFile = Configuration::getInstance()->enemyInformationInputFile();
	string outputFile = Configuration::getInstance()->enemyInformationOutputFile();
	string crashedBehaviorName = MatchData::getInstance()->getCrashedBehaviorName();
	int frameThatCrashed = MatchData::getInstance()->getFrameThatCrashed();
	Logging::getInstance()->log("Trying to find behavior %s in frame %i",crashedBehaviorName.c_str(),frameThatCrashed);
	
	if(crashedBehaviorName != "empty" && frameThatCrashed != -1) // if the last game crashed
	{
		Logging::getInstance()->log("Discounting behavior %s because it crashed last game in the frame %i",crashedBehaviorName.c_str(),frameThatCrashed);
		tinyxml2::XMLDocument doc;
		XMLError inputError = doc.LoadFile(inputFile.c_str());
		if(inputError == XML_NO_ERROR)
		{
			XMLElement *rootNode;
			XMLElement *frameNode;
			XMLElement *myBehvNode;
			// if file was not found, we create a node and fill information in it
			if (inputError == XML_ERROR_FILE_NOT_FOUND) {
				rootNode = doc.NewElement("scores");
				doc.InsertFirstChild(rootNode);
			}
			// if another error occurred, we're in trouble =/
			else if (inputError != XML_NO_ERROR) {
				Logging::getInstance()->log("Error while parsing file '%s'. Won't switch behavior. Error: '%s'",inputFile,doc.ErrorName());
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
			while(frameNode != NULL)
			{
				if(frameNode->IntAttribute("value") == frameThatCrashed)
				{
					break;
				}
				frameNode = frameNode->NextSiblingElement("frame");
			}
			if(frameNode != NULL)
			{
				myBehvNode = frameNode->FirstChildElement(crashedBehaviorName.c_str());
				if(myBehvNode != NULL)
				{
				    float alpha = Configuration::getInstance()->alpha; //alias for easy reading
					float oldScore;
					int result_value = -1;
					float score;
					myBehvNode->QueryFloatText(&score);
					score = (1 - alpha)*oldScore + alpha*result_value;
					myBehvNode->SetText(score);
				}
			}
		}
		doc.SaveFile(outputFile.c_str());
		doc.SaveFile(inputFile.c_str());
	}
}

