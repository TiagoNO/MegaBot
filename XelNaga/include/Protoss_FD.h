#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <Arbitrator.h>
#include <WorkerManager.h>
#include <SupplyManager.h>
#include <BuildManager.h>
#include <BuildOrderManager.h>
#include <TechManager.h>
#include <UpgradeManager.h>
#include <BaseManager.h>
#include <ScoutManager.h>
#include <DefenseManager.h>
#include <UnderAttackManager.h>
#include <InformationManager.h>
#include <SpyManager.h>
#include <BorderManager.h>
#include <UnitGroupManager.h>
#include <SpendManager.h>
#include <ArmyManager.h>
#include <MoodManager.h>
#include <EnhancedUI.h>


class Protoss_FD : public BWAPI::AIModule
{
private:
	double	minDist;
	int			frame;
	int			lastFrameExpand;
	int			lastScout;
	bool         dddd; //��ũ�� �����ֱ� �ѹ���
	bool             d;
	bool            dd;
	bool           ddddd;
	bool             d5;
	bool            first_probe_onrevoke;
	int           a;
	int           getFirst_scout_probe_ID;
	int				getCIG2013_scout_probe_ID;
	int           enemy_start_locationX, enemy_start_locationY;
	int			  enemy_start_location_change;
	bool		  enemy_start_location_change_true;
	bool          enemy_start_first;
	bool		  scout_start;	 
	int			  self_attack_unit_position_x[150]; //���� ���� ������ + ���ݷ� ����  x,y,���ݷ� . 30�������� ���߿� �� �ʿ��ϸ� �÷������. chc
	int			  self_attack_unit_position_y[150];
	double		  self_attack_unit_attak_power[150];   
	int			  enemy_attack_unit_position_x[150]; 
	int			  enemy_attack_unit_position_y[150]; 
	double			  enemy_attack_unit_attak_power[150]; 
	double			  confidence[150]; //�츮�� �ڽŰ�
	double			  confidence_enemy[150]; // �� �ڽŰ�


	//cig2013 ����
	//�ѹ��� �ޱ����� bool

	bool cig0;
	bool cig1;
	bool cig2;
	bool cig3_fastest_3gate_zealot;
	bool cig4_fatest_fix_build_end;
	bool cig4_slow_fix_build_end;
	bool cig5_terran_start_auto_build;

	int Protoss_one_Gateway_cig_id;
	int Protoss_two_Gateway_cig_id;
	int Protoss_one_gas_cig_id;
	int cig_2013_cyber_timing;
	int cig_2013_adun_timing;

	int aiide2014_total_attack_true_frame;
	bool aiide2014_huban_attack;
	bool aiide2014_autobuild_start;




	//cig2013 ��


	int			search_prob_id;
	bool				firsss21;
	bool			very_early_rush_build;
	bool				very_early_rush_auto_build;
	bool			 scout_complete2;
	bool			very_early_rush;
	bool			defense_makgi;
	bool			firsss;
	bool			firsss2;
	bool			cyber_cancel;
	bool			  run_away[150];  //�ְ� �������� �ִ���
	bool				total_attack; //�Ѱ��ݸ��
	bool				my_auto_build; //�ڵ�������
	bool				my_expand_true; //�� �ո��� �ִ���
	int					ob_3_expand; //������
	int					probe_attack_id; //�� �����ϲ��� ����ϴ� �츮�� �ϲ� ���̵�
	int				enemy_search_unit;
	bool			enemy_attack_first1;
	bool			continuos_bu;
	bool			cheat_early;
	bool			my_exten;

	bool			early_attack_assimi;
	bool			early_attack_gate;
	bool			very_early_attack_gate;

	bool			robotics_1;
	bool			shuttle_1;
	bool			zerg_first_attack;
	bool			zerg_first_;
	bool			storm_enemy_confidence_first;
	bool			early_rush; //�� �ʹݷ����Ǵ�
	bool			multi_bool1;
	bool			multi_bool2;
	bool			multi_bool3;
	bool			multi_bool4;


	bool				high_templer_loaded_complete;  //�������÷� 4������ �� ������
	std::set<BWTA::BaseLocation*>::const_iterator base_lo;

	//�� �̻� ������� �����ϸ� ����?


	//BWTA::BaseLocation base_lo;
	bool    base_lo_first_input;  //base_lo �ʱ�ȭ

	bool    enemy_dead;
	int		enemy_dead_frame;
	bool    enemy_dead_after_2min;
	bool    first_tt22;
	bool cig2013_11;


	int used_ob[2];   //������ ����
	bool ob_bool;
	bool ob_bool2;

	bool en_expand_exist;

	//chc
	std::set<BWTA::Chokepoint*> enemyBorder;
	std::vector<BWTA::Chokepoint*> enemyBorderVector;


	BWTA::BaseLocation *closest;
	BWTA::BaseLocation *home;

public:
	virtual void onStart				();
	virtual void onEnd					(bool isWinner);
	virtual void onFrame				();
	virtual void onUnitDiscover	(BWAPI::Unit* unit);
	virtual void onUnitEvade		(BWAPI::Unit* unit);
	virtual void onUnitMorph		(BWAPI::Unit* unit);
	virtual void onUnitRenegade	(BWAPI::Unit* unit);
	virtual void onUnitDestroy	(BWAPI::Unit* unit);
	virtual void onSendText			(std::string text);

	~Protoss_FD(); //not part of BWAPI::AIModule

	void showStats(); //not part of BWAPI::AIModule
	void showPlayers();
	void showForces();
	bool analyzed;

	std::map<BWAPI::Unit*,BWAPI::UnitType>			buildings;
	Arbitrator::Arbitrator<BWAPI::Unit*,double> arbitrator;

	WorkerManager					*workerManager;
	SupplyManager					*supplyManager;
	BuildManager					*buildManager;
	TechManager						*techManager;
	UpgradeManager				*upgradeManager;
	BaseManager						*baseManager;
	ScoutManager					*scoutManager;
	SpendManager					*spendManager;
	BuildOrderManager			*buildOrderManager;
	DefenseManager				*defenseManager;
	UnderAttackManager		*underAttackManager;
	InformationManager		*informationManager;
	BorderManager					*borderManager;
	UnitGroupManager			*unitGroupManager;
	SpyManager						*spyManager;
	ArmyManager						*armyManager;
	MoodManager						*moodManager;
	EnhancedUI						*enhancedUI;
	bool									showManagerAssignments;
	bool									debugMode;
	bool									destinationMineralSpotted;
	bool									cleaningPath;
	//bool				total_attack; //�Ѱ��ݸ��
};