#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cfloat>
#include "BWAPI.h"
#include "MetaStrategy.h"
#include "Xelnaga.h"
#include "Skynet.h"
#include "PackAndAttack.h"
#include "Expand.h"
#include "Explore.h"
#include "NUSBotModule.h"
#include "../MegaBot.h"
#include "../data/Configuration.h"
#include "../utils/tinyxml2.h"
#include "../utils/Logging.h"
#include "../data/MatchData.h"
#include "EpsilonGreedy.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>


//initializes consts
const string MetaStrategy::SKYNET = "Skynet";
const string MetaStrategy::XELNAGA = "Xelnaga";
const string MetaStrategy::NUSBot = "NUSBot";
const string MetaStrategy::EXPLORE = "Explore";
const string MetaStrategy::EXPAND = "Expand";
const string MetaStrategy::PACKANDATTACK = "PackAndAttack";

MetaStrategy::MetaStrategy() : rng(std::time(0)) {
	name = "none";

	//initalizes behaviors
    portfolio.insert(make_pair(SKYNET, new Skynet()));
    portfolio.insert(make_pair(XELNAGA, new Xelnaga()));
    portfolio.insert(make_pair(NUSBot, new NUSBotModule()));
	portfolio.insert(make_pair(EXPLORE, new Explore()));
	portfolio.insert(make_pair(EXPAND, new Expand()));
	portfolio.insert(make_pair(PACKANDATTACK,new PackAndAttack()));

    //initializes reverse map
	map<string, BWAPI::AIModule*>::iterator behv;
	for(behv = portfolio.begin(); behv != portfolio.end(); behv++){
		strategyNames.insert(make_pair((*behv).second, (*behv).first));
		//Logging::getInstance()->log("Added %s to reverse map", (*behv).first.c_str() );
    }

	
}

MetaStrategy::~MetaStrategy() {
	
}

BWAPI::AIModule* MetaStrategy::getCurrentStrategy(){
	return currentStrategy;
}

std::string MetaStrategy::getCurrentStrategyName(){
	return strategyNames[currentStrategy];
}

void MetaStrategy::onStart() {
	lastFrameChecked = 0;
	map<string, BWAPI::AIModule*>::iterator behv;

	for(behv = portfolio.begin(); behv != portfolio.end(); behv++){
		Logging::getInstance()->log("%s: onStart()", (*behv).first.c_str());
		(*behv).second->onStart();
	}
}

void MetaStrategy::print()
{
	int a = 0;
	map<string, BWAPI::AIModule*>::iterator behv;

	for(behv = portfolio.begin(); behv != portfolio.end(); behv++){
		Broodwar->printf("%s %i", (*behv).first.c_str(),a);
		a++;
	}
}

string MetaStrategy::getName(){
	return name;
}

int MetaStrategy::getLastFrameNode()
{
	return lastFrameChecked;
}


void MetaStrategy::forceStrategy(string strategyName){

	Logging::getInstance()->log("Forced strategy switch to '%s'", strategyName.c_str());
	string oldStrategyName = getCurrentStrategyName();

	if (strategyName == "random"){
		currentStrategy = randomUniform();
	}
	else if ( portfolio.find(strategyName) != portfolio.end() ){ //found strategyName in map
		currentStrategy = portfolio[strategyName];
	}
	else { //strategyName not found in map
		Logging::getInstance()->log(
			"Attempted to switch to invalid strategy '%s'. Will not switch.",
			strategyName.c_str()
		);
		return;
	}
	

	//undoes switches in case of some error:
	if (currentStrategy == NULL){
		Logging::getInstance()->log(
			"Attempted to switch to invalid strategy '%s'. Reverting switch...",
			strategyName.c_str()
		);
		currentStrategy = portfolio[oldStrategyName];
		return;
	}

	Logging::getInstance()->log(
		"Switching %s -> %s", oldStrategyName.c_str(), getCurrentStrategyName().c_str()
	);

}

AIModule* MetaStrategy::randomUniform() {
	Logging::getInstance()->log("Random uniform strategy selection...");
		
	boost::random::uniform_int_distribution<> unifInt(0, portfolio.size() - 1);
	int index = unifInt(rng);

	//code partly from: http://stackoverflow.com/a/158865
	map<string,AIModule*>::iterator iter = portfolio.begin();
	std::advance(iter, index);

	//just testing the randomness of the generator below :P
	//Logging::getInstance()->log("Random sequence: %d %d %d %d %d", dist(gen), dist(gen), dist(gen), dist(gen), dist(gen));
	Logging::getInstance()->log("Random index: %d", index);
	Logging::getInstance()->log("Selected: %s", (*iter).first.c_str());
	if((*iter).second == portfolio["Explore"] || (*iter).second == portfolio["Expand"] || (*iter).second == portfolio["PackAndAttack"])
	{
		Broodwar->sendText("changing into %s",(*iter).first.c_str());
		return (*iter).second;
	}
	else
	{
		Broodwar->sendText("stayed in the berravior, because selected %s",(*iter).first.c_str());
		return portfolio[Configuration::getInstance()->firstBerraviorChoise];
	}
}

AIModule* MetaStrategy::randomUniformBegin() {
	Logging::getInstance()->log("Random uniform strategy selection...");

	Random rand;
	int index = (rand.nextInt())%3;
	Broodwar->sendText("%i",index);
	if(index == 0) {
		return portfolio["NUSBot"];
	}
	else if(index == 1)	{
		return portfolio["Skynet"];
	}
	else if(index == 2)	{
		return portfolio["Xelnaga"];
	}
	else {
		return portfolio["NUSBot"];
	}
}

string MetaStrategy::chooseNewBehavior(BWAPI::AIModule* currentStrategy)
{
    using namespace tinyxml2;


    /* DEBUG
    ofstream outFile;
    outFile.open("bwapi-data/write/dbg.txt", ios::out | ios::app);
    */

    XMLElement* rootNode;
    XMLElement* myBehvNode;
	XMLElement* frameNode;
    XMLElement* queryNode;

    string inputFile = Configuration::getInstance()->enemyInformationInputFile();
    string outputFile = Configuration::getInstance()->enemyInformationOutputFile();

    //const char* filename = Configuration::getInstance()->readDataFile.c_str();

    tinyxml2::XMLDocument doc;
    XMLError input_result = doc.LoadFile(inputFile.c_str());

    // if file was not found, ok, we create a node and fill information in it
	if (input_result == XML_ERROR_FILE_NOT_FOUND) {
        rootNode = doc.NewElement("scores");
        doc.InsertFirstChild(rootNode);
    }
    // if another error occurred, we're in trouble =/
    else if (input_result != XML_NO_ERROR) {
		
        /*Broodwar->printf(
            "Error while parsing the configuration file '%s'. Error: '%s'",
            inputFile,
            doc.ErrorName()
        );*/

		
        return "a";
    }
    else { //no error, goes after root node
        rootNode = doc.FirstChildElement("scores");
        if (rootNode == NULL) {
            rootNode = doc.NewElement("scores");
            doc.InsertFirstChild(rootNode);
        }
    }

	frameNode = rootNode->FirstChildElement("frame");
	while(frameNode != NULL) {
		if(frameNode->Attribute("value") != NULL && frameNode->Attribute("value") == (const char*)(Broodwar->getFrameCount())) {
			break;
		}
		frameNode = frameNode->NextSiblingElement("frame");
	}
	if(frameNode == NULL) {
		frameNode = doc.NewElement("frame");
		frameNode->SetAttribute("value",Broodwar->getFrameCount());
		rootNode->InsertEndChild(frameNode);
		forceStrategy("random");
		myBehvNode = doc.NewElement(getCurrentStrategyName().c_str());
		myBehvNode->SetAttribute("value", 0);
		frameNode->InsertFirstChild(myBehvNode);
	}
	else {
		myBehvNode = frameNode->FirstChildElement();
		if (myBehvNode == NULL) {
			forceStrategy("random");
			myBehvNode = doc.NewElement(getCurrentStrategyName().c_str());
			myBehvNode->SetAttribute("value",0);
			frameNode->InsertFirstChild(myBehvNode);
		}
		else {
			float bigger = -1.0f;
			string BotName =  "Skynet";
			float score = -FLT_MAX;
			while(myBehvNode != NULL){
				if(bigger < myBehvNode->FloatAttribute("value")) {
					bigger = myBehvNode->FloatAttribute("value");
					BotName = myBehvNode->Name();
				}
				myBehvNode = myBehvNode->NextSiblingElement();
			}
			forceStrategy(BotName);
		}
	}
	lastFrameChecked = Broodwar->getFrameCount();
    doc.SaveFile(outputFile.c_str());
	doc.SaveFile(inputFile.c_str());
	return "a";
}

/*
void MetaStrategy::printInfo() {
    Broodwar->drawTextScreen(180, 5, "\x0F%s", currentStrategyId.c_str());
}
*/


