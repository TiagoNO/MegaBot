#pragma once
#include "MetaStrategy.h"
#include "BWAPI.h"
#include "EpsilonGreedyOnce.h"

/**
 * Just like epsilon greedy once, but can switch to a new algorithm anytime 
 */
class EpsilonGreedy : public EpsilonGreedyOnce {

	/** Counts the number of crashes to reduce score during strategy selection */
	void discountCrashes();
	//BWAPI::AIModule* randomUniform();

public:
	EpsilonGreedy(void);
	~EpsilonGreedy(void);

	//virtual void onStart(); don't override parent onStart
	virtual void onFrame();
};

