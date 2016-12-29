#include "SpottedObject.h"
#include "../utils/Logging.h"

//using namespace BWAPI;

SpottedObject::SpottedObject(BWAPI::Unit* mUnit) {
    type = mUnit->getType();
    position = mUnit->getPosition();
    tilePosition = mUnit->getTilePosition();
    unitID = mUnit->getID();
	lastSeenFrame = BWAPI::Broodwar->getFrameCount();
}

void SpottedObject::update(BWAPI::Unit* mUnit) {

    if (unitID != mUnit->getID()) {
        Logging::getInstance()->log(
			"Warning, attempted updating units with diff IDs (expected=%d, received=%d). Ignoring...", 
			unitID, mUnit->getID()
		);
        return;
    }

    type = mUnit->getType();
    position = mUnit->getPosition();
    tilePosition = mUnit->getTilePosition();
	lastSeenFrame = BWAPI::Broodwar->getFrameCount();
}

int SpottedObject::getUnitID() {
    return unitID;
}

BWAPI::UnitType SpottedObject::getType() {
    return type;
}

BWAPI::Position SpottedObject::getPosition() {
    return position;
}

int SpottedObject::getLastSeenFrame(){
	return lastSeenFrame;
}

BWAPI::TilePosition SpottedObject::getTilePosition() {
    return tilePosition;
}



