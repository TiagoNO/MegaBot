#pragma once
#include "MetaStrategy.h"
#include "BWAPI.h"
class EpsilonGreedyOnce : public MetaStrategy {

	/** Counts the number of crashes to reduce score during strategy selection */
	void discountCrashes();
	//BWAPI::AIModule* randomUniform();

public:
	EpsilonGreedyOnce(void);
	~EpsilonGreedyOnce(void);

	virtual void onStart();
	virtual void onFrame();
};

