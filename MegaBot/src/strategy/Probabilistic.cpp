#include "Probabilistic.h"
#include "BWAPI.h"
#include "../utils/Logging.h"
#include "../utils/tinyxml2.h"

Probabilistic::Probabilistic(void) : StrategySelector() {
}


Probabilistic::~Probabilistic(void)
{
}

/**
 * Performs a weighted selection of strategy based on probabilities defined in config. file
 */
void Probabilistic::onStart() {
	currentStrategy = selectStrategy();
	Logging::getInstance()->log("%s: onStart() - executed in Probabilistic::onStart", getCurrentStrategyName().c_str());
	currentStrategy->onStart();
	
}

BWAPI::AIModule* Probabilistic::selectStrategy() {
	using namespace tinyxml2;

    string defaultBehavior = StrategySelector::SKYNET;	//in case something go wrong

    //parses strategy file
    map<string, float> behaviors;

    tinyxml2::XMLDocument doc;
    int result = doc.LoadFile(Configuration::getInstance()->strategyFile.c_str());

    if (result != XML_NO_ERROR) {
        Logging::getInstance()->log(
            "An error has occurred while parsing strategy file '%s'. Error: '%s'",
            Configuration::getInstance()->strategyFile.c_str(),
            doc.ErrorName()
            );
		return portfolio[defaultBehavior];
    }

    XMLElement* behaviorEntry = doc.FirstChildElement("strategy")->FirstChildElement("behavior");
    for (; behaviorEntry; behaviorEntry = behaviorEntry->NextSiblingElement()) {
        string name = string(behaviorEntry->Attribute("name"));
        float probability = 0;
        behaviorEntry->QueryFloatAttribute("probability", &probability);

        behaviors.insert(make_pair(name, probability));
    }


    //strategies loaded, now will select one
    float sum = 0.f; //probabilities should add to 1.0, but this is to guard against abnormal cases
    map<string, float>::iterator behv;
    for (behv = behaviors.begin(); behv != behaviors.end(); ++behv) {
        sum += behv->second;
    }

    /*
    uncomment when c++11 is available
    for (auto behv : behaviors) {
    sum += behv.second;
    }*/

    //generates a pseudo-random number between 0 and sum
    float random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sum));

    //traverses the list until we find an opening that matches the random number
    float acc = 0;
    for (behv = behaviors.begin(); behv != behaviors.end(); ++behv) {//for (auto opening : behaviors) {
        if (random < acc + behv->second) {	//found!
            Logging::getInstance()->log(
                "MegaBot chose: %s (random: %.3f, target: %.3f, acc: %.3f, sum: %.3f)",
                behv->first.c_str(), random, (acc + behv->second), acc, sum
            );
			//currentStrategy = portfolio[behv->first];
            return portfolio[behv->first]; // behv->first;
        }
        acc += behv->second;
    }
    Logging::getInstance()->log(
        "ERROR: behavior was not randomly selected (random: %.3f, acc: %.3f, sum: %.3f). Defaulting to: %s.",
        random, acc, sum, defaultBehavior
    );
	//currentStrategy = portfolio[defaultBehavior];
    return  portfolio[defaultBehavior]; // defaultBehavior;	//something went wrong, opening was not randomly selected =/
}

