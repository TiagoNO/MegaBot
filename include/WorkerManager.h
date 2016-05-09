#pragma once
#include <Arbitrator.h>
#include <BWAPI.h>
#include <BaseManager.h>

class BuildOrderManager;
class WorkerManager : public Arbitrator::Controller<BWAPI::Unit,double>
{
public:
	class WorkerData
	{
	public:
		WorkerData() {resource = NULL; lastFrameSpam = 0;}
		BWAPI::Unit resource;
		BWAPI::Unit newResource;
		int lastFrameSpam;
	};
	WorkerManager();
	WorkerManager(Arbitrator::Arbitrator<BWAPI::Unit,double>* arbitrator);
	void setBaseManager(BaseManager* baseManager);
	void setBuildOrderManager(BuildOrderManager* buildOrderManager);
	virtual void onOffer(std::set<BWAPI::Unit> units);
	virtual void onRevoke(BWAPI::Unit unit, double bid);
	virtual void update();
	virtual std::string getName() const;
	virtual std::string getShortName() const;
	
	
	void onRemoveUnit(BWAPI::Unit unit);
	void setWorkersPerGas(int count);
	double getMineralRate() const;
	double getGasRate() const;
	int getOptimalWorkerCount() const;
	void enableAutoBuild();
	void disableAutoBuild();
	void setAutoBuildPriority(int priority);
	void setDestinationMineral(BWAPI::Unit);

private:

	Arbitrator::Arbitrator<BWAPI::Unit,double>* arbitrator;
	BaseManager* baseManager;
	BuildOrderManager* buildOrderManager;
	std::map<BWAPI::Unit,WorkerData> workers;
	std::map<BWAPI::Unit, std::set<BWAPI::Unit> > currentWorkers;
	std::map<BWAPI::Unit, Base*> resourceBase;
	std::map<BWAPI::Unit, int> desiredWorkerCount;
	std::vector<std::pair<BWAPI::Unit, int> > mineralOrder;
	BWAPI::Unit *destinationMineral;
	BWAPI::Unit *cleaner;
	int mineralOrderIndex;
	int lastSCVBalance;
	std::set<Base*> basesCache;
	int WorkersPerGas;

	bool	firsss2; //chc
	bool	very_early_rush;
	bool	very_early_attack_gate;
	bool	early_attack_assimi;
	bool			early_attack_gate;
	bool	early_rush ;
	bool	firsss;

	void rebalanceWorkers();
	void updateWorkerAssignments();
	double mineralRate;
	double gasRate;
	bool autoBuild;
	int autoBuildPriority;
	int optimalWorkerCount;
	bool cleaningInProgress;
};