#include "Protoss_Multi.h"
#include "../src/Util.h"
using namespace BWAPI;

//���� �����
#include <stdlib.h>
void Protoss_Multi::onStart()
{
	
	scout_start = false;
	enemy_start_location_change = 0;
	enemy_start_location_change_true = true;
	enemy_start_first = true;
	d5 = true;
	ddddd=true;
	dddd = false;
	firsss21 = false;
	first_probe_onrevoke = true;
	d = true;
	dd= true;
	a=0;
	search_prob_id = -1000;
	high_templer_loaded_complete = false; //�������÷� ���ø�Ʈ
	en_expand_exist = false;
	ob_bool = false;
	ob_bool2 = false;
	enemy_dead_frame = 999999;
	enemy_dead_after_2min = false;
	first_tt22 = false;
	enemy_attack_first1 = false;
	probe_attack_id = 0;
	zerg_first_attack = false; //���� ó�� ����11���� ���� 
	early_rush = false;
	continuos_bu = false;
	very_early_rush = false;
	cheat_early = false;
	my_exten = false;
	cyber_cancel = false;
	defense_makgi = false;
	very_early_rush_build = false;
	very_early_rush_auto_build = false;
	multi_bool1 = false;
	multi_bool2 = false;
	multi_bool3 = false;
	multi_bool4 = false;
	cig1 = false;
	cig2 = false;
	cig0 = false;
	cig3_fastest_3gate_zealot = true;
	cig4_fatest_fix_build_end = false;
	cig4_slow_fix_build_end = false;
	cig_2013_cyber_timing = -2;
	cig_2013_adun_timing = -2;
	cig5_terran_start_auto_build = false;
	cig2013_11 = false;
	aaab=false;

	Protoss_one_Gateway_cig_id = -2;
	Protoss_two_Gateway_cig_id = -2;
	Protoss_one_gas_cig_id = -2;

	getFirst_scout_probe_ID = -1000;
	getCIG2013_scout_probe_ID = -1000;


	bool			firsss = false;
	bool			firsss2 = false;

	scout_complete2 = false;
	early_attack_assimi = true;
	early_attack_gate = true;
	very_early_attack_gate = true;


	zerg_first_ = false;

	used_ob[0] = 0; //������ ���� �ʱ�ȭ
	used_ob[1] = 0; //������ ���� �ʱ�ȭ
	ob_3_expand = 0;
	enemy_search_unit = 0; //�� ��������

	enemy_dead = false;

	base_lo_first_input = false;
	my_auto_build = false;
	my_expand_true = false;

	robotics_1 = false;
	shuttle_1 = false;
	storm_enemy_confidence_first = false;
	



	this->showManagerAssignments=false;
	total_attack=false; //�Ѱ��� flase;
	if (Broodwar->isReplay()) return;

	Broodwar->setTextSize(0);
	//Broodwar->sendText("Protoss_Multi v2.0 AI Bot Testing");

	// Thanks for the trick, Gabriel!
	// Broodwar->setLatCom(false);

	// Enable some cheat flags

	Broodwar->enableFlag(Flag::UserInput);
	// Broodwar->enableFlag(Flag::CompleteMapInformation);

	BWTA::readMap();
	BWTA::analyze();
	this->analyzed=true;
	this->buildManager       = new BuildManager(&this->arbitrator);
	this->techManager        = new TechManager(&this->arbitrator);
	this->upgradeManager     = new UpgradeManager(&this->arbitrator);
	this->spyManager				 = new SpyManager(&this->arbitrator);
	this->workerManager      = new WorkerManager(&this->arbitrator);
	this->supplyManager      = new SupplyManager();
	this->spendManager			 = new SpendManager();
	this->baseManager        = new BaseManager();
	this->buildOrderManager  = new BuildOrderManager(this->buildManager,this->techManager,this->upgradeManager,this->workerManager,this->supplyManager);
	this->defenseManager     = new DefenseManager(&this->arbitrator);
	this->underAttackManager = new UnderAttackManager(&this->arbitrator);
	this->armyManager				 = new ArmyManager(&this->arbitrator);
	this->informationManager = InformationManager::create();
	this->scoutManager       = new ScoutManager(&this->arbitrator, this->informationManager);
	this->borderManager      = BorderManager::create();
	this->unitGroupManager	 = UnitGroupManager::create();
	this->moodManager				 = new MoodManager();
	this->enhancedUI         = new EnhancedUI();

	this->buildOrderManager->enableDependencyResolver();

	this->underAttackManager->setDefenseManager(this->defenseManager);
	this->underAttackManager->setBaseManager(this->baseManager);

	this->supplyManager->setBuildManager(this->buildManager);
	this->supplyManager->setBuildOrderManager(this->buildOrderManager);

	this->spendManager->setBuildManager(this->buildManager);
	this->spendManager->setBuildOrderManager(this->buildOrderManager);
	this->spendManager->setMoodManager(this->moodManager);
	this->spendManager->setArmyManager(this->armyManager);

	this->techManager->setBuildingPlacer(this->buildManager->getBuildingPlacer());

	this->upgradeManager->setBuildingPlacer(this->buildManager->getBuildingPlacer());

	this->workerManager->setBaseManager(this->baseManager);
	this->workerManager->setBuildOrderManager(this->buildOrderManager);

	this->baseManager->setBuildOrderManager(this->buildOrderManager);
	this->baseManager->setBorderManager(this->borderManager);

	this->defenseManager->setBorderManager(this->borderManager);
	this->defenseManager->setBaseManager(this->baseManager);
	this->defenseManager->setInformationManager(this->informationManager);

	this->spyManager->setInformationManager(this->informationManager);
	this->spyManager->setBuildOrderManager(this->buildOrderManager);

	this->armyManager->setDefenseManager(this->defenseManager);
	this->armyManager->setInformationManager(this->informationManager);
	this->armyManager->setBaseManager(this->baseManager);

	this->moodManager->setInformationManager(this->informationManager);

	lastFrameExpand = 0;
	lastScout = 0;
	//chc
	debugMode = false;
	cleaningPath = false;
	destinationMineralSpotted = false;

	BWAPI::Race race = Broodwar->self()->getRace();
	BWAPI::Race enemyRace = Broodwar->enemy()->getRace();
	BWAPI::UnitType workerType=race.getWorker();

	home=BWTA::getStartLocation(Broodwar->self());
	closest = NULL;

	std::string s1 = race.getName();
	std::string s2 = enemyRace.getName();

	this->buildManager->setDebugMode(false);
	this->scoutManager->setDebugMode(false); //chc
	this->spyManager->setDebugMode(false);
	this->buildOrderManager->setDebugMode(false);

	//make the basic production facility




	if(enemyRace == Races::Terran) // ����
	{
			//�׶��� �⺻���� �����
		//����� cig2013
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,450); //9
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,430); //10
		this->buildOrderManager->buildAdditional(3,UnitTypes::Protoss_Probe,410); //13

		baseManager->expand(405); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,401); //14
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,400);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,395); //16
		this->buildOrderManager->build(3,UnitTypes::Protoss_Gateway,390);
		this->buildOrderManager->build(17,UnitTypes::Protoss_Probe,380); //17








		/*
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,467); //12
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,462); //13
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,460);		//13
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,458); //14
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Assimilator,455); //14
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,453); //15
		this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,450); //15	
		this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,445); //17
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Cybernetics_Core,440); //17
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,435); //18
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Zealot,430); //22
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,428); //22
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Dragoon,404); //26
		*/
		/*
		this->buildOrderManager->build(15,UnitTypes::Protoss_Probe,500);
		//this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,459);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Assimilator,462); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Cybernetics_Core,449);


		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Citadel_of_Adun,402); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Templar_Archives,398);
		this->buildOrderManager->build(19,UnitTypes::Protoss_Probe,500);
		this->buildOrderManager->build(2,UnitTypes::Protoss_Zealot,500);
		this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,459);

		this->buildOrderManager->research(TechTypes::Psionic_Storm,1000);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_High_Templar,599);
		this->buildOrderManager->research(TechTypes::Psionic_Storm,458);

		this->buildOrderManager->upgrade(1, UpgradeTypes::Leg_Enhancements, 391);


		*/

		//baseManager->expand(900);	 //Ȯ��	
		//this->buildOrderManager->build(70,UnitTypes::Protoss_Probe,280);
		//this->buildOrderManager->build(30,UnitTypes::Protoss_Zealot,275);
		//this->buildOrderManager->build(8,UnitTypes::Protoss_Gateway,270);

		/*
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470);//8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);  
		this->buildOrderManager->build(10,UnitTypes::Protoss_Probe,458);  //10
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,456);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,453); //11
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Assimilator,451); 
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,450); //13
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Cybernetics_Core,449);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,447);  //14
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,446); //16
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,445); //17
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,444); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,440); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,437); //19
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Gateway,434);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,431); //21
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Support_Bay,428); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Shuttle,426);  //23
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,424);  //25
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,421); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Reaver,419); //29
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,415); //31
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,412); //33
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,410); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,408); //35


		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Shuttle,405); // 37
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,403); //39
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,395); 

		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Shuttle,390); //41
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,388); //43
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,385); //45
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,383); 
		// ���� ���°ű��� �� �ؼ� ����


		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,380);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Zealot,375);  //49
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Gateway,370);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,365); 

		this->buildOrderManager->buildAdditional(3,UnitTypes::Protoss_Zealot,360);
		this->buildOrderManager->buildAdditional(3,UnitTypes::Protoss_Zealot,355);

		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,350); 
		this->buildOrderManager->buildAdditional(3,UnitTypes::Protoss_Zealot,349);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,345); 
		this->buildOrderManager->buildAdditional(101,UnitTypes::Protoss_Zealot,330); 
		*/

	}


	if(enemyRace == Races::Zerg) // 
	{
		/*

		std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); 

		Position *e = new Position(2300,120);
		(*it)->rightClick(*e);
		if(Broodwar->getFrameCount()>100)
		{
		TilePosition q = (*it)->getTilePosition();
		(*it)->build(BWAPI::Broodwar->self()->getStartLocation(),UnitTypes::Protoss_Pylon);
		}

		this->buildOrderManager->build(5,UnitTypes::Protoss_Probe,470);


		UnitGroup::build
		*/		

		//this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,90);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470);//8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);  
		this->buildOrderManager->build(10,UnitTypes::Protoss_Probe,450);  
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,440);
		this->buildOrderManager->build(13,UnitTypes::Protoss_Probe,430);
		this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,420);
		this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,410);
		this->buildOrderManager->build(14,UnitTypes::Protoss_Probe,400);
		this->buildOrderManager->build(2,UnitTypes::Protoss_Pylon,390);

		this->buildOrderManager->build(15,UnitTypes::Protoss_Probe,380);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Zealot,370);
		this->buildOrderManager->build(4,UnitTypes::Protoss_Gateway,340);
		this->buildOrderManager->build(3,UnitTypes::Protoss_Pylon,330);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,320);
		this->buildOrderManager->build(4,UnitTypes::Protoss_Pylon,310);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,300);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,289);



		//���� ���̸� ����
		/*

		for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
		{			
		if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
		{
		std::set<BWAPI::Unit *>::const_iterator zealot = it;
		BWAPI::Position pos = informationManager->getEnemyStartLocation()->getPosition();


		for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
		{

		if(spendManager->getUnitCount()->zealot >= 11)
		(*zealot)->attack(pos);

		}
		}
		}




		*/
		/*
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,250);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,249);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,248);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,247);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,246);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,245);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,243);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,242);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,240);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,225);

		this->buildOrderManager->buildAdditional(100,UnitTypes::Protoss_Zealot,200);
		*/
	}

	if(enemyRace == Races::Protoss) // 
	{

		//�׶��� �⺻���� �����
		//����� cig2013
			//����� cig2013
	this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,450); //9
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,430); //10
		this->buildOrderManager->buildAdditional(3,UnitTypes::Protoss_Probe,410); //13

		baseManager->expand(405); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,401); //14
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,400);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,395); //16
		this->buildOrderManager->build(3,UnitTypes::Protoss_Gateway,390);
		this->buildOrderManager->build(17,UnitTypes::Protoss_Probe,380); //17





		/*
		//����� cig2013
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,450); //9
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,430); //10
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,410); //11

		baseManager->expand(405); 
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,400);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,395); //13
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,390);
		this->buildOrderManager->build(14,UnitTypes::Protoss_Probe,389); //13
		this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,388); //13

		*/
		/*

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,450); //9
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,440);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,430); //10
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Assimilator,420); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,410); //11
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,409); //12
		this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,409); //14
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Cybernetics_Core,408);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,407); //15
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,406); //16
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,406);  
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,405); //17
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,404); // 18
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,404); // 18
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Dragoon,404); // 20
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Citadel_of_Adun,402); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,401); //21
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Gateway,400);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,399);//23
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Templar_Archives,398);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,397);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Shuttle,397);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Dragoon,396);//25
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,395);//26
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,395); //27
		//this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Dark_Templar,395); //31

		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Gateway,392);
		this->buildOrderManager->upgrade(1, UpgradeTypes::Leg_Enhancements, 391);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Observatory,392);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_High_Templar,392); 
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Zealot,390);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,381);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,281);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,280);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,279);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,269);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,260);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,259);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,258);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,257);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,256);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,255);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,254);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,253);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,252);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,251);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,250);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,150);
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,149);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,148);



		*/
		//��������
		/*
		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Probe,470); //8
		this->buildOrderManager->build(1,UnitTypes::Protoss_Pylon,460);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,450); //9
		this->buildOrderManager->build(1,UnitTypes::Protoss_Gateway,440);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,430); //10
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Assimilator,420); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,410); //11
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,409); //12
		this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,409); //14
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Cybernetics_Core,408);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,407); //15
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,406); //16
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,406);  
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,405); //17
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,404); // 18
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Dragoon,404); // 20
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Citadel_of_Adun,402); 
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,401); //21
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Gateway,400);
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Probe,399);//23
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Templar_Archives,398);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,397);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Dragoon,396);//25
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,395);//26
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,395); //27
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Dark_Templar,395); //31
		*/
		/*
		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Gateway,392);
		this->buildOrderManager->upgrade(1, UpgradeTypes::Leg_Enhancements, 391);


		this->buildOrderManager->buildAdditional(2,UnitTypes::Protoss_Zealot,390);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,388);

		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,381);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,380);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,379);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,376);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,375);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,374);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,373);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,372);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,371);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,370);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,368);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,367);


		this->buildOrderManager->buildAdditional(4,UnitTypes::Protoss_Zealot,365);
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Pylon,363);

		this->buildOrderManager->buildAdditional(101,UnitTypes::Protoss_Zealot,300);

		*/
		//�������峡



		//��ũ��Ʈ��
		/*
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{			
		if ((*its)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
		{
		std::set<BWAPI::Unit *>::const_iterator dark = its;

		BWAPI::Position pos = this->informationManager->getEnemyStartLocation()->getPosition();
		(*dark)->rightClick(pos);



		if((*dark)->isUnderAttack())
		{
		Position *poss = new Position(2100,2100);				
		(*dark)->rightClick(*poss);

		}





		}
		}
		*/
		/*��ø��Ƴ��� chc
		this->workerManager->enableAutoBuild();
		this->workerManager->setAutoBuildPriority(10);
		this->baseManager->setRefineryBuildPriority(30);


		*/



	}
}


Protoss_Multi::~Protoss_Multi()
{
	delete this->buildManager;
	delete this->techManager;
	delete this->upgradeManager;
	delete this->scoutManager;
	delete this->spyManager;
	delete this->workerManager;
	delete this->supplyManager;
	delete this->spendManager;
	delete this->buildOrderManager;
	delete this->baseManager;
	delete this->defenseManager;
	delete this->underAttackManager;
	delete this->armyManager;
	delete this->moodManager;
	InformationManager::destroy();
	BorderManager::destroy();
	UnitGroupManager::destroy();
	delete this->enhancedUI;
}

void Protoss_Multi::onEnd(bool isWinner)
{
	log("onEnd(%d)\n",isWinner);
}

void Protoss_Multi::onFrame()
{
	/*
	Broodwar->drawTextScreen(320,70,"BWAPI::Broodwar->getStartLocations().size():  %d\ ",BWAPI::Broodwar->getStartLocations().size());
	Broodwar->drawTextScreen(320,100,"cig3_fastest_3gate_zealot:  %d\ ",cig3_fastest_3gate_zealot);
	Broodwar->drawTextScreen(320,120,"Protoss_one_Gateway_cig_id:  %d\ ",Protoss_one_Gateway_cig_id);
	Broodwar->drawTextScreen(320,130,"Protoss_two_Gateway_cig_id:  %d\ ",Protoss_two_Gateway_cig_id);
	Broodwar->drawTextScreen(320,140,"Protoss_one_gas_cig_id :  %d\ ",Protoss_one_gas_cig_id);

	Broodwar->drawTextScreen(150,120,"cig_2013_cyber_timing :  %d\ ",cig_2013_cyber_timing);
	Broodwar->drawTextScreen(150,110,"cig_2013_adun_timing :  %d\ ",cig_2013_adun_timing);





	Broodwar->drawTextScreen(320,140,"Protoss_one_gas_cig_id :  %d\ ",Protoss_one_gas_cig_id);

	Broodwar->drawTextScreen(320,170,"Dead Probe  %d\ ",Broodwar->self()->deadUnitCount(BWAPI::UnitTypes::Protoss_Probe));
	*/
	//Broodwar->drawTextScreen(320,180,"myNexusPosition  %d\ ",(*myNexusPosition).x());


	///�١١١١١١١١١١١�����vs���� ������ ���ۡ١١١١١١١١١�

	int Start_Combat_GetId[20] = {0,};
	int Start_Combat_GetId_num=0;


	static int cig2013_1 = Broodwar->getFrameCount();
	static int cig2013_2 = Broodwar->getFrameCount();
	static int cig2013_3 = Broodwar->getFrameCount();


	if(Broodwar->enemy()->getRace() == Races::Protoss)
	{
		if(cig2013_1 == Broodwar->getFrameCount())
		{
			cig2013_1 = cig2013_1 + 4;

			//�ϼ��� ������ 6���� �����̰ų� ����� ���� �� �ߵ�
			if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) ==0)
			{

				//--1.�� ������ ���� �����Ÿ�(132) �ȿ� ������ �����ý��� �ߵ�
				for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
				{
					if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*allMyUnit)->isCompleted())
					{
						for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit !=BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
						{
							if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
							{
								if((*allMyUnit)->getDistance(*allEnemyUnit) < 132)
									Start_Combat_GetId[Start_Combat_GetId_num] = (*allMyUnit)->getID();


							}
						}

						if(Start_Combat_GetId[Start_Combat_GetId_num] !=0)
							Start_Combat_GetId_num++;
					}
				}

				bool total_attack_zealot_cig2013=false;
				//--2 ��ü �������� ��ü �ο��� ���� -


				// ����<=6�� �� +0�������� ��밡��.  
				if(Start_Combat_GetId_num >= BWAPI::Broodwar->enemy()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) && BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) <=6)
					total_attack_zealot_cig2013=true;

				// ����>=7 �� �� +1�������� ��밡��.  
				if(Start_Combat_GetId_num+1 >= BWAPI::Broodwar->enemy()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) && BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >=7)
					total_attack_zealot_cig2013=true;


				//���� �������� �׼�
				if(total_attack_zealot_cig2013 == false)
					for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
					{
						if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*allMyUnit)->isCompleted())
						{
							bool right_combat_cig=false;
							for(int ii=0;ii<20;ii++)
							{
								if((*allMyUnit)->getID() == Start_Combat_GetId[ii])
									right_combat_cig=true;
							}


							/////////////////////

							//������ 8�̻��϶��� ���� �Ȱ�.
							if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) < 8)
								if(right_combat_cig==true && (*allMyUnit)->getDistance(BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition()) > 140)//��������. �����ֺ������� ���� ����
									(*allMyUnit)->move(BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition());
						}
					}

					/*
					Broodwar->drawTextScreen(420,100," %d ",total_attack_zealot_cig2013);
					Broodwar->drawTextScreen(420,120," %d ",Start_Combat_GetId_num);
					Broodwar->drawTextScreen(420,140," %d ",BWAPI::Broodwar->enemy()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot));
					*/




					//������ �ƴ϶������ �� 3~4

					int num_low_hp=0;


					if(cig2013_2 == Broodwar->getFrameCount())
					{
						cig2013_2 = cig2013_2 + 16;
						if(total_attack_zealot_cig2013==true)
						{





							for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
							{
								if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*allMyUnit)->isCompleted())
								{
									bool right_combat_cig=false;
									for(int ii=0;ii<20;ii++)
									{
										if((*allMyUnit)->getID() == Start_Combat_GetId[ii])
											right_combat_cig=true;
									}

									if(right_combat_cig==true)
									{

										//--3 ������ �� �����ϰ� ����
										//���� ���� ����


										//distance ���� : 20~110
										//hitpoint ���� : 0~100
										int min_good_attack_unit_score=999999;
										int enemy_under_attack_score=0;

										std::set<BWAPI::Unit *>::const_iterator attack_good = BWAPI::Broodwar->enemy()->getUnits().begin();

										for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit != BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
										{
											if((*allEnemyUnit)->isUnderAttack())
												enemy_under_attack_score = -5;



											if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) <=4)//4�������� ������ 1.4����
												if(min_good_attack_unit_score > (*allMyUnit)->getDistance(*allEnemyUnit) + (*allEnemyUnit)->getHitPoints() + enemy_under_attack_score)
												{
													min_good_attack_unit_score = (*allMyUnit)->getDistance(*allEnemyUnit) + (*allEnemyUnit)->getHitPoints() + enemy_under_attack_score;
													attack_good = allEnemyUnit;
												}

												if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) > 4)//4�������� ������ �׳ɰ�����
													if(min_good_attack_unit_score > (*allMyUnit)->getDistance(*allEnemyUnit))
													{
														min_good_attack_unit_score = (*allMyUnit)->getDistance(*allEnemyUnit);
														attack_good = allEnemyUnit;
													}





										}

										//!!!!�ϴ��� �׳� �� �ƹ��� �����ϴ� ������ ��...!!
										if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) <=4)//4�������� ������ 1.4����
										{
											if(!(*allMyUnit)->isAttacking())
												(*allMyUnit)->attack((*attack_good));
										}

										if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Zealot) > 4)//4�������� ������ �׳ɰ�����
										{
											if(!(*allMyUnit)->isAttacking())
												(*allMyUnit)->attack((*attack_good)->getPosition());

										}

										//--3 ������ �� �����ϰ� ���� ��

									}
								}
							}
						}
					}



					//--4 ���������� �������� ��� ���ִ� ��Ʈ�� 

					if(cig2013_3 == Broodwar->getFrameCount())
					{
						cig2013_3 = cig2013_3 + 4;

						if(total_attack_zealot_cig2013==true)
						{





							for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
							{
								if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*allMyUnit)->isCompleted())
								{
									bool right_combat_cig=false;
									for(int ii=0;ii<20;ii++)
									{
										if((*allMyUnit)->getID() == Start_Combat_GetId[ii])
											right_combat_cig=true;
									}

									if(right_combat_cig==true)
									{









										if((*allMyUnit)->isUnderAttack() && (*allMyUnit)->getHitPoints() <=36)
										{
											int min_getdis_cig = 999999;
											std::set<BWAPI::Unit *>::const_iterator min_getdis_cig_unit = BWAPI::Broodwar->self()->getUnits().begin();
											//���� ����� ���� ����
											for (std::set<BWAPI::Unit *>::const_iterator allMyUnit2 = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit2 !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit2) 
											{
												if(allMyUnit != allMyUnit2 && (*allMyUnit)->getDistance(*allMyUnit2) < min_getdis_cig)
												{
													min_getdis_cig = (*allMyUnit)->getDistance(*allMyUnit2);
													min_getdis_cig_unit = allMyUnit2;

												}

											}
											if((*min_getdis_cig_unit)->getHitPoints() >= 35) //���� ����� ������ �ǰ� 35���� Ŭ�ų� ���� ������ �ڷλ�		 	
												(*allMyUnit)->move(BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition());					

										}

										////--4 ��

									}
								}
							}




						}


					}
			}
		}
	}





	//�׽�Ʈ.
	static int build_fram213e = Broodwar->getFrameCount();
	if(build_fram213e == Broodwar->getFrameCount()) 
	{
		/////////////�� ��ŸƮ������, ��ũ����Ʈ,  �� �ո��� ������ ����///////////
		Position en_start = this->informationManager->getEnemyStartLocation()->getPosition();
		Position en_choke = BWTA::getNearestChokepoint(en_start)->getCenter();
		Position en_expand = BWTA::getNearestBaseLocation(en_choke)->getPosition();
		Position my_start = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();
		Position my_choke = BWTA::getNearestChokepoint(my_start)->getCenter();
		Position my_ex1 =  BWTA::getNearestBaseLocation(my_choke)->getPosition();




		build_fram213e = build_fram213e+4;   ///��ü�� 4�����Ӹ��� �ѹ��� �����ϰ� ����.  �ý����� �ʹ� ���ſ��� �ٿ�Ǵ� �� ����.    ���� �� �ȿ��� �������� �������ٶ��� 4�������� ����� ����� �������.








		// !!!!!! ����    !! ������ ���� �������� �� �������� �ȸ����� ���� �������� �ʴ´ٰ� �Ǵ��ϴ� ��찡 ����.

		//���常���

		static int build_frame = Broodwar->getFrameCount();
		if(build_frame == Broodwar->getFrameCount())
		{
			build_frame = build_frame + 12 ; //0.5�ʸ��� ����


			/////////////�����佺 �߰� ���� �κ�.

			//Ȯ�����ֱ���� ����

			//			if(Broodwar->enemy()->getRace() == Races::Protoss)
			if(false)		
			{

				//cig2013�١١١١١١١١١��� �Ǵ��ϴ� �� ���ۡ١١١� cig3_fastest_3gate_zealot�� false�� ���ֱ�. �⺻�� true



				// 1. �������� �Ǵ�
				for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit != BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
				{	
					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Gateway)
					{
						if(Protoss_one_Gateway_cig_id == -2)
							Protoss_one_Gateway_cig_id = (*allEnemyUnit)->getID();

						if(Protoss_one_Gateway_cig_id != (*allEnemyUnit)->getID() && Protoss_two_Gateway_cig_id == -2)
							Protoss_two_Gateway_cig_id = (*allEnemyUnit)->getID();


					}


					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Assimilator)
					{
						Protoss_one_gas_cig_id = (*allEnemyUnit)->getID(); 
					}

					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core && cig_2013_cyber_timing ==-2)
					{
						//���̹��׽�ƽ�ھ� �������� �ð� 38�� -- �� ���̹��׽�ƽ�ھ �������� ������ ������ �ǹ���.
						cig_2013_cyber_timing = Broodwar->getFrameCount()/24 - 38 +  (*allEnemyUnit)->getRemainingBuildTime();
					}

					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun && cig_2013_adun_timing ==-2)
					{
						cig_2013_adun_timing = Broodwar->getFrameCount();
					}



				}

				//�ѹ��� ��������
				if(cig0 == false && Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) >=2)
				{
					//������Ʈ �̻� ������ ������ ��������	
					if(Protoss_one_Gateway_cig_id != -2 && Protoss_two_Gateway_cig_id != -2 && Protoss_one_gas_cig_id == -2)
						cig3_fastest_3gate_zealot = true;
					else
						cig3_fastest_3gate_zealot = false;


					if(Protoss_one_Gateway_cig_id == -2 && Protoss_two_Gateway_cig_id == -2 && Protoss_one_gas_cig_id == -2)
						cig3_fastest_3gate_zealot = true; //�ƹ��͵� �������� ��������

					cig0 = true;
				}


				//2. ���̹� �ӵ��� ��ũ�Ǵ� + �Ƶ����� ��ũ�Ǵ�.	 ���� (*allEnemyUnit)->getRemainingBuildTime








				/*
				int cig_2013_cyber_timing;
				int cig_2013_adun_timing;
				*/				









				//cig2013�ڡڡڡڡڡڡڡ��� �Ǵ��ϴ� �� ���ڡڡڡڡڡڡڡ�



				//cig2013
				//1����Ʈ ���Ŀ� ���� ����. 


				if(Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) >=2) //�̰� �����佺 ��ü�� �ش���. 1����Ʈ �������� onstart���� ����.
				{

					if(false) //���� ���� ������ ��
					{
						this->buildOrderManager->build(14,UnitTypes::Protoss_Probe,800); //14

						this->buildOrderManager->build(3,UnitTypes::Protoss_Gateway,785);
						this->buildOrderManager->build(14,UnitTypes::Protoss_Probe,780); //14
						this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,779); //16
						this->buildOrderManager->build(15,UnitTypes::Protoss_Probe,778); //17
						this->buildOrderManager->build(4,UnitTypes::Protoss_Zealot,776); //23
						this->buildOrderManager->build(2,UnitTypes::Protoss_Pylon,775); 
						this->buildOrderManager->build(17,UnitTypes::Protoss_Probe,774); //25



						this->buildOrderManager->build(7,UnitTypes::Protoss_Zealot,772); 
						this->buildOrderManager->build(3,UnitTypes::Protoss_Pylon,771); 
						this->buildOrderManager->build(19,UnitTypes::Protoss_Probe,770);
						this->buildOrderManager->build(10,UnitTypes::Protoss_Zealot,769);







						//this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,774);


						if(Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Probe)>=18)
							cig4_fatest_fix_build_end = true;

						if(cig4_fatest_fix_build_end==true)		
							if(Broodwar->self()->supplyTotal()/2!=200)
							{

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

								}

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.2 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus))  //6�� ���آZ��.
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

								}

							}





							//*****���ֺ��� ���� �� �� ������� ����
							//�⺻ ���ֵ�+����Ʈ���� cig2013

							if(cig4_fatest_fix_build_end)
							{

								//�� ���̹� �ð��� ���� ���κ� �� �̾��ֱ�.
								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 150)
										this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,770);
									else if(cig_2013_cyber_timing <= 180)
										this->buildOrderManager->build(23,UnitTypes::Protoss_Probe,770);
									else if(cig_2013_cyber_timing <= 240)
										this->buildOrderManager->build(23,UnitTypes::Protoss_Probe,770);						
								}

								else 
								{
									this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,770);
								}



								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 200)
										this->buildOrderManager->build(3,UnitTypes::Protoss_Dragoon,769);

								}

								this->buildOrderManager->build(11,UnitTypes::Protoss_Zealot,760); //���� 11���� �̱�. cig�ӽ� 
								this->buildOrderManager->build(43,UnitTypes::Protoss_Probe,750);  //�ո��� ���� �Ծ��� ���� �ϲ� ��  �̳׶��� ���κ� �� 2.5�� �ִ��̰�, 2.3������ ���� �츰 �� ����. 



								this->buildOrderManager->build(100,UnitTypes::Protoss_Zealot,700);
								//	this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.7�� �̱�
								this->buildOrderManager->build(7,UnitTypes::Protoss_Gateway,500);												


								///�⺻���� ���Ϸ� ����~~~

								//���� ����� ���Ϸ� �α��� + ��Ż�α��� - ���� ����� �α��� <= ���� �������� �α��� �ؾ�������. (�׳� ����� �ִ� ���� * 1.9��)

								if(Broodwar->self()->supplyTotal()/2!=200)
								{

									if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
									{
										this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

									}

									if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.4 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus) + 6)  //6�� ���آZ��.
									{
										this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

									}

								}




								//cig2013 ������ ������ �ƹ��͵� ������� �������� ����
								if(Broodwar->self()->gas() > 200)
									this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.6),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.6�� �̱�




								////////////�߰�����.


								/////////////!!!!!!!!!!���̹��� ���� ��������
								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 150)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 3) //������ 3���� �̻��̸� ���� 2�� �ѹ��� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,826);
										}

										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 3) //������ 3���� �̻��̸� �ھ� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,825);
										}


									}
									else if(cig_2013_cyber_timing <= 180)
									{	
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 4) //������ 5���� �̻��̸� ���� 2�� �ѹ��� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,826);
										}

										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 4) //������ 5���� �̻��̸� �ھ� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,825);
										}

									}
									else if(cig_2013_cyber_timing <= 230)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 7) //������ 8���� �̻��̸� ���� 2�� �ѹ��� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,826);
										}

										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >=7) //������ 8���� �̻��̸� �ھ� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,825);
										}
									}

									else if(cig_2013_cyber_timing >230)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 13) //������ 13���� �̻��̸� ���� 2�� �ѹ��� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,826);
										}

										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 13) //������ 13���� �̻��̸� �ھ� ����
										{
											this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,825);
										}



									}
								}

								if(cig_2013_cyber_timing==-2)
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 13) //������ 13���� �̻��̸� ���� 2�� �ѹ��� ����
									{
										this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,826);
									}

									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 13) //������ 13���� �̻��̸� �ھ� ����
									{
										this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,825);
									}


								}


								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 2) //����� 2���� �̻��̸� ���� 2������.
								{
									this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
								}





								//�� �Ƶ� �߰����� �� ������
								if(cig_2013_adun_timing!=-2)
								{
									this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,900);
									this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,899);

									if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core) >= 1) //����� 1���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
									{

										//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

										if(robotics_1 == false)
										{
											this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,898); //
											robotics_1 = true;
										}


										if(robotics_1 == true)
											this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,897);

										this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,880);   


									}
								}








								//������ ����


								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 150)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 3) //����� 1���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
										{

											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}




									}
									else if(cig_2013_cyber_timing <= 180)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 4) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
										{

											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}

									}
									else if(cig_2013_cyber_timing <= 230)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 4) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
										{

											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}
									}
									else if(cig_2013_cyber_timing > 230)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 5) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
										{

											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}
									}
								}


								if(cig_2013_cyber_timing==-2)
								{





									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 5) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
									{

										//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

										if(robotics_1 == false)
										{
											this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
											robotics_1 = true;
										}
										this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
									}
								}






								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observatory) >= 1) //������ �͸� ������ ������ 2���� ����
								{
									this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,799);// ������
								}


								if(BWAPI::Broodwar->self()->supplyUsed()/2 > 90)  //�α����� 90�̻��̸� ������ 4���� ����.
									this->buildOrderManager->build(3,UnitTypes::Protoss_Observer,789); //3��������



								for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3) //���4���� �̻� ������ �������
									{
										if((*its)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
											(*its)->upgrade(UpgradeTypes::Singularity_Charge);  //��� ���

									}


									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 8 && Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 1)  //��� 9���� �̻� �ְ�, �Ƶ� ������ �߾� ����
									{

										if((*its)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun)
											(*its)->upgrade(UpgradeTypes::Leg_Enhancements);  //���� �߾�
									}

								}

								//����� 7���� �̻��̸� �Ƶ� �ø�
								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 6) 
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 0)
										this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);  
								}






							}
					}








					//*****���ֺ��� ���� �� �� ������� ��


					//�١١١١١��Ϲ����� �� ������� ���� �١١١١١١�//




					if(true) //���� ���� �ƴ� ��
					{
						this->buildOrderManager->build(14,UnitTypes::Protoss_Probe,800); //14

						this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,785);
						this->buildOrderManager->build(15,UnitTypes::Protoss_Probe,780); //14
						this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,779); //����

						this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,779); //16
						this->buildOrderManager->build(16,UnitTypes::Protoss_Probe,778); //18

						if(cig_2013_cyber_timing!=-2)
						{
							if(cig_2013_cyber_timing <= 200)
							{
								this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,776);
								this->buildOrderManager->build(3,UnitTypes::Protoss_Zealot,775); //21
							}
							else if(cig_2013_cyber_timing > 200)
							{
								this->buildOrderManager->build(3,UnitTypes::Protoss_Zealot,776); //21
								this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,775);
							}

						}
						if(cig_2013_cyber_timing==-2)
						{
							this->buildOrderManager->build(3,UnitTypes::Protoss_Zealot,776); //21
							this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,775);
						}


						this->buildOrderManager->build(18,UnitTypes::Protoss_Probe,774); //23
						this->buildOrderManager->build(5,UnitTypes::Protoss_Zealot,490); //23
						this->buildOrderManager->build(2,UnitTypes::Protoss_Pylon,489); //23






						//this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,774);


						if(Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Probe)>=18)
							cig4_slow_fix_build_end = true;

						if(cig4_slow_fix_build_end==true)		
							if(Broodwar->self()->supplyTotal()/2!=200)
							{

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

								}

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.3 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus))  //6�� ���آZ��.
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

								}

							}





							//*****���ֺ��� ���� �� �� ������� ����
							//�⺻ ���ֵ�+����Ʈ���� cig2013

							if(cig4_slow_fix_build_end == true)
							{


								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 160)
									{
										this->buildOrderManager->build(5,UnitTypes::Protoss_Zealot,770);
										this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,769);
										this->buildOrderManager->build(2,UnitTypes::Protoss_Dragoon,768);

									}
									else if(cig_2013_cyber_timing <= 220)	
									{
										this->buildOrderManager->build(6,UnitTypes::Protoss_Zealot,770);
										this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,769);
										this->buildOrderManager->build(3,UnitTypes::Protoss_Dragoon,768);

									}
									else if(cig_2013_cyber_timing > 220)	
									{
										this->buildOrderManager->build(6,UnitTypes::Protoss_Zealot,770);
										this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,769);
										this->buildOrderManager->build(5,UnitTypes::Protoss_Dragoon,768);

									}					
								}

								if(cig_2013_cyber_timing==-2)
								{
									this->buildOrderManager->build(6,UnitTypes::Protoss_Zealot,770);
									this->buildOrderManager->build(24,UnitTypes::Protoss_Probe,769);
									this->buildOrderManager->build(5,UnitTypes::Protoss_Dragoon,768);

								}



								this->buildOrderManager->build(43,UnitTypes::Protoss_Probe,750);  //�ո��� ���� �Ծ��� ���� �ϲ� ��  �̳׶��� ���κ� �� 2.5�� �ִ��̰�, 2.3������ ���� �츰 �� ����. 






								this->buildOrderManager->build(100,UnitTypes::Protoss_Zealot,700);
								//	this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.7�� �̱�
								this->buildOrderManager->build(8,UnitTypes::Protoss_Gateway,500);												


								///�⺻���� ���Ϸ� ����~~~

								//���� ����� ���Ϸ� �α��� + ��Ż�α��� - ���� ����� �α��� <= ���� �������� �α��� �ؾ�������. (�׳� ����� �ִ� ���� * 1.9��)

								if(Broodwar->self()->supplyTotal()/2!=200)
								{

									if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
									{
										this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

									}

									if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.3 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus) + 6)  //6�� ���آZ��.
									{
										this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

									}

								}




								//cig2013 ������ ������ �ƹ��͵� ������� �������� ����
								if(Broodwar->self()->gas() > 200)
									this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.6),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.6�� �̱�




								////////////�߰�����.


								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 200)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 4) //����� 3���� �̻��̸� ���� 2�� �ѹ��� ����
											this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
									}
									else if(cig_2013_cyber_timing > 200)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 6) //�����6���� �̻��̸� ���� 2�� �ѹ��� ����
											this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
									}

								}
								if(cig_2013_cyber_timing==-2)
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 6) //�����6���� �̻��̸� ���� 2�� �ѹ��� ����
										this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
								}





								//�� �Ƶ� �߰����� �� ������
								if(cig_2013_adun_timing!=-2)
								{
									this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,900);
									this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,899);

									if(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core) >= 1) //����� 1���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����  
									{

										//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

										if(robotics_1 == false)
										{
											this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,898); //
											robotics_1 = true;
										}


										if(robotics_1 == true)
											this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,897);

										this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,880);   


									}
								}





								if(cig_2013_cyber_timing!=-2)
								{
									if(cig_2013_cyber_timing <= 160)
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 4) //����� 3���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
										{
											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}


									}
									else if(cig_2013_cyber_timing <= 220)	
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 4) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
										{
											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}

									}
									else if(cig_2013_cyber_timing > 220)	
									{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 6) //����� 6���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
										{
											//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

											if(robotics_1 == false)
											{
												this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
												robotics_1 = true;
											}
											this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
										}


									}					
								}

								if(cig_2013_cyber_timing==-2)
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 6) //����� 6���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
									{
										//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

										if(robotics_1 == false)
										{
											this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
											robotics_1 = true;
										}
										this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
									}


								}








								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observatory) >= 1) //������ �͸� ������ ������ 2���� ����
								{
									this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,799);// ������
								}


								if(BWAPI::Broodwar->self()->supplyUsed()/2 > 90)  //�α����� 90�̻��̸� ������ 4���� ����.
									this->buildOrderManager->build(3,UnitTypes::Protoss_Observer,789); //3��������



								for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 2) //��� 2���� �̻� ������ �������
									{
										if((*its)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
											(*its)->upgrade(UpgradeTypes::Singularity_Charge);  //��� ���

									}


									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 9 && Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 1)  //��� 9���� �̻� �ְ�, �Ƶ� ������ �߾� ����
									{

										if((*its)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun)
											(*its)->upgrade(UpgradeTypes::Leg_Enhancements);  //���� �߾�
									}

								}

								//����� 7���� �̻��̸� �Ƶ� �ø�
								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 7) 
								{
									if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 0)
										this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);  //���÷� ��ũ�� �κ�ƽ�� ��ũ���� ����
								}






							}
					}



					//�ڡڡڡڡڡ��Ϲ����� �� ������� �� �ڡڡڡڡڡڡڡڡ�//





					////////////*********���� �ʹݷ��� �Ǵ� ��

					//cig2013 
					//�� ��ũ�϶� ����/////
					/*
					for (std::set<BWAPI::Unit *>::const_iterator t = Broodwar->enemy()->getUnits().begin(); t != BWAPI::Broodwar->enemy()->getUnits().end(); ++t)
					{

					if((*t)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun || (*t)->getType() == BWAPI::UnitTypes::Protoss_Templar_Archives)   
					{
					this->buildOrderManager->build(1,UnitTypes::Protoss_Robotics_Facility,860);
					this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,859);
					this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,858);
					}




					if((*t)->getType() == BWAPI::UnitTypes::Protoss_Templar_Archives)   
					{

					//cig2013 �̰� ��?
					this->armyManager->observer = false;
					armyManager->observer = false;
					}

					//�� ��ũ�϶� ��/////


					}
					*/

					//Ȯ�� ���ֱ� ��




					/* cig2013

					if(my_auto_build) //���� ������尡 ���� �־�� �����.
					{

					//���� �����. ��Ƽ ���� ���� ����  �׶����� ��Ƽ �԰� ���� ���� ���� ����

					//�⺻����.  ���κ�, ����, ���, ����Ʈ����
					this->buildOrderManager->build(42,UnitTypes::Protoss_Probe,750);  //�ո��� ���� �Ծ��� ���� �ϲ� ��  �̳׶��� ���κ� �� 2.5�� �ִ��̰�, 2.3������ ���� �츰 �� ����. 
					this->buildOrderManager->build(100,UnitTypes::Protoss_Zealot,700);
					this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.7�� �̱�
					this->buildOrderManager->build(8,UnitTypes::Protoss_Gateway,500);

					/////////////

					///�⺻���� ���Ϸ� ����~~~

					//���� ����� ���Ϸ� �α��� + ��Ż�α��� - ���� ����� �α��� <= ���� �������� �α��� �ؾ�������. (�׳� ����� �ִ� ���� * 1.9��)

					if(Broodwar->self()->supplyTotal()/2!=200)
					{
					if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
					{
					this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

					}

					if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.4 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus) + 6)  //5�� ���آZ��.
					{
					this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

					}


					}
					///�⺻���� ���Ϸ� ��~~~





					//�߰�����.

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 2) //����� 3���� �̻��̸� ���� ����
					{
					this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
					}

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
					{
					//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);
					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 0)
					this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);  //���÷� ��ũ�� �κ�ƽ�� ��ũ���� ����
					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Templar_Archives) == 0)
					this->buildOrderManager->build(1,UnitTypes::Protoss_Templar_Archives,800);

					if(robotics_1 == false)
					{
					this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
					robotics_1 = true;
					}
					this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
					}

					if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Robotics_Facility) != 1 && BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Robotics_Facility) >= 1) //�κ�ƽ�� �۽Ǹ�Ƽ ������ ��Ʋ ����
					{
					if(shuttle_1 == false)
					{
					this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Shuttle,950);
					shuttle_1 = true;
					}
					}

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observatory) >= 1) //������ �͸� ������ ������ 2���� ����
					{
					this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,770);// ������
					}
					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Shuttle) >= 1 && BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Templar_Archives) >= 1) //��Ʋ 1�� �� ���÷���ī�̺� ������ �������÷� 4���� ����
					//if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 4) //����� 5���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
					this->buildOrderManager->build(4,UnitTypes::Protoss_High_Templar,760);


					if(BWAPI::Broodwar->self()->supplyUsed()/2 >80)  //�α����� 80�̻��̸� ������ 4���� ����.
					this->buildOrderManager->build(4,UnitTypes::Protoss_Observer,755);



					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3) //��� 4���� �̻� ������ �������
					{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
					(*its)->upgrade(UpgradeTypes::Singularity_Charge);  //��� ���

					}


					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 4)  //��� 5���� �̻� ������ �߾�, ����� ����
					{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Templar_Archives)
					(*its)->research(TechTypes::Psionic_Storm);  //���� ��


					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun)
					(*its)->upgrade(UpgradeTypes::Leg_Enhancements);  //���� �߾�
					}
					}
					}

					*/


				}
			}





			/////////////�����佺 �߰� ���� �κ�  ��



			//���� Ȯ�����ֱ���� ����	



			if(Broodwar->enemy()->getRace() == Races::Zerg)
			{	
				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 11 && !my_expand_true) //��ũ�� 2���� �̻� �ְ� Ȯ���� ������ Ȯ�����ֱ�
				{
					baseManager->expand(1100);
					my_auto_build = true;
					my_expand_true = true;
					this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,850);
					this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,843);
				}


				///Ȯ�����ֱ� ��

				if(my_auto_build) //���� ������尡 ���� �־�� �����.
				{	

					//���� �����. ��Ƽ ���� ���� ����  �׶����� ��Ƽ �԰� ���� ���� ���� ����

					//�⺻����.  ���κ�, ����, ���, ����Ʈ����
					this->buildOrderManager->build(42,UnitTypes::Protoss_Probe,750);  //�ո��� ���� �Ծ��� ���� �ϲ� ��  �̳׶��� ���κ� �� 2.5�� �ִ��̰�, 2.3������ ���� �츰 �� ����. 
					this->buildOrderManager->build(100,UnitTypes::Protoss_Zealot,700);
					this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.7�� �̱�
					this->buildOrderManager->build(8,UnitTypes::Protoss_Gateway,500);

					/////////////


					///�⺻���� ���Ϸ� ����~~~

					//���� ����� ���Ϸ� �α��� + ��Ż�α��� - ���� ����� �α��� <= ���� �������� �α��� �ؾ�������. (�׳� ����� �ִ� ���� * 1.9��)

					if(Broodwar->self()->supplyTotal()/2!=200)
					{
						if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
						{
							this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

						}

						if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.4 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus) + 6)  //5�� ���آZ��.
						{
							this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

						}


					}
					///�⺻���� ���Ϸ� ��~~~





					//�߰�����.

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 1) //����� 1���� �̻��̸� ���� ����
					{
						this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
					}

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
					{
						this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);
						//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

						if(robotics_1 == false)
						{
							this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
							robotics_1 = true;
						}
						this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
					}



					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observatory) >= 1) //������ �͸� ������ ������ 2���� ����
					{
						this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,770);// ������
					}


					if(BWAPI::Broodwar->self()->supplyUsed()/2 >80)  //�α����� 80�̻��̸� ������ 3���� ����.
						this->buildOrderManager->build(3,UnitTypes::Protoss_Observer,755);



					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
						if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3) //��� 4���� �̻� ������ �������
						{
							if((*its)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
								(*its)->upgrade(UpgradeTypes::Singularity_Charge);  //��� ���

						}


						if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 5)  //��� 6���� �̻� ������ �߾�, ����� ����
						{
							if((*its)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun)
								(*its)->upgrade(UpgradeTypes::Leg_Enhancements);  //���� �߾�
						}
					}
				}





			}








			///////////���� ���� ��



			//////////////!!!!!!�׶����� ����


			//�׶� Ȯ�� ������� Ȱ��ȭ Ÿ�̹� ����
			if(Broodwar->enemy()->getRace() == Races::Terran || Broodwar->enemy()->getRace() == Races::Protoss)
			{

				//����Ʈ 2���̻��� ���� ���� Ȱ��ȭŸ�̹�
				if(Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway)>=3)
				{
					this->buildOrderManager->build(17,UnitTypes::Protoss_Probe,789); //17				
					this->buildOrderManager->build(2,UnitTypes::Protoss_Gateway,785);
					
					this->buildOrderManager->build(1,UnitTypes::Protoss_Zealot,779); //19	
					this->buildOrderManager->build(18,UnitTypes::Protoss_Probe,778); //20

					this->buildOrderManager->build(2,UnitTypes::Protoss_Zealot,777); //22
					this->buildOrderManager->build(20,UnitTypes::Protoss_Probe,776); //24
					this->buildOrderManager->build(3,UnitTypes::Protoss_Zealot,774); //26
					this->buildOrderManager->build(2,UnitTypes::Protoss_Pylon,773); //	
					this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,772); //����						
					this->buildOrderManager->build(1,UnitTypes::Protoss_Cybernetics_Core,771); //23








					//this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,774);


					if(Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core) >=1)
						cig5_terran_start_auto_build = true;

					if(cig5_terran_start_auto_build==true)		
						if(Broodwar->self()->supplyTotal()/2!=200)
						{

							if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
							{
								this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

							}

							if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.2 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus))  //6�� ���آZ��.
							{
								this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

							}

						}





						//*****���ֺ��� ���� �� �� ������� ����
						//�⺻ ���ֵ�+����Ʈ���� cig2013

						if(cig5_terran_start_auto_build==true)
						{

							this->buildOrderManager->build(20,UnitTypes::Protoss_Probe,762);
							this->buildOrderManager->build(6,UnitTypes::Protoss_Zealot,761);
							this->buildOrderManager->build(21,UnitTypes::Protoss_Probe,760);
							this->buildOrderManager->build(7,UnitTypes::Protoss_Zealot,759);


							this->buildOrderManager->build(43,UnitTypes::Protoss_Probe,750);  //�ո��� ���� �Ծ��� ���� �ϲ� ��  �̳׶��� ���κ� �� 2.5�� �ִ��̰�, 2.3������ ���� �츰 �� ����. 



							this->buildOrderManager->build(100,UnitTypes::Protoss_Zealot,700);
							//this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.7�� �̱�
							this->buildOrderManager->build(8,UnitTypes::Protoss_Gateway,500);												


							///�⺻���� ���Ϸ� ����~~~

							//���� ����� ���Ϸ� �α��� + ��Ż�α��� - ���� ����� �α��� <= ���� �������� �α��� �ؾ�������. (�׳� ����� �ִ� ���� * 1.9��)

							if(Broodwar->self()->supplyTotal()/2!=200)
							{

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2 <= (Broodwar->self()->incompleteUnitCount(UnitTypes::AllUnits) - Broodwar->self()->incompleteUnitCount(UnitTypes::Buildings)) * 1.9)
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000);

								}

								if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Pylon)*8 + Broodwar->self()->supplyTotal()/2 - Broodwar->self()->supplyUsed()/2  < BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) * 2.4 + BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Nexus) + 6)  //6�� ���آZ��.
								{
									this->buildOrderManager->build(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) + 1 , UnitTypes::Protoss_Pylon,1000); // ���Ϸ� �ϳ� �����

								}

							}

											//cig2013 ������ ������ �ƹ��͵� ������� �������� ����
			

							/*
							int gas_carrying_probe_num=0;
	for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{
			if((*its)->getType() == BWAPI::UnitTypes::Protoss_Probe)
			{
				if((*its)->isCarryingGas())
					gas_carrying_probe_num++;

			}
	}

							Broodwar->drawTextScreen(100,250,"%d",gas_carrying_probe_num);
						*/




							
							if(aaab == true) //�ȵ�θ޴�
							{
								Broodwar->drawTextScreen(120,120,"Andromeda");
								if(Broodwar->self()->gas() > 200)
									this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*0.7),UnitTypes::Protoss_Dragoon,720); //����� ������ 0.7�� �̱�
							}
							else
							{
									if(Broodwar->self()->gas() > 200)
									this->buildOrderManager->build((int)(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot)*1.6),UnitTypes::Protoss_Dragoon,720); //����� ������ 1.6�� �̱�

							}


						


							////////////�߰�����.


							if(aaab == true)
							{
							
							if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 4) //����� 4���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
							{
								//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

								if(robotics_1 == false)
								{
									this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
									robotics_1 = true;
								}
								this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
							}
							}
							
							if(aaab == false)
							{
										if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 3) //����� 3���� �̻��̸� ���� 2�� �ѹ��� ����
							{
								this->buildOrderManager->build(2,UnitTypes::Protoss_Assimilator,826);
							}




							if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 7) //����� 7���� �̻��̸�  �κ�ƽ��, �������͸�, �Ƶ�, ���÷� ��ī�̺� ����
							{
								//this->buildOrderManager->build(1,UnitTypes::Protoss_Assimilator,822);

								if(robotics_1 == false)
								{
									this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Robotics_Facility,790); //
									robotics_1 = true;
								}
								this->buildOrderManager->build(1,UnitTypes::Protoss_Observatory,780);   
							}

							}


							if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observatory) >= 1) //������ �͸� ������ ������ 2���� ����
							{
								this->buildOrderManager->build(2,UnitTypes::Protoss_Observer,799);// ������
							}


							if(BWAPI::Broodwar->self()->supplyUsed()/2 > 90)  //�α����� 90�̻��̸� ������ 4���� ����.
								this->buildOrderManager->build(3,UnitTypes::Protoss_Observer,789); //3��������



							for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
							{
								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 2) //��� 2���� �̻� ������ �������
								{
									if((*its)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core)
										(*its)->upgrade(UpgradeTypes::Singularity_Charge);  //��� ���

								}


								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 9 && Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 1)  //��� 10���� �̻� �ְ�, �Ƶ� ������ �߾� ����
								{

									if((*its)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun)
										(*its)->upgrade(UpgradeTypes::Leg_Enhancements);  //���� �߾�
								}

							}

							//����� 8���� �̻��̸� �Ƶ� �ø�
								if(aaab == true)
									{
							if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 5) 
							{
								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 0)
									this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);  //���÷� ��ũ�� �κ�ƽ�� ��ũ���� ����
							}
							}
							if(aaab == false)
							{
							if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 8) 
							{
								if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Citadel_of_Adun) == 0)
									this->buildOrderManager->build(1,UnitTypes::Protoss_Citadel_of_Adun,812);  //���÷� ��ũ�� �κ�ƽ�� ��ũ���� ����
							}
							}

						







						}

				}
			}




			////////////�׶� ���� ��




		}


		//////////////////////////////////////////****���� ��



		//////�츮���� �����ϰ� �ִ� ���� �����ֱ�.

		//	total_attack=true;
		//if(total_attack = true)

		/*for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{		

		if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
		{
		BWAPI::Broodwar->drawLineMap((*its)->getPosition().x(), (*its)->getPosition().y(), (*its)->getTargetPosition().x(), (*its)->getTargetPosition().y(), BWAPI::Colors::Green);
		}

		}*/


		/****�Ѱ����ϱ�***////


		/******�츮�� �ڽŰ��ý��� ���� *****///



		for(int i=0; i<150; i++)  //�迭�� �ʱ�ȭ
		{
			self_attack_unit_attak_power[i] = 0;
			self_attack_unit_position_x[i] = 0; 
			self_attack_unit_position_y[i] = 0;


			confidence[i] = 0;
			confidence_enemy[i] = 0;
			enemy_attack_unit_position_x[i] = 0;
			enemy_attack_unit_position_y[i] = 0;
			enemy_attack_unit_attak_power[i] = 0;

		}


		//******�١١١١ٿ츮��� �� �������� ��ġ, ���ݷ� ���� ���� �١١١١١١�
		//int unit_self=0; //���Ƿ� �ű� �츮�� ���ݷ� 16�̻��� ���ֹ�ȣ 0���ͽ���

		//int unit_s=0;
		int unit_e=0;
		int low_confidence_unit=0; //�ڽŰ� ���Ƽ� �������� �ֵ� ���� ���ֱ�
		std::set<BWAPI::Unit *>::const_iterator confidence_nice_unit = BWAPI::Broodwar->self()->getUnits().begin(); //�ڽŰ� ���� ���� ã������
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{
			if((*its)->getType().canAttack() && (*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
			{

				////////////�� ���� �ֺ��� ������ �ڽŰ� �϶�
				for (std::set<BWAPI::Unit *>::const_iterator enemys = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys)
				{	

					//�츮�� �ڽŰ� ���߱�.
					//��Ŀ�϶��� �ϴ��� ����.. ���߿� ��Ŀ��������Ͽ� ����
					if((*enemys)->getType().canAttack() && (*enemys)->getType().groundWeapon().damageAmount() >= 7 || (*enemys)->getType() == BWAPI::UnitTypes::Terran_Marine || (*enemys)->getType() == BWAPI::UnitTypes::Zerg_Zergling && !((*enemys)->getType() == BWAPI::UnitTypes::Terran_Bunker)) // �������� 10���� ũ�ٸ� . �������� �����ϱ� ����
					{
						if(130>(*its)->getDistance(*enemys))
						{
							confidence[unit_e] = confidence[unit_e] - (double)(*enemys)->getType().groundWeapon().damageAmount()/(*enemys)->getType().groundWeapon().damageCooldown();
							//	unit_e++;
						}
					}


				}

				////////////�� ���� �ֺ��� ������ �ڽŰ� �϶� ��


				//�츮 �� ���� �ֺ��� ������ �ڽŰ� ���
				for (std::set<BWAPI::Unit *>::const_iterator its2 = BWAPI::Broodwar->self()->getUnits().begin(); its2 != BWAPI::Broodwar->self()->getUnits().end(); ++its2)
				{
					if((*its2)->getType().canAttack() && (*its2)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
					{
						if(130>(*its)->getDistance(*its2))
						{
							confidence[unit_e] = confidence[unit_e] + (double)(*its2)->getType().groundWeapon().damageAmount()/(*its2)->getType().groundWeapon().damageCooldown();
							//unit_s++;
						}

					}
				}
				////�츮 �� ���� �ֺ��� ������ �ڽŰ� ��� ��




				//�츮�� �ڽŰ� ���
				Position q=(*its)->getPosition(); 
				//Broodwar->drawText(CoordinateType::Map,q.x(),q.y(),"%d", (int)(confidence[unit_e]*100));



				//// ���� �ڽŰ��� ū�� ã�� ����///
				int confidence_max=0;
				for(int i=0; i<150 ;i++)
				{
					if(confidence[i] >= confidence_max)
						confidence_max = i;
				}

				////���� �ڽŰ��� ū�� ã�� ��///

				int search_confidence_nice_unit_num=0;
				for (std::set<BWAPI::Unit *>::const_iterator its3 = BWAPI::Broodwar->self()->getUnits().begin(); its3 != BWAPI::Broodwar->self()->getUnits().end(); ++its3)
				{			
					if((*its3)->getType().groundWeapon().damageAmount() >= 8 && (*its3)->getType().canAttack()) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
					{
						if(search_confidence_nice_unit_num == confidence_max)
							confidence_nice_unit = its3;
						search_confidence_nice_unit_num++;
					}

				}


				if(Broodwar->enemy()->getRace() == Races::Zerg)//�������� ��� -180���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -200)
					{
						low_confidence_unit++; //�ڽŰ� �����ֵ� ���� ++
						run_away[unit_e]=true;

					}
				}

				if(Broodwar->enemy()->getRace() == Races::Terran)//�׶������� ��� -200���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -200)
					{
						low_confidence_unit++; //�ڽŰ� �����ֵ� ���� ++
						run_away[unit_e]=true;

					}
				}

				if(Broodwar->enemy()->getRace() == Races::Protoss)//�������� ��� -120���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -120)
					{
						low_confidence_unit++; //�ڽŰ� �����ֵ� ���� ++
						run_away[unit_e]=true;

					}
				}
				//���������ϱ�
				/*
				if(Broodwar->enemy()->getRace() == Races::Zerg)//�������� ��� -180���� �ڽŰ��� ������ ������
				{
				if((int)(confidence[unit_e]*100) < -200)
				{
				//q=(*its)->getPosition();
				Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Red,false);
				BWAPI::Position *confidence_nice_position = new Position(0,0);
				*confidence_nice_position = (*confidence_nice_unit)->getPosition();
				(*its)->move(*confidence_nice_position);

				low_confidence_unit++; //�ڽŰ� �����ֵ� ���� ++

				}

				}
				*/
				///���������ϱ�
				unit_e++;
			}

		}


		///�ֵ� �������� �ϱ�..  �� 5���� �̻� �������� �����Ǹ� �������� �ʴ´�.
		unit_e = 0;  //0���� �ʱ�ȭ��������Ѵ�.
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{
			if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
			{

				if(Broodwar->enemy()->getRace() == Races::Zerg)//�������� ��� -200���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -200 && low_confidence_unit <=2)  //3���� �̻��̸� �������.. ���߿� ����
					{
						Position q=(*its)->getPosition(); 
						//Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Red,false);
						BWAPI::Position *confidence_nice_position = new Position(0,0);
						*confidence_nice_position = (*confidence_nice_unit)->getPosition();
						//(*its)->move(*confidence_nice_position);
					}

					/*
					if(!((int)(confidence[unit_e]*100) < -200 && low_confidence_unit <=4) && run_away[unit_e] == true) // ���� �ڽŰ��� ���������� ������ �ְ� ���� �������� ���̶�� �ٽ� �����ϰ� �ض�.
					{
					(*its)->attack(this->informationManager->getEnemyStartLocation()->getPosition());
					run_away[unit_e]=false; //���� false
					}
					*/

				}


				if(Broodwar->enemy()->getRace() == Races::Terran)//�׶����� ��� -200���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -200 && low_confidence_unit <=3)  //4���� �̻��̸� ���þȵ�. ���߿� ����
					{
						Position q=(*its)->getPosition(); 
						//	Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Red,false);
						BWAPI::Position *confidence_nice_position = new Position(0,0);
						*confidence_nice_position = (*confidence_nice_unit)->getPosition();
						//	(*its)->move(*confidence_nice_position);
					}
				}

				if(Broodwar->enemy()->getRace() == Races::Protoss)//�����佺���� ��� -120���� �ڽŰ��� ������ ������
				{
					if((int)(confidence[unit_e]*100) < -120 && low_confidence_unit <=3)  //4���� �̻��̸� ���þȵ�. ���߿� ����
					{
						Position q=(*its)->getPosition(); 
						//	Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Red,false);
						BWAPI::Position *confidence_nice_position = new Position(0,0);
						*confidence_nice_position = (*confidence_nice_unit)->getPosition();
						//(*its)->move(*confidence_nice_position);
					}
				}



				//if(Broodwar->enemy()->getRace() == Races::Zerg)//�������� ��� -200���� �ڽŰ��� ������ ������
				unit_e++;

			}
		}


		/////************�츮�� �ڽŰ��ý��۳�****///////////
		//////




		//�������÷� 4������ ��� ��Ʋ�� ������ Ȯ���ϱ�.~! ����//

		/*
		int high_templer_loaded_num=0;

		for (std::set<BWAPI::Unit *>::const_iterator its2 = BWAPI::Broodwar->self()->getUnits().begin(); its2 != BWAPI::Broodwar->self()->getUnits().end(); ++its2)
		{
		if((*its2)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
		{
		if((*its2)->isLoaded())
		high_templer_loaded_num++;
		}
		}

		//	Broodwar->drawTextScreen(100,110,"is loaded : %d", testttt);

		//�������÷� 4������ ��� ��Ʋ�� ������ Ȯ���ϱ�.~! ��//




		//�������÷� 4������ �� ������ true�� ���ش�.
		if(high_templer_loaded_num==4)
		high_templer_loaded_complete = true; 

		*/
		if(BWAPI::Broodwar->self()->supplyUsed()/2 > 185)
			high_templer_loaded_complete = true;




		//////****���� �ڽŰ��ý��� + �������÷����� ����***////


		int psionic_storm_attackedX[100] = {0,}; //�������÷����� ���̿��� ������ ���� ��� ���� ���� ����
		int psionic_storm_attackedY[100] = {0,};
		int psionic_storm_num=0; //���̿��н����� ���� �� Ƚ��  

		//�������÷� ��Ʋ ��Ʈ�ѿ� �ʿ��� ������
		bool its_right_click_enemys = false;   
		bool its_unload_its2 = false;
		std::set<BWAPI::Unit *>::const_iterator its_right_click_enemys_unit = BWAPI::Broodwar->enemy()->getUnits().begin();
		////

		unit_e=0; //0���� �ʱ�ȭ�������.
		std::set<BWAPI::Unit *>::const_iterator confidence_nice_enemy_unit = BWAPI::Broodwar->enemy()->getUnits().begin(); //���� �ڽŰ� ���� ���� ã������
		int confidence_nice_enemy_unit_confidence_num=0;
		//4�����ӿ� �ѹ��� ���ư�����
		static int fram3__2 = Broodwar->getFrameCount();
		if(fram3__2 == Broodwar->getFrameCount())
		{
			fram3__2=fram3__2 + 4;
			for (std::set<BWAPI::Unit *>::const_iterator enemys = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys)
			{
				if((*enemys)->getType().groundWeapon().damageAmount() >= 5 && (*enemys)->getType().canAttack() && (*enemys)->getType().canMove() &&  (*enemys)->getType() != BWAPI::UnitTypes::Protoss_Probe && (*enemys)->getType() != BWAPI::UnitTypes::Zerg_Drone && (*enemys)->getType() != BWAPI::UnitTypes::Terran_SCV) // �������� 5���� ũ�ٸ�...... ���ָ� ���õ�. �ϲ� ����
				{
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{

						//���� �ڽŰ� ���߱�.
						//��Ŀ�϶��� �ϴ��� ����.. ���߿� ��Ŀ��������Ͽ� ����
						if((*its)->getType().canAttack() && (*its)->getType().groundWeapon().damageAmount() >= 7) // �������� 10���� ũ�ٸ� . �������� �����ϱ� ����
						{
							if(130>(*enemys)->getDistance(*its))
							{
								confidence_enemy[unit_e] = confidence_enemy[unit_e] - (double)(*its)->getType().groundWeapon().damageAmount()/(*its)->getType().groundWeapon().damageCooldown();
								//	unit_e++;
							}
						}
					}
					///���� �ڽŰ� ���߱� ��



					//���� ���� �ֺ��� ���� ������ �ڽŰ� ��� ����   - �ǹ� ���� ���ָ� ���������.
					for (std::set<BWAPI::Unit *>::const_iterator enemys2 = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys2 != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys2)
					{
						if((*enemys2)->getType().canAttack() && (*enemys2)->getType().groundWeapon().damageAmount() >= 5 && (*enemys2)->getType().canMove() && (*enemys2)->getType() != BWAPI::UnitTypes::Protoss_Probe && (*enemys2)->getType() != BWAPI::UnitTypes::Zerg_Drone && (*enemys2)->getType() != BWAPI::UnitTypes::Terran_SCV) // �������� 5���� ũ�ٸ�
						{
							if(130>(*enemys)->getDistance(*enemys2))
							{
								confidence_enemy[unit_e] = confidence_enemy[unit_e] + (double)(*enemys2)->getType().groundWeapon().damageAmount()/(*enemys2)->getType().groundWeapon().damageCooldown();
								//unit_s++;
							}

						}
					}

					//���� ���� �ֺ��� ���� ������ �ڽŰ� ��� ��




					////���� ���� �ڽŰ��� ū�� ã�� ����///
					int confidence_max=0;
					for(int i=0; i<150 ;i++)
					{
						if(confidence_enemy[i] >= confidence_max)
							confidence_max = i;
					}

					////���� ���� �ڽŰ��� ū�� ã�� ��///

					int search_confidence_nice_unit_num=0;
					for (std::set<BWAPI::Unit *>::const_iterator enemys2 = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys2 != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys2)
					{			
						if((*enemys2)->getType().groundWeapon().damageAmount() >= 5 && (*enemys2)->getType().canAttack() && (*enemys2)->getType().canMove() &&  (*enemys2)->getType() != BWAPI::UnitTypes::Protoss_Probe && (*enemys2)->getType() != BWAPI::UnitTypes::Zerg_Drone && (*enemys2)->getType() != BWAPI::UnitTypes::Terran_SCV) // �������� 5���� ũ�ٸ�...... ���ָ� ���õ�. �ϲ� ����
						{
							if(search_confidence_nice_unit_num == confidence_max)
							{
								confidence_nice_enemy_unit_confidence_num = confidence_max;
								confidence_nice_enemy_unit = enemys2;
							}
							search_confidence_nice_unit_num++;
						}

					}




					//** �Ѱ����� �� ��Ʋ���� ������ ��Ʈ�� 1.  for�� �ȿ� ���� �ֱ� ������ for�� �ۿ��� �̰��� �� �������.

					//if(total_attack) //�Ѱ����̸� 
					/*
					if(high_templer_loaded_complete)  //4���� �� �¿� ��
					{
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Shuttle) //��Ʋ����
					{
					if((*its)->getShields() < 30)
					;
					//(*its)->unload(*its2);  //���尡 30���� ������ �������÷� �� ������
					else if((*its)->getDistance(*confidence_nice_unit)<130 && (*its)->getDistance(*enemys)>90 && (int)(confidence_enemy[unit_e]*100) > 250)  //�츮�� �ڽŰ� ���� ���ְ� ������� ������ ���� �ڽŰ��� 250���� ũ�ٸ�
					//�������� 250 �� ���ڸ� �����ؾ���.
					{
					its_right_click_enemys = true;
					its_right_click_enemys_unit = enemys;
					}
					//	(*its)->rightClick(*enemys);   
					//�ڽŰ� ������� ���� ���� ������ ����.
					else if((*its)->getDistance(*enemys)<300 && (int)(confidence_enemy[unit_e]*100) > 250)
					its_unload_its2 = true;
					//	(*its)->unload(*its2);
					else;
					//(*its)->move((*confidence_nice_unit)->getPosition()); //���� �ڽŰ� ���� ���ֿ��� �̵�.

					}
					}
					}

					*/



					//** �Ѱ����� �� ��Ʋ���� ������ ��Ʈ�� 1 ��






					//���̿��н��� �Ÿ� ������ �ڵ�( �ʿ���� �ڵ���  ��������.)
					/*
					std::set<BWAPI::Unit *>::const_iterator its3 = BWAPI::Broodwar->self()->getUnits().begin();
					std::set<BWAPI::Unit *>::const_iterator its4 = its3++;
					if((*its3)->getDistance(*its4) <66) 
					Broodwar->drawTextScreen(100,150,"sd");
					if(sqrt(double((*its3)->getPosition().x() - (*its4)->getPosition().x())*((*its3)->getPosition().x() - (*its4)->getPosition().x()) + ((*its3)->getPosition().x() - (*its4)->getPosition().x())*((*its3)->getPosition().x() - (*its4)->getPosition().x())) <100) 
					Broodwar->drawTextScreen(100,160,"success");




					Position q1=(*its3)->getPosition(); 
					Position q2=(*its4)->getPosition(); 
					Broodwar->drawCircle(CoordinateType::Map,q1.x(),q1.y(),67,Colors::Red,false);
					Broodwar->drawCircle(CoordinateType::Map,q2.x(),q2.y(),67,Colors::Red,false);

					*/

					/*
					static int frame_storm = Broodwar->getFrameCount();
					if(frame_storm == Broodwar->getFrameCount())
					{
					frame_storm = frame_storm + 8;

					bool storm_ok = true;  //������ �ߺ��� ���ɼ��� �ִ°�
					///�������÷��� �� �ڽŰ��� 670���� ũ�� �����ϱ�. ����  - ���ױ���
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{

					for(int i=0; i < psionic_storm_num ; i++)
					{
					if(psionic_storm_attackedX[i] == 0 && psionic_storm_attackedY[i] ==0)
					break;

					double dist_storm_command = sqrt(double((psionic_storm_attackedX[i]-(*enemys)->getPosition().x())*(psionic_storm_attackedX[i]-(*enemys)->getPosition().x()) + (psionic_storm_attackedY[i]-(*enemys)->getPosition().y())*(psionic_storm_attackedY[i]-(*enemys)->getPosition().y()))); //�Ÿ� ���ϴ� ����	

					if(dist_storm_command < 100)
					storm_ok = false;
					}

					if((int)(confidence_enemy[unit_e]*100) > 280 && !((*enemys)->isUnderStorm()) && storm_ok) // �ڽŰ��� 670���� ũ��, ���� ����ؿ� ���� �ʰ�, ����� ��ġ�� �ߺ��� �������� ���� �� ������ ����
					{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar && (*its)->getEnergy() >= 75)
					{							
					(*its)->useTech(BWAPI::TechTypes::Psionic_Storm,*enemys);
					psionic_storm_attackedX[psionic_storm_num] = (*enemys)->getPosition().x();
					psionic_storm_attackedY[psionic_storm_num] = (*enemys)->getPosition().y();
					psionic_storm_num++;					
					break; //�� �Ѹ����� �������÷� �Ѹ����� �����ϱ� ���� break;
					}

					}
					}

					///�������÷��� �� �ڽŰ��� 600���� ũ�� �����ϱ�. ��


					}
					*/

					unit_e++; //unit���� 1�� ���������ֱ�.


				}
			}
		}


		/////****�� �ڽŰ� ���� ���������� ���

		int enemy_num121=0;
		for (std::set<BWAPI::Unit *>::const_iterator enemys2 = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys2 != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys2)
		{
			enemy_num121++; //�� �������.
		}


		/*
		static int fram2222 = Broodwar->getFrameCount();
		if(fram2222 == Broodwar->getFrameCount())
		{
		fram2222 = fram2222 + 8;

		if(enemy_num121>=2)
		{
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{

		if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar && (*its)->getEnergy() >= 75)
		{	
		(*its)->useTech(BWAPI::TechTypes::Psionic_Storm,*confidence_nice_enemy_unit);
		break;
		}

		}
		}
		}
		*/
		///****�� �ڽŰ� ���� ���������� ��� 2

		//******���� �ڽŰ��ý��� + �������÷����� ��***///






		std::set<BWAPI::Unit *>::const_iterator min_my_attack_unit_en_expand_unit = BWAPI::Broodwar->self()->getUnits().end(); // �� �ո���� ���� ����� �츮 �������� 
		int min_my_attack_unit_en_expand = 100000;  

		///////////////�� �ո���� ���� ����� �������� ����////////////
		static int frame__2 = Broodwar->getFrameCount();
		if(frame__2 == Broodwar->getFrameCount())
		{
			frame__2 = frame__2 + 4;  //4�����Ӹ��� ����ǰ�.
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{	
				if((*its)->isCompleted() && (*its)->getType().groundWeapon().damageAmount() >= 5 && (*its)->getType().canAttack() && (*its)->getType().canMove() &&  (*its)->getType() != BWAPI::UnitTypes::Protoss_Probe && (*its)->getType() != BWAPI::UnitTypes::Zerg_Drone && (*its)->getType() != BWAPI::UnitTypes::Terran_SCV) // �������� 5���� ũ�ٸ�...... ���ָ� ���õ�. �ϲ� ����
				{
					if((*its)->getDistance(en_expand)< min_my_attack_unit_en_expand)
					{
						min_my_attack_unit_en_expand = (*its)->getDistance(en_expand);
						min_my_attack_unit_en_expand_unit = its;
					}

				}
			}

		}


		//** �Ѱ����� �� �������÷� ��Ʋ���� ������ ��Ʈ�� 2 ����





		static int frame___44 = Broodwar->getFrameCount();
		if(frame___44 == Broodwar->getFrameCount())
		{
			frame___44 = frame___44+4 ; //4������ ���� ����
			//if(total_attack) //�Ѱ����̸� 
			if(high_templer_loaded_complete) //�������÷� 4���� ��� ������ ��Ʋ ��Ʈ�� ����.
			{
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Shuttle) //��Ʋ����
					{
						for (std::set<BWAPI::Unit *>::const_iterator its2 = BWAPI::Broodwar->self()->getUnits().begin(); its2 != BWAPI::Broodwar->self()->getUnits().end(); ++its2)
						{
							if((*its2)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
							{
								if((*its)->getShields() < 30)
									(*its)->unload(*its2);  //���尡 30���� ������ �������÷� �� ������
								else if(its_right_click_enemys)  //�츮�� �ڽŰ� ���� ���ְ� ������� ������ ���� �ڽŰ��� 250���� ũ�ٸ�
									(*its)->move((*min_my_attack_unit_en_expand_unit)->getPosition());
								// �ϴ� ���(*its)->rightClick(*its_right_click_enemys_unit);//�������� 250 �� ���ڸ� �����ؾ���.

								//	(*its)->rightClick(*enemys);
								//�ڽŰ� ������� ���� ���� ������ ����.
								else if(its_unload_its2)
									(*its)->unload(*its2);
								else
								{
									//(*its)->move((*confidence_nice_unit)->getPosition()); //���� �ڽŰ� ���� ���ֿ��� �̵�.

									(*its)->move((*min_my_attack_unit_en_expand_unit)->getPosition());	//���� �ո���� ���� ����� �츮���ֿ��Է� �̵�.
								}
							}
						}
					}
				}
			}

		}


		//** �Ѱ����� �� �������÷� ��Ʋ���� ������ ��Ʈ��  2 ��



		////********** �������÷� �������� ��ġ�� ����

		/*
		int hi_total = BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_High_Templar);
		if(hi_total != 0)
		{
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its) // �������÷��� �ְ� ¦���̸�
		{
		//Broodwar->drawTextScreen(420,20,"%s %d","hi_total : ",hi_total);
		if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar && (*its)->getEnergy() < 48) //������ 48���ϸ�
		{
		//Broodwar->drawTextScreen(420,30,"%s","energy_less 49 : ");
		for(std::set<BWAPI::Unit *>::const_iterator itss = BWAPI::Broodwar->self()->getUnits().begin(); itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss)
		{
		if((*itss)->getType() == BWAPI::UnitTypes::Protoss_High_Templar && (*itss)->getEnergy() < 48 && (*its)->getID() != (*itss)->getID())
		{
		//Broodwar->drawTextScreen(420,40,"%s","archon_test : ");
		(*its)->useTech(BWAPI::TechTypes::Archon_Warp,*itss);
		break;
		}
		}
		break;
		}
		}
		}
		*/

		///�������÷� �������� ��ġ�� ��**********





		/////***��������Ʈ�� ����.***//////
		static int frame_obob=Broodwar->getFrameCount();
		if(frame_obob==Broodwar->getFrameCount())
		{
			frame_obob = frame_obob+4; //4������ ���� ����

			int observer_total = BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Observer);
			//int *total_array_ob = new int[observer_total];
			int count_i=0;

			/*for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{

			if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer && observer_total != count_i)
			{
			total_array_ob[count_i]= (*its)->getID(); // ��� ������ ���̵� ����
			Broodwar->drawTextScreen(420,40,"all_ob_id : %d",total_array_ob[count_i]);
			count_i++;
			}
			}
			*/

			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{ //�ڽŰ����� ���� ����ٴϴ� ������ used_ob[0] �� �� Ȯ����� �������� ������ used_ob[1]�� ���̵� ����.
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer)
				{
					if(ob_bool == false)
					{
						used_ob[0]=(*its)->getID();
						ob_bool = true;
						//Broodwar->drawTextScreen(420,10,"%s %d","used_ob[0] : ", used_ob[0]);
						break;
					}
					if(ob_bool2 == false)
					{
						if((*its)->getID() != used_ob[0])
						{
							used_ob[1]=(*its)->getID();
							ob_bool2 = true;
							//Broodwar->drawTextScreen(420,20,"%s %d","used_ob[1] : ", used_ob[1]);
							break;
						}
						else
							break;
					}
				}
			}

			count_i=0;
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{ //�� ���õ� �������� �׾����� ��Ҵ��� ���̵�� �˻�, ���̵� ������ ���������� �Ǵ���. �ڽŰ� ����ٴϴ� ������
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer)
				{	
					count_i++;
					if((*its)->getID() == used_ob[0]) 
						break;
					else if((*its)->getID() != used_ob[0] && count_i == observer_total)
					{
						ob_bool = false;
						break;
					}

				}
			}

			count_i=0;
			if(ob_3_expand < 3)
			{
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer)
					{	
						count_i++;
						if((*its)->getID() == used_ob[1]) 
							break;
						else if((*its)->getID() != used_ob[1] && count_i == observer_total && observer_total != 1) // ���Ⱑ �׾��ٰ� �Ǵ��ϴ� �κ�
						{
							ob_bool2 = false; // ���̵� ���� �ޱ� ����
							ob_3_expand++;
							count_i=0;
							break;
						}
					}
				}
			}
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{ // �ڽŰ� ���� ���ֿ��� ������ ���� �ٴϱ�
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer && (*its)->getID() == used_ob[0])
				{
					(*its)->move((*confidence_nice_unit)->getPosition());
					//BWAPI::Broodwar->drawLineMap((*its)->getPosition().x(), (*its)->getPosition().y(), (*confidence_nice_unit)->getPosition().x(), (*confidence_nice_unit)->getPosition().y(), BWAPI::Colors::Red);
					//Broodwar->drawTextScreen(420,80,"%s %d","confidence",used_ob[1]);
					break;
				}	
			}

			Position en_start = this->informationManager->getEnemyStartLocation()->getPosition();
			Position en_choke = BWTA::getNearestChokepoint(en_start)->getCenter();
			Position en_expand = BWTA::getNearestBaseLocation(en_choke)->getPosition();

			if(ob_3_expand < 3)// ������ 3���������� �� Ȯ����� �����Ϸ� ����. ������ ���°��� ���� �ϱ� ���Ͽ�
			{
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{  
					if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer && (*its)->getID() == used_ob[1]) 
					{
						(*its)->rightClick(en_expand);
						//Broodwar->drawTextScreen(420,70,"%s %d","expand", used_ob[1]);
						break;
					}
				}
			}

			std::set<BWAPI::Unit *>::const_iterator search_save = BWAPI::Broodwar->self()->getUnits().begin(); //���ݹް� �ִ� ������ begin���� �˻��ϴµ� ���� �ֱٱ��� �˻��� ���� ����
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its) // �������˻�
			{
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_Observer && (*its)->getID() != used_ob[0] && (*its)->getID() != used_ob[1]) // ���������� �Ǵ��ϰ�, �ڽŰ� ���� ������ �̹� �Ѱ��ִ� �������� �ƴϾ���Ѵ�.
				{
					for (std::set<BWAPI::Unit *>::const_iterator itss = search_save; itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss) // ��� ���� �˻�
					{
						search_save++;
						if((*itss)->isUnderAttack() && !((*itss)->getType() == BWAPI::UnitTypes::Protoss_Observer)) // �˻��� ������ ���ݹް� �ְ� �������� �ƴϸ�
						{
							Position q=(*itss)->getPosition(); // ������ �޾ƿͼ�
							(*its)->rightClick(q); // �̵�
							//Broodwar->drawTextScreen(420,90,"%s","attack");
							break;	
						}
					}

				}		
			}	

			for (std::set<BWAPI::Unit *>::const_iterator en = Broodwar->enemy()->getUnits().begin(); en != BWAPI::Broodwar->enemy()->getUnits().end(); ++en)
			{
				if((*en)->getType() == BWAPI::UnitTypes::Protoss_Nexus || (*en)->getType() == BWAPI::UnitTypes::Terran_Command_Center || (*en)->getType() == BWAPI::UnitTypes::Zerg_Hatchery)
				{
					if((*en)->getDistance(en_expand) < 40)
					{
						en_expand_exist = true;
						break;
					}
				}
			}
		}
		////////////////������ ��

		////****������ ����, ���ݽ� ��Ʈ�� ��***////











		//ó���� �� ��ŸƮ�����̼��� 0,0���� ����
		/*
		if(enemy_start_first)
		{
		//�� ��ŸƮ�����̼ǿ� �����Ⱚ �־��. �� ��ŸƮ�����̼��� 3���ٲ��=> �� ������ ã������.
		BWTA::getStartLocation(BWAPI::Broodwar->self());
		BWTA::BaseLocation* tt = NULL;
		this->informationManager->setEnemyStartLocation(tt);
		//this->informationManager->getEnemyStartLocation()->getPosition().x() = 0;
		//this->informationManager->getEnemyStartLocation()->getPosition().y() = 0;
		enemy_start_first = false;
		}
		*/





		//�١١��� �ǹ�, ���ֵ� ���Ϸ� ����ϴ¼ҽ�.
		/* �������� �ʿ���⶧��
		static int frametesttest=Broodwar->getFrameCount();
		int en_id;
		for (std::set<BWAPI::Unit *>::const_iterator en = Broodwar->enemy()->getUnits().begin(); en != BWAPI::Broodwar->enemy()->getUnits().end(); ++en)
		{
		//if ((*en)->getType().isBuilding() && !((*en)->getType().isInvincible()))
		{
		//if((*en)->getType().isBuilding() == true)
		{
		if(Broodwar->getFrameCount() == frametesttest) 
		{
		//en_id = (*en)->getID();
		if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Nexus) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Nexus %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Assimilator) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Assimilator %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Pylon) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Pylon %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Forge) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Forge %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Gateway) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Gateway %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Observatory) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Observatory %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Photon_Cannon %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Robotics_Facility) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Robotics_Facility %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Robotics_Support_Bay) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Robotics_Support_Bay %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Shield_Battery) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Shield_Battery %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Stargate) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Stargate %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Citadel_of_Adun) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Citadel_of_Adun %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Cybernetics_Core) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Cybernetics_Core %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Templar_Archives) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Templar_Archives %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Command_Center) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Command_Center %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Refinery) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Refinery %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Comsat_Station) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Comsat_Station %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Control_Tower) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Control_Tower %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Academy) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Academy %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Barracks) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Barracks %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Bunker) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Bunker %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Engineering_Bay) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Engineering_Bay %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Factory) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Factory %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Machine_Shop) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Machine_Shop %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Missile_Turret) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Missile_Turret %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Physics_Lab) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Physics_Lab %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Starport) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Starport %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Supply_Depot) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Supply_Depot %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Cocoon) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Cocoon %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Creep_Colony) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Creep_Colony %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Evolution_Chamber) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Evolution_Chamber %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Extractor) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Extractor %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Hatchery) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Hatchery %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Hydralisk_Den) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Hydralisk_Den %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Lair) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Lair %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Larva) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Larva %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Sunken_Colony) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Sunken_Colony %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Spawning_Pool %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Spire) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Spire %d\n",(Broodwar->getFrameCount()/24),en_id);}
		// ������� ����
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Firebat) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Firebat %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Goliath) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Goliath %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Marine) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Marine %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Medic) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Medic %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_SCV) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_SCV %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Siege_Tank_Siege_Mode %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Siege_Tank_Tank_Mode %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Terran_Vulture) { en_id = (*en)->getID(); fprintf(fp,"%d Terran_Vulture %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Corsair) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Corsair %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Dragoon) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Dragoon %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Probe) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Probe %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Zealot) { en_id = (*en)->getID(); fprintf(fp,"%d Protoss_Zealot %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Drone) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Drone %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Egg) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Egg %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Hydralisk) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Hydralisk %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Lurker) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Lurker %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Lurker_Egg) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Lurker_Egg %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Mutalisk) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Mutalisk %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Overlord) { en_id = (*en)->getID(); fprintf(fp,"%d Zerg_Overlord %d\n",(Broodwar->getFrameCount()/24),en_id);}
		else if ((*en)->getType() == BWAPI::UnitTypes::Zerg_Zergling) { en_id = (*en)->getID(); fprintf(fp,"%d :Zerg_Zergling %d\n",(Broodwar->getFrameCount()/24),en_id);}

		}


		//fprintf(fp,"%d\n",en_id);  //���� �����
		}
		}
		}
		//1�ʸ��� ���
		if(Broodwar->getFrameCount() == frametesttest) 
		frametesttest = frametesttest + 24;

		*/ //�������� �ʿ���⶧��

		//�١١�

		//Broodwar->drawTextScreen(420,90,"enemy_startlocation x , y : %d, %d", this->informationManager->getEnemyStartLocation()->getPosition().x(), this->informationManager->getEnemyStartLocation()->getPosition().y());
		//Broodwar->drawTextScreen(420,170,"enemy_locatION_change : %d", enemy_start_location_change);
		//Broodwar->drawTextScreen(420,180,"%d %d", enemy_start_locationX, enemy_start_locationY);

		// �ڡڡ���getstart�������� �� �� �ٲ����� �ľ��ϱ�. 4�ο���� �� 4��° ��ġ�� ���� �Ȱ��� ���� �ذ��ϱ�������. 


		/*
		if(enemy_start_locationX != this->informationManager->getEnemyStartLocation()->getPosition().x() &&  enemy_start_locationY != this->informationManager->getEnemyStartLocation()->getPosition().y())
		enemy_start_location_change++;

		enemy_start_locationX = this->informationManager->getEnemyStartLocation()->getPosition().x();
		enemy_start_locationY = this->informationManager->getEnemyStartLocation()->getPosition().y();
		*/


		//Broodwar->drawTextScreen(420,150,"scout id : %d", getCIG2013_scout_probe_ID);
		//Broodwar->drawTextScreen(420,170,"probe unit count : %d", BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Probe));


		//�����佺���� //
		if(Broodwar->enemy()->getRace() == Races::Protoss)
		{
			//�������� ���κ� ���̵� �޾ƿ���  --�����佺����--
			if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Probe) == 9 && cig1 == false)
			{
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{ 
					if((*its)->getDistance(my_start) > 300 && (*its)->getType() == BWAPI::UnitTypes::Protoss_Probe)
					{
						getCIG2013_scout_probe_ID = (*its)->getID();

						cig1 = true;//�ѹ��� �ޱ�����.
					}


				}
			}

			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{ 
				if((*its)->getID() == getCIG2013_scout_probe_ID)
				{
					//BWAPI::Broodwar->drawCircleMap((*its)->getPosition().x(),(*its)->getPosition().y(), 6, BWAPI::Colors::Yellow);
				}
			}



			if(cig2 == false)
			{
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{ 
					if(cig1=true && (*its)->getType() == BWAPI::UnitTypes::Protoss_Probe && (*its)->getID() == getCIG2013_scout_probe_ID && Broodwar->getFrameCount() < 24*300) //5�� �̳��϶���
					{
						if((*its)->isGatheringMinerals())
						{
							(*its)->rightClick(this->informationManager->getEnemyStartLocation()->getPosition());
							cig2=true;
						}

					}

				}
			}


			//-----------2�ο���� �� �����佺�� ��������---����--------// ���߿� �ð��Ǹ� ���ֱ�

			if(BWAPI::Broodwar->getStartLocations().size() ==2)
			{

				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Probe) == 9 && cig2013_11 == false) {

					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{ 
						if((*its)->getType() == BWAPI::UnitTypes::Protoss_Probe && (*its)->isCompleted())
						{
							getCIG2013_scout_probe_ID = (*its)->getID();
							(*its)->rightClick(this->informationManager->getEnemyStartLocation()->getPosition()); 
							cig2013_11 = true;
							break;				

						}
					}
				}

				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{ 

					if(getFirst_scout_probe_ID == (*its)->getID())
						if((*its)->isConstructing())
							getFirst_scout_probe_ID = -2;


				}
			}


			//-----------2�ο���� �� �����佺�� ��������---��--------//



		}





		//BWAPI::Broodwar->drawCircleMap(my_ex1.x(),my_ex1.y(), 6, BWAPI::Colors::Yellow); 


		//��ī��Ʈ�� �Ϸ�Ǹ� �� �ѹ� �� ���������� �̵����ֱ�. 4�ο���� �� 4��° ��ġ�� ���� �Ȱ��� ���� �ذ��ϱ�������.  �����佺���� ���ֱ�.  
		//	if(Broodwar->enemy()->getRace() != Races::Terran) 
		/*
		if(Broodwar->enemy()->getRace() == Races::Protoss)
		{
		if(enemy_start_location_change_true)
		{
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{ 
		if((*its)->getType() == BWAPI::UnitTypes::Protoss_Nexus)
		{
		for (std::set<BWAPI::Unit *>::const_iterator probe3 = BWAPI::Broodwar->self()->getUnits().begin(); probe3 != BWAPI::Broodwar->self()->getUnits().end(); ++probe3)
		{ 
		//�������� �Ÿ��� 400�̻��̰�, �̳׶��� ĳ�� ���� ���κ긦 �����ض�. ��, ���� ���� ���κ� 
		BWAPI::Position pos_bonjin = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();
		if((*probe3)->getDistance(my_ex1) > 200 && (*probe3)->getDistance(pos_bonjin)>400 && (*probe3)->isGatheringMinerals() && Broodwar->getFrameCount() < 24*300)   //5�� �̳��϶���
		//	if((*probe3)->getID() == getCIG2013_scout_probe_ID && (*probe3)->isGatheringMinerals() && Broodwar->getFrameCount() < 24*300)   // cig2013(���κ� ���̵�� �޾ƿ��� �ٲ�) 5�� �̳��϶���
		{
		Position *enemy_start_loca = new Position(this->informationManager->getEnemyStartLocation()->getPosition().x(),this->informationManager->getEnemyStartLocation()->getPosition().y());


		//(*probe3)->rightClick(*enemy_start_loca);	
		enemy_start_location_change_true = false;

		}


		}
		}
		}
		}
		}
		*/






		//�ڡڡڳ�


		////----------------------�ѹ��� ����ǰ� .. �������κ� �¸���ũ �����ֱ�  

		if(first_probe_onrevoke)
		{

			for (std::set<BWAPI::Unit *>::const_iterator en = Broodwar->enemy()->getUnits().begin(); en != BWAPI::Broodwar->enemy()->getUnits().end(); ++en)
			{ 
				if ((*en)->getType() == BWAPI::UnitTypes::Protoss_Nexus || (*en)->getType() == BWAPI::UnitTypes::Terran_Command_Center || (*en)->getType() == BWAPI::UnitTypes::Zerg_Hatchery)
				{
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{ 
						if((*en)->getDistance(*its)<30)
						{
							std::set<BWAPI::Unit *>::const_iterator probe = its;
							//this->workerManager->onRevoke(*probe,2);


							//���⼭���� �¸���ũ��Ű�� �ҽ�
							//	for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
							//	{				
							//ab++;

							//BWAPI::Broodwar->self()->getUnits().
							if ((*its)->getType() == BWAPI::UnitTypes::Protoss_Probe)
							{
								std::set<BWAPI::Unit *>::const_iterator probe = its;
								//Position *d = new Position(3310,3530);
								//BWAPI::Position pos = this->informationManager->get

								getFirst_scout_probe_ID = (*probe)->getID();
								this->workerManager->onRevoke(*probe,2);
								//(*probe)->
							}
							//if(ab==2)
							//break;

							//			}

							//first_probe_onrevoke = false;

						}

					}
				}



			}
		}

		//--------------------------------------------------------------------------------------------------

		/*

		//�� ����ũ�����ִ� �ҽ�

		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{				
		//ab++;

		//BWAPI::Broodwar->self()->getUnits().
		if ((*its)->getType() == BWAPI::UnitTypes::Protoss_Probe)
		{
		std::set<BWAPI::Unit *>::const_iterator probe = its;
		//Position *d = new Position(3310,3530);
		//BWAPI::Position pos = this->informationManager->get

		this->workerManager->onRevoke(*probe,2);
		//(*probe)->
		}
		//if(ab==2)
		//break;

		}
		*/


		// �ϲ۵�����

		double ww=0;
		double bvx[20] = {0,};
		double bvy[20] = {0,};
		int countx = 0;
		static double enemy_base_loc_x = 0;
		static double enemy_base_loc_y = 0;
		std::set<BWAPI::Unit *>::const_iterator a = BWAPI::Broodwar->self()->getUnits().begin();
		for (std::set<BWAPI::Unit *>::const_iterator en = Broodwar->enemy()->getUnits().begin(); en != BWAPI::Broodwar->enemy()->getUnits().end(); ++en)
		{
			//��ü �츮 ���� ����
			for (std::set<BWAPI::Unit *>::const_iterator itss = BWAPI::Broodwar->self()->getUnits().begin(); itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss)
			{

				//Broodwar->drawTextScreen(420,150,"first  %d,  after %d", getFirst_scout_probe_ID, (*itss)->getID());
				if((*itss)->getID() == getFirst_scout_probe_ID) //���̵� ������ �������κ�� ���ٸ�
				{



					//if(*en)->getType() == BWAPI::UnitTypes::Protoss_Nexus)
					if(!((*en)->getType().canMove()) && !((*en)->getType().isInvincible())) //�� �ǹ� �޾ƿ���.   && �ڴ� ������ ��(��, �̳׶��̳� ������ �ǹ���)
					{
						//�ǹ��� ���κ� ������ �ޱ�,  
						BWAPI::Position builded = (*en)->getPosition();
						BWAPI::Position probe = (*itss)->getPosition();
						//if((*en)->getDistance(*itss)<180)

						a = itss;

						//<!----------�ǹ��� ���κ������� ������ �Ǵ� �� ���------>
						//������ �Ǵ� ���� m`, ����ġ w
						//double m1 = -((probe.y() - builded.y()) / (probe.x() - builded.x()));
						//�������ֱ� ���� for���ȿ� ����ġ���ϴ°� �����ʿ�¾���
						//double w = 1/( (probe.x()-builded.x()) * (probe.x()-builded.x()) + (probe.y()-builded.y()) * (probe.y()-builded.y()));
						//ww = w;
						// ���κ���ġ�� ���������ϴ� = �ǹ� builded.x()-probe.x()
						//Broodwar->drawTextScreen(400,70,"1/sqrt(m1*m1+1),m1/sqrt(m1*m1+1) : %f, %f",10/(w * sqrt(m1*m1+1)), (10*m1)/(w *sqrt(m1*m1+1)));
						//	Position *bv = new Position(1/sqrt(m1*m1+1),m1/sqrt(m1*m1+1));  // Building Vector ��������
						//Position *bv = new Position(10/(w * sqrt(m1*m1+1)),(m1 * 10)/(w *sqrt(m1*m1+1)));  // Building Vector ��������

						//Position *bv = new Position((builded.y()-probe.y()), -(builded.x()-probe.x()));  // Building Vector ��������

						//�ִ� 80�����Ѱ�
						Position *bv = new Position((builded.x()-probe.x())*0.17365 - (builded.y()-probe.y()) * (-0.9848), (builded.x()-probe.x()) * (-0.9848) + 0.17365 * (builded.y()-probe.y()));
						//Broodwar->drawTextScreen(420,60,"bvxx, bvyy : %d, %d", (*bv).x(), (*bv).y());


						if(this->informationManager->getEnemyStartLocation()->getPosition().x() == builded.x() && this->informationManager->getEnemyStartLocation()->getPosition().y() == builded.y())
						{

						}
						else
						{
							bvx[countx] = (*bv).x();
							bvy[countx] = (*bv).y();
							countx++;

						}
					}
				}
			}
		}

		for (std::set<BWAPI::Unit *>::const_iterator a = BWAPI::Broodwar->self()->getUnits().begin(); a != BWAPI::Broodwar->self()->getUnits().end(); ++a)
		{


			/*//�������κ� �������� �ؽ�Ʈ���Ͽ� ���
			if(scout_start)
			{			
			if((*a)->getID() != getFirst_scout_probe_ID) //���̵� ������ �������κ�� ���� �ʴٸ�
			{
			fprintf(fp,"\ndead\n\n\n\n");
			}
			}*/




			if((*a)->getID() == getFirst_scout_probe_ID) //���̵� ������ �������κ�� ���ٸ�
			{
				scout_start = true;			

				//BWAPI::Broodwar->printf("first  %d,  after %d", getFirst_scout_probe_ID, (*a)->getID());

				//Broodwar->drawTextScreen(420,150,"first  %d,  after %d", getFirst_scout_probe_ID, (*a)->getID());
				//���κ�������
				BWAPI::Position probe2 = (*a)->getPosition();
				//�ؼ��� �ǹ� ����ƽ
				//enemy_base_loc_x = this->informationManager->getEnemyStartLocation()->getPosition().y() - probe2.y() ;
				//	enemy_base_loc_y = -(this->informationManager->getEnemyStartLocation()->getPosition().x() - probe2.x());

				//�ִ� 80�����Ѱ�
				enemy_base_loc_x = (this->informationManager->getEnemyStartLocation()->getPosition().x() - probe2.x()) * 0.17365 -  (this->informationManager->getEnemyStartLocation()->getPosition().y() - probe2.y()) * (-0.9848)  ;
				enemy_base_loc_y = (this->informationManager->getEnemyStartLocation()->getPosition().x() - probe2.x()) *  (-0.9848) + 0.17365 * (this->informationManager->getEnemyStartLocation()->getPosition().y() - probe2.y()) ;

				//�ִ� 82���� �Ѱ�
				//enemy_base_loc_x = (this->informationManager->getEnemyStartLocation()->getPosition().x() - probe2.x()) * 0.13917 -  (this->informationManager->getEnemyStartLocation()->getPosition().y() - probe2.y()) * (-0.99027)  ;
				//enemy_base_loc_y = (this->informationManager->getEnemyStartLocation()->getPosition().x() - probe2.x()) *  (-0.99027) + 0.13917 * (this->informationManager->getEnemyStartLocation()->getPosition().y() - probe2.y()) ;



				// �������� ����
				double bvxx = 0;
				double bvyy = 0;

				for(int l=0 ; l<20 ; l++)
				{
					bvxx += bvx[l];
					bvyy += bvy[l];
				}

				bvxx += enemy_base_loc_x;
				bvyy += enemy_base_loc_y;
				//Broodwar->drawTextScreen(420,90,"enemy_startlocation x , y : %d, %d", this->informationManager->getEnemyStartLocation()->getPosition().x(), this->informationManager->getEnemyStartLocation()->getPosition().y());
				//Broodwar->drawTextScreen(420,80,"enemy_base x , y : %d, %d", enemy_base_loc_x, enemy_base_loc_y);
				int test1=0;
				int test2=0;
				test1 = (bvxx * ww) * 1/100;
				test2 = (bvyy * ww) * 1/100;
				//bvx[l] = bvx[l]*300/sqrt(bvx[l] * bvx[l] + bvy[l] * bvy[l]);
				//bvy[0] = bvy[l]*300/sqrt(bvx[l] * bvx[l] + bvy[l] * bvy[l]);
				bvxx = bvxx * 300/sqrt(bvxx * bvxx + bvyy * bvyy);
				bvyy = bvyy * 300/sqrt(bvxx * bvxx + bvyy * bvyy);

				//Position *bvv = new Position(bvxx ,bvyy);
				Position *bvv = new Position(bvxx + probe2.x(), bvyy + probe2.y());

				//12�����Ӹ��� �����̰�
				static int frametest=Broodwar->getFrameCount();   //24������ = 1��

				if(Broodwar->getFrameCount() == frametest) 
				{
					//���κ갡 �ָ� ������ �ʵ��� ���κ갡 ���� Ŭ���ϴ°� ����(���� Ŭ���� ���� ���κ���ġ���� ����) 1:3  ����Ŭ���� ������ �� ����.
					//Position *bvvv = new Position((3*(*bvv).x() + (*a)->getPosition().x())/4 , (3*(*bvv).y() + (*a)->getPosition().y())/2 );


					//	BWAPI::Broodwar->drawCircleMap((*bvv).x(),(*bvv).y(), 6, BWAPI::Colors::Yellow); //����� ������ ���κ� ��°� ǥ��
					//BWAPI::Broodwar->printf("first  %d,  after %d", getFirst_scout_probe_ID, (*a)->getID());

					//Broodwar->drawTextScreen(10,50,"frametest : %d", frametest);


					(*a)->rightClick(*bvv);	
					frametest = frametest + 12;
					//	Broodwar->drawTextScreen(420,50,"frametest : %d", frametest);

				}



				//Broodwar->drawTextScreen(420,30,"probe Position : %d, %d",  probe2.x(), probe2.y());
				//Broodwar->drawTextScreen(420,40,"Move Position : %lf, %lf", bvxx * ww + probe2.x(), bvyy * ww + probe2.y());

			}
		}




		//BWAPI::Broodwar->printf("probe Position : %f, %f",  probe2.x(), probe2.y());
		//BWAPI::Broodwar->printf("Move Position : %f, %f", bvxx * ww + probe2.x(), bvyy * ww + probe2.y());


		//////////////////////////////////////////////////////////////������

		//static int frametest2 = Broodwar->getFrameCount();
		//	if(Broodwar->getFrameCount() == frametest2) 
		//	{
		double distEnemyNexus = 0;
		double distMyNexus = 0;
		BWAPI::Position *myNexusPosition = new Position(0,0);

		// double distEnemyGround = 0;
		int enemyi = 0;

		bool defense_ing = false; //���������?


		//////////////////////////////���  �����鸸 ���⿡




		/////������

		for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
		{
			if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Nexus) 
			{
				*myNexusPosition = (*allMyUnit)->getPosition();
			}

		}



		static int frametest_defens = Broodwar->getFrameCount();
		if(frametest_defens == Broodwar->getFrameCount())
		{
			frametest_defens = frametest_defens + 20;


			if(!total_attack)  // �Ѱ����� �ƴ� ���� ��� �ý��� �۵� 
			{
				for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit != BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
				{
					//if((*allEnemyUnit)->BWAPI::UnitTypes::Zerg_Overlord)
					//	continue;  //���� �����ε��̸� �׳� �Ѿ.

					int j = -1;
					int i = 0;
					bool k = false;
					//enemyi = 0;

					BWAPI::Position *enemyPosition = new Position(0,0);
					BWAPI::Position *myPosition = new Position(0,0);

					*enemyPosition = (*allEnemyUnit)->getPosition();

					//double EnemyPower=0;
					//EnemyPower = ((double)allEnemyUnit->getType().groundWeapon().damageAmount())/allEnemyUnit->getType().groundWeapon().damageCooldown()


					//����
					/*
					for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
					{
					if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Nexus) 
					{
					distEnemyNexus = (*allEnemyUnit)->getDistance(*allMyUnit);
					//*myNexusPosition = (*allMyUnit)->getPosition();
					}

					}
					*/

					//�ո���
					for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
					{
						if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Nexus) 
						{
							distEnemyNexus = (*allEnemyUnit)->getDistance(*allMyUnit);
							break;
							//*myNexusPosition = (*allMyUnit)->getPosition();
						}

					}





					BWAPI::Position pos1241 = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();

					if((*allEnemyUnit)->getDistance(pos1241) < 550 || distEnemyNexus < 340 || (*allEnemyUnit)->getDistance(my_ex1) < 340)
					{
						for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
						{




							//cig2013  -- �ʹݿ� ����vs ���� �����̸鼭 ���� 120�Ÿ� �̸��ο����� ���ý��� ���� x ��¥��, ����vs �������� ��������.  -- ���� --

							if(Broodwar->enemy()->getRace() == Races::Protoss)
							{
								bool right_combat_cig=false;
								for(int ii=0;ii<20;ii++)
								{
									if((*allMyUnit)->getID() == Start_Combat_GetId[ii])
										right_combat_cig=true;
								}

								if(right_combat_cig == true)
									continue;
							}

							//cig2013  -- �ʹݿ� ����vs ���� �����̸鼭 ���� 120�Ÿ� �̸��ο����� ���ý��� ���� x ��¥��, ����vs �������� ��������.  -- �� --





							if((double)(*allMyUnit)->getType().groundWeapon().damageAmount() > 3 && (*allMyUnit)->isCompleted() && (*allMyUnit)->getType().canMove() && !((*allEnemyUnit)->BWAPI::UnitTypes::Zerg_Overlord))
							{
								//���κ�� ���� �ϲ��϶��� ������.
								if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe && !((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe) && !((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Zerg_Drone) && !((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Terran_SCV))
									continue;
								if(!((*allMyUnit)->getType().canMove()))
									continue;
								if(!((*allMyUnit)->isCompleted()))
									continue;

								if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe) //�ϲ۳����� ���� ���ݸ�� ����.
									continue;

								//������ begin�� begin+1�� ���õǴ� ���� �ذ� 
								j++;
								if(enemyi<=j || k==true)
								{			
									//BWAPI::Broodwar->drawLineMap((*allMyUnit)->getPosition().x(), (*allMyUnit)->getPosition().y(), (*allEnemyUnit)->getPosition().x(), (*allEnemyUnit)->getPosition().y(), BWAPI::Colors::Red);
									(*allMyUnit)->attack((*allEnemyUnit)->getPosition());	
									defense_ing = true;
									//(*allMyUnit)->rightClick(*allEnemyUnit);
									enemyi = enemyi + 1;
									i++;
									k=true;


									//���� ���� �ϲ��̸� �츮�� �Ѹ����� �޶�پ��. - �������� �ʾ���.
									/*
									if(((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe) || ((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Zerg_Drone) || ((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Terran_SCV))
									break;
									*/

									if(i==2)
										break;
								}
							}
						}
						//BWAPI::Position myPosition = new Position(0,0);
						//	myPosition = (*allMyUnit)->getPosition();
						//	double myPower=0;
						//	myPower = ((double)allMyUnit->getType().groundWeapon().damageAmount())/allMyUnit->getType().groundWeapon().damageCooldown();
					}



				}

			}

		}


		/////////////////��� ��


		int zeal_nn=0;
		for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
		{
			if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*allMyUnit)->isCompleted())
			{
				zeal_nn++;

			}
		}

		if(!firsss21)
		{
			firsss21 = true;
			for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
			{
				if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe)
				{
					if((*allMyUnit)->getDistance(my_start) > 800)
						search_prob_id = (*allMyUnit)->getID();
				}
			}
		}


		/////////////�ϲ� vs �ϲ� ���. �ϲ� �ڽ��� ���ݴ��� ������ ����������.

		if(zeal_nn == 0)
		{
			static int frametest_11 = Broodwar->getFrameCount();   //24������ = 1��
			if(frametest_11 == Broodwar->getFrameCount())
			{
				frametest_11 = frametest_11 + 20; //20������ ���� ����

				enemy_search_unit = 0;
				////������ �� �ϲ� �� ����.enemy_search_unit;
				for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit !=BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
				{
					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Terran_SCV || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Zerg_Drone)
					{
						if((*allEnemyUnit)->getDistance(my_start)<350)
						{
							enemy_search_unit++;
						}
					}
				}


				///������ �Ϸ�Ǿ�����?
				for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit !=BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit) 
				{
					if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Nexus || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Zerg_Hatchery || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Terran_Command_Center)
						scout_complete2 = true;

				}





				/////





				static int frametest_13 = Broodwar->getFrameCount();   //24������ = 1��   
				if(frametest_13 == Broodwar->getFrameCount())
				{
					frametest_13 = frametest_13 + 60; // 2.7������ ���� ����. 

					for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
					{
						if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe && getFirst_scout_probe_ID != (*allMyUnit)->getID() && search_prob_id != (*allMyUnit)->getID() && getCIG2013_scout_probe_ID != (*allMyUnit)->getID()) //�������ְ� ���̵� ���� �ʴٸ�
						{
							if(enemy_attack_first1 == false || probe_attack_id ==  (*allMyUnit)->getID())  // ó���̰ų� �ϲ��� ���̵� ó���� �����ߴ� ���ְ� ���ٸ�
							{
								probe_attack_id = (*allMyUnit)->getID(); //ó���� �ٲ�� ���ķδ� ���� ���̵� ���� �� ����.
								enemy_attack_first1 = true;
								if((*allMyUnit)->getDistance(my_start)<350) 
								{

									for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit != BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit)
										if((*allEnemyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Terran_SCV || (*allEnemyUnit)->getType() == BWAPI::UnitTypes::Zerg_Drone)
										{
											if((*allEnemyUnit)->getDistance(my_start)<350)
											{
												(*allMyUnit)->rightClick(*allEnemyUnit);
												break;
											}

										}

								}


								if((*allMyUnit)->getDistance(my_start)>760)
								{
									(*allMyUnit)->move(my_start); 
								}

							}
						}
					}

				}




				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) <= 2)
				{
					if(enemy_search_unit>=2 || Broodwar->self()->deadUnitCount(BWAPI::UnitTypes::Protoss_Probe) >= 1) //�� �ϲ� ������ 2���� �̻��̸�

					{
						for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit !=BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
						{
							if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe)
							{
								if((*allMyUnit)->getDistance(my_start)<450)
								{
									if((*allMyUnit)->getShields() < 10)
									{
										(*allMyUnit)->attack((*allMyUnit)->getPosition());
									}

									if((*allMyUnit)->getDistance(my_start)>760)
									{
										(*allMyUnit)->move(my_start); 
									}



								}

							}
						}
					}
				}









			}
		}



		///////////////////////////////��� ����  ��








		//�������÷� �¿��

		if(!high_templer_loaded_complete)
		{
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_Shuttle) //��Ʋ����
				{
					for (std::set<BWAPI::Unit *>::const_iterator its2 = BWAPI::Broodwar->self()->getUnits().begin(); its2 != BWAPI::Broodwar->self()->getUnits().end(); ++its2)
					{
						if((*its2)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
							(*its)->load(*its2);

					}
				}

			}
		}



		////~~~ �ʹ� ��ũ����Ʈ ���̱� +  �ո��� �԰� �ո��� �տ� ���̱� ����.////





		////~~~ �ʹ� ��ũ����Ʈ ���̱� +  �ո��� �԰� �ո��� �տ� ���̱� ��.////

		////***************�Ѱ��ݰ��� //////////


		double enemyDPS2 = 0;


		for each (BWAPI::Unit *u in SelectAllEnemy()(canMove)(isCompleted)(maxGroundHits,">",0).not(isWorker))
		{
			enemyDPS2 += ((double)u->getType().groundWeapon().damageAmount())/u->getType().groundWeapon().damageCooldown();
		}





		double myDPS2 = 0;

		for each (BWAPI::Unit *u in SelectAll()(canMove)(isCompleted)(maxGroundHits,">",0).not(isWorker))
		{
			myDPS2 += ((double)u->getType().groundWeapon().damageAmount())/u->getType().groundWeapon().damageCooldown();
		}


		//Broodwar->drawTextScreen(420,100,"Nexus Distance : %lf ",myDPS2);
		//myDPS2;


		//	enemy_dead_after_2min ����ϱ� .. �ƹ̸Ŵ��� �����, ��ũ����Ʈ�� �̵� ���⼭ ���ֱ�.  total_attack  enemy_dead_after_2min ���
		//. 8�ʸ��� �ѹ��� �� ���� ���ݸ��  �ϴ� ������ .armymanager���� �ϱ�


		static int frametest_total_attack = Broodwar->getFrameCount();   //24������ = 1��
		if(Broodwar->getFrameCount() == frametest_total_attack) 
		{

			///********�׶��� ���ݰ��� ����
			if(Broodwar->enemy()->getRace() == Races::Terran) 
			{
				//if (en_expand_exist && BWAPI::Broodwar->self()->supplyUsed()/2 > 110 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 135)  // �������÷��� �� ����, �α����� 105 �̻��̰�, ���� �ո����� �Ծ����� ó��� ����.  �ƴϸ� �α����� 135 �̻�Ǹ� ������ ó���� 
				if (BWAPI::Broodwar->self()->supplyUsed()/2 > 135 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 135)  // �������÷��� �� ����, �α����� 105 �̻��̰�, ���� �ո����� �Ծ����� ó��� ����.  �ƴϸ� �α����� 135 �̻�Ǹ� ������ ó���� 
				{
					total_attack = true;
					static int total_attack_start_time = Broodwar->getFrameCount();   //��Ż ������ ó�� �ð�.

					//�ϴ� ���ͷ� ����  total_attack_start_time
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
						Position *tmp = new Position(BWAPI::Broodwar->mapWidth()*32/2, BWAPI::Broodwar->mapHeight()*32/2);
						if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
						{

							(*its)->attack(*tmp); 
						}

						//chc �������÷��� ���� ����.
						if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
							(*its)->move(*tmp);

					}


					//���ݰ���

					if(total_attack_start_time+24*13 < Broodwar->getFrameCount())  //���� �� �� 13�� �Ŀ� ������. �� �������� 8�ʸ��� ����ǹǷ� 16�� �Ŀ� ���ݰ���.   ���� ���ٰ� ���ݰ��°��� �� ó�� ���ݿ��� ����.
						for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
						{
							if(confidence_nice_enemy_unit_confidence_num < 300)
							{

								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack(this->informationManager->getEnemyStartLocation()->getPosition());
								}

								//chc �������÷��� ���� ����.
								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move(this->informationManager->getEnemyStartLocation()->getPosition());

							}


							//�� �ڽŰ��� ���� ������ ������ �������� ���ݰ���. �� �������� �ڽŰ� ���� �ٲ㼭 ���ֱ�.
							if(confidence_nice_enemy_unit_confidence_num >= 300) //�佺�� 300�̻�
							{
								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack((*confidence_nice_enemy_unit)->getPosition());
								}


								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move((*confidence_nice_enemy_unit)->getPosition());

							}



						}

				}
			}


			///********�׶��� ���ݰ��� ��
			////////////

			///********������ ���ݰ��� ����
			if(Broodwar->enemy()->getRace() == Races::Protoss) 
			{
				//if (myDPS2 >= 6.5)  // �������ֱ� ������ 6.5


				//chc�̰͵� �������÷����� �ӽ�. ���µ� �ϴ� ���ͷ� �𿴴ٰ� ����
				/*
				for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
				{

				if(myDPS2>=8 && myDPS2<12)
				{
				Position *poss1 = new Position(2100,2100);
				if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar || (*its)->getType().groundWeapon().damageAmount() >= 8)
				(*its)->move(*poss1);

				}
				}*/

				///////////////�ӽó�

				//if (en_expand_exist && BWAPI::Broodwar->self()->supplyUsed()/2 > 110 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 135)  // �������÷��� �� ����, �α����� 105 �̻��̰�, ���� �ո����� �Ծ����� ó��� ����.  �ƴϸ� �α����� 135 �̻�Ǹ� ������ ó���� 

				if (BWAPI::Broodwar->self()->supplyUsed()/2 > 143 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 135)  // �������÷��� �� ����, �α����� 105 �̻��̰�, ���� �ո����� �Ծ����� ó��� ����.  �ƴϸ� �α����� 135 �̻�Ǹ� ������ ó���� 
				{
					total_attack = true;
					static int total_attack_start_time = Broodwar->getFrameCount();   //��Ż ������ ó�� �ð�.

					//�ϴ� ���ͷ� ����  total_attack_start_time
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
						Position *tmp = new Position(BWAPI::Broodwar->mapWidth()*32/2, BWAPI::Broodwar->mapHeight()*32/2);
						if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
						{

							(*its)->attack(*tmp); 
						}

						//chc �������÷��� ���� ����.
						if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
							(*its)->move(*tmp);

					}


					//���ݰ���

					if(total_attack_start_time+24*13 < Broodwar->getFrameCount())  //���� �� �� 13�� �Ŀ� ������. �� �������� 8�ʸ��� ����ǹǷ� 16�� �Ŀ� ���ݰ���.   ���� ���ٰ� ���ݰ��°��� �� ó�� ���ݿ��� ����.
						for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
						{
							if(confidence_nice_enemy_unit_confidence_num < 300)
							{

								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack(this->informationManager->getEnemyStartLocation()->getPosition());
								}

								//chc �������÷��� ���� ����.
								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move(this->informationManager->getEnemyStartLocation()->getPosition());

							}


							//�� �ڽŰ��� ���� ������ ������ �������� ���ݰ���. �� �������� �ڽŰ� ���� �ٲ㼭 ���ֱ�.
							if(confidence_nice_enemy_unit_confidence_num >= 300) //�佺�� 300�̻�
							{
								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack((*confidence_nice_enemy_unit)->getPosition());
								}


								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move((*confidence_nice_enemy_unit)->getPosition());

							}



						}

				}
			}

			////////////������ ���ݰ��� ��

			////*********������ ���ݰ��� ����***//
			if(Broodwar->enemy()->getRace() == Races::Zerg) //
			{
				//������ �������� �ƴϰ�, 11���� �̻��̸� ���� ��
				//if(!zerg_first_)

				int my_zealot_num=0;

				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Assimilator) == 0)
				{
					//������ 11���� �¾�� 
					for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
					{	
						if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot && (*it)->isCompleted())
						{
							my_zealot_num++;
						}
					}
					//	if(Broodwar->self()->incompleteUnitCount(UnitTypes::Protoss_Zealot) < 1 && BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot >= 11))
					//if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Zealot) >= 11)
					if(my_zealot_num>=11) //���� 11���� �̻��̸� ���� ���
					{
						///�ϱ�
						for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
						{			
							if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
							{
								(*it)->attack(this->informationManager->getEnemyStartLocation()->getPosition());
								zerg_first_attack = true;
								defense_makgi = true;
								//zerg_first_ = true
							}
						}
						/*

						/////////////////////�츮�� ���� ��ġ�� �ϱ� ����
						bool exist_enemy = false; //���� �Ѹ����� �ִ��� Ȯ��.
						for (std::set<BWAPI::Unit *>::const_iterator allEnemyUnit = BWAPI::Broodwar->enemy()->getUnits().begin(); allEnemyUnit != BWAPI::Broodwar->enemy()->getUnits().end(); ++allEnemyUnit)
						{
						exist_enemy = true;
						}


						int distance_far = 0;
						for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
						{	
						if((*it)->getDistance(*min_my_attack_unit_en_expand_unit) >= 200) //�׽�Ʈ
						distance_far++;
						}

						if(distance_far >= 3 && exist_enemy == true) // ���� ����
						{
						for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
						{	
						if((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
						{
						if(it == min_my_attack_unit_en_expand_unit)
						(*it)->stop();
						else 
						(*it)->move((*min_my_attack_unit_en_expand_unit)->getPosition());
						}

						}
						}

						//////////////////////////////////////  �츮�� ���� ��ġ�� �ϱ� ��  //////




						*/

					}
				}


				if (BWAPI::Broodwar->self()->supplyUsed()/2 > 135 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 135)  // �������÷��� �� ����, �α����� 135 �̻��̰�, ���� �ո����� �Ծ����� ó��� ����.  �ƴϸ� �α����� 135 �̻�Ǹ� ������ ó���� 
				{
					total_attack = true;
					static int total_attack_start_time = Broodwar->getFrameCount();   //��Ż ������ ó�� �ð�.

					//�ϴ� ���ͷ� ����  total_attack_start_time
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
						Position *tmp = new Position(BWAPI::Broodwar->mapWidth()*32/2, BWAPI::Broodwar->mapHeight()*32/2);
						if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
						{

							(*its)->attack(*tmp); 
						}

						//chc �������÷��� ���� ����.
						if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
							(*its)->move(*tmp);

					}


					//���ݰ���  

					if(total_attack_start_time+24*16 < Broodwar->getFrameCount())  //���� �� �� 16�� �Ŀ� ������. �� �������� 8�ʸ��� ����ǹǷ� 16�� �Ŀ� ���ݰ���.   ���� ���ٰ� ���ݰ��°��� �� ó�� ���ݿ��� ����.
						for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
						{
							if(confidence_nice_enemy_unit_confidence_num < 300)
							{

								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack(this->informationManager->getEnemyStartLocation()->getPosition());
								}

								//chc �������÷��� ���� ����.
								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move(this->informationManager->getEnemyStartLocation()->getPosition());

							}


							//�� �ڽŰ��� ���� ������ ������ �������� ���ݰ���. �� �������� �ڽŰ� ���� �ٲ㼭 ���ֱ�.
							if(confidence_nice_enemy_unit_confidence_num >= 300) //�佺�� 300�̻�
							{
								if((*its)->getType().groundWeapon().damageAmount() >= 8) // �������� 8���� ũ�ٸ� . �������� �����ϱ� ����  ������ 8�� �ι������ϴ°���.
								{
									(*its)->attack((*confidence_nice_enemy_unit)->getPosition());
								}


								if((*its)->getType() == BWAPI::UnitTypes::Protoss_High_Templar)
									(*its)->move((*confidence_nice_enemy_unit)->getPosition());

							}
						}

				}
			}
			frametest_total_attack = frametest_total_attack+24*8;
		}






		////////////////////////�׽�Ʈ�� ��




		///////////////****����Ƽ�Ա� ����
		if(Broodwar->getFrameCount() >= 24*60*17 && multi_bool1 == false)   //17�п� �ϳ� ����.
		{
			baseManager->expand(1600);
			multi_bool1 = true;
		}

		if(Broodwar->getFrameCount() >= 24*60*19 && multi_bool2 == false)   //19�п� �ϳ� ����.
		{
			baseManager->expand(1620);
			multi_bool2 = true;
		}

		if(Broodwar->getFrameCount() >= 24*60*30 && multi_bool2 == false)   //30�п� 3�� ����.
		{
			baseManager->expand(1660);
			baseManager->expand(1670);
			baseManager->expand(1690);
			multi_bool2 = true;
		}



		///***********����Ƽ�Ա� ��


		/////*****�� ��Ƽ �˻� �� ���� ����
		int enemy_startlocation_exist_myunit = 0;  //�� ���� ��ó�� �츮 ������ ��� �ִ���
		static int tttaa_1=Broodwar->getFrameCount();
		if(tttaa_1==Broodwar->getFrameCount())
		{
			tttaa_1 = tttaa_1 + 72; //3�ʿ� �ѹ��� ����

			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{

				if((*its)->getDistance(en_start) < 80)
				{
					enemy_startlocation_exist_myunit++; // �� ���� ��ó�� �츮 ���� ������.
				}
			}
		}

		if(enemy_startlocation_exist_myunit>=5)
			enemy_dead=true;

		if(enemy_dead && !first_tt22)  //���� �������� �� �������� �����Ѵ�. �ѹ��� ���ֱ����� bool ���� ���
		{
			enemy_dead_frame = Broodwar->getFrameCount(); 
			first_tt22 = true;

		}

		if(Broodwar->getFrameCount() > enemy_dead_frame + 24*60*3 )  //�� ���� �� 2���̻� �������� true
			enemy_dead_after_2min = true;



		/////////****�� ��Ƽ �˻� �� ���� ����////////

		if(enemy_dead_after_2min)  //���� �� ����ģ �� . 3 �� ��
		{

			if(!base_lo_first_input)
			{
				base_lo = BWTA::getBaseLocations().begin();
				base_lo_first_input=true;	
			}	


			static int frame_expa_attack=Broodwar->getFrameCount();
			if(frame_expa_attack==Broodwar->getFrameCount())
			{
				frame_expa_attack = frame_expa_attack + 24; //1�ʿ� �ѹ��� ����.

				if(base_lo != BWTA::getBaseLocations().end())
				{
					for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
					{
						if(!(*its)->hasPath((*base_lo)->getPosition())) //������ �� �ִ� �����̶��(���� �ƴ϶��) ���̽� �������� �ѱ�� �극��ũ.
						{
							base_lo++;
							break;
						}


						if((*its)->getType().groundWeapon().damageAmount() >= 8)  //��������
						{
							(*its)->move((*base_lo)->getPosition()); //�� ���̽��� �̵�


							if((*its)->getDistance((*base_lo)->getPosition()) < 50) // �� ���̽��� �����ߴٸ� ���̽������̼� �ø��� ��������.
							{
								base_lo++;
								break;
							}

							for (std::set<BWAPI::Unit *>::const_iterator enemys = BWAPI::Broodwar->enemy()->getUnits().begin(); enemys != BWAPI::Broodwar->enemy()->getUnits().end(); ++enemys)
							{
								(*its)->attack((*enemys)->getPosition()); // ���� �ϳ��� �߰��ϸ� �� ����

							}


						}

					}
				}
			}

			if(base_lo==BWTA::getBaseLocations().end()) //�� ���̽������̼��� �����̸� �ٽ� ó������.  ��� ��ȯ�ϱ� ������. �� �Ǵ��� �׽�Ʈ�غ��� �߸��ϸ� ����������
				base_lo = BWTA::getBaseLocations().begin();

		}


		/////////****�� ��Ƽ �˻� �� ���� ��////////












		//�� ������ �ʹ� �ָ� ������ �ʵ��� ..  �����ؼ����� ���ư����� . ���߿� ��ũ����Ʈ�� ������ �����ؾ���.

		if(!total_attack && !zerg_first_attack)  //�Ѱ��ݸ���϶���. ����.   chc ���� zerg_first_attack
		{
			for (std::set<BWAPI::Unit *>::const_iterator allMyUnit = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit) 
			{

				if(!((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Probe))
				{
					if((*allMyUnit)->getType() == BWAPI::UnitTypes::Protoss_Nexus) 
					{
						//distEnemyNexus = (*allEnemyUnit)->getDistance(*allMyUnit);
						*myNexusPosition = (*allMyUnit)->getPosition();
					}


					//(*allMyUnit)->getDistance(
					BWAPI::Position pos = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();
					distMyNexus = (*allMyUnit)->getDistance(pos);	
					//Broodwar->drawTextScreen(420,100,"Nexus Distance : %lf , choke distance : %lf,  ground distance: %lf ", distMyNexus);
					//Broodwar->drawTextScreen(20,100,"Nexus Distance : %lf , choke distance : %lf,  ground distance: %lf ", *myNexusPosition);


					if( distMyNexus>1200 && (*allMyUnit)->getDistance(my_ex1) > 600 && (*allMyUnit)->getType() != BWAPI::UnitTypes::Protoss_Observer && (*allMyUnit)->getType() != BWAPI::UnitTypes::Protoss_Dark_Templar)
					{


						(*allMyUnit)->move(my_ex1);

						//�ֺ����ֵ鵵 ��ũ����Ʈ�� ����
						for (std::set<BWAPI::Unit *>::const_iterator allMyUnit2 = BWAPI::Broodwar->self()->getUnits().begin(); allMyUnit2 != BWAPI::Broodwar->self()->getUnits().end(); ++allMyUnit2) 
						{
							if((*allMyUnit2)->getType() == BWAPI::UnitTypes::Protoss_Zealot || (*allMyUnit2)->getType() == BWAPI::UnitTypes::Protoss_Dragoon)
								if((*allMyUnit)->getDistance(*allMyUnit2)<200) //cig2013
									(*allMyUnit2)->move(my_ex1);



						}







					}
				}
				// frametest2  =  frametest2 + 8;
			}
		}

		////////////////////////////////////////////////��



		/*
		if(total_attack)
		Broodwar->drawTextScreen(420,150,"true ");

		if(!total_attack)
		Broodwar->drawTextScreen(420,150,"false");


		*/

		//���������϶� �׽�Ʈ
		//	this->buildOrderManager->upgrade(1, UpgradeTypes::Leg_Enhancements, 391);

		//���� �����佺
		if(Broodwar->enemy()->getRace() == Races::Protoss) 
		{


			//��ũ�� �����ֱ�

			/*	if(dddd && spendManager->getUnitCount()->darkTemplar >= 2 )
			{
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{		
			std::set<BWAPI::Unit *>::const_iterator all = its;

			//	BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();

			BWAPI::Position poss = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();
			(*all)->rightClick(poss);

			}
			dddd = false;


			}

			*/


			//cig2013 ��ũ ���� ����
			/*
			if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dark_Templar) >= 2)
			{

			//��ũ�������� ����
			if(d)
			{
			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{		

			if ((*its)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{
			std::set<BWAPI::Unit *>::const_iterator dark = its;


			BWAPI::Position pos = this->informationManager->getEnemyStartLocation()->getPosition();
			(*dark)->rightClick(pos);
			//d = false;



			if((*dark)->getPosition().x() < pos.x() + 200 && (*dark)->getPosition().x() > pos.x() - 200 && (*dark)->getPosition().y() < pos.y() + 200 && (*dark)->getPosition().y() > pos.y() - 200)
			d = false;

			break; //�Ѹ����� ���ֱ� ����.

			}

			}


			}


			//�ؼ������� ����
			if(d5)
			{
			for (std::set<BWAPI::Unit *>::const_iterator pn = Broodwar->enemy()->getUnits().begin(); pn != BWAPI::Broodwar->enemy()->getUnits().end(); ++pn)
			{

			*/

			/*

			if((*pn)->getType() == BWAPI::UnitTypes::Protoss_Nexus)
			{

			for (std::set<BWAPI::Unit *>::const_iterator itss = BWAPI::Broodwar->self()->getUnits().begin(); itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss)
			{		

			if ((*itss)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{
			(*itss)->rightClick(*pn);
			}
			}
			}

			*/

			/*
			if((*pn)->getType() == BWAPI::UnitTypes::Protoss_Photon_Cannon)
			{
			for (std::set<BWAPI::Unit *>::const_iterator itss = BWAPI::Broodwar->self()->getUnits().begin(); itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss)
			{		

			if ((*itss)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{
			(*itss)->rightClick(*pn);
			}
			break; //�Ѹ����� ���ֱ� ����.

			}



			}


			else if((*pn)->getType() == BWAPI::UnitTypes::Protoss_Probe)
			{
			for (std::set<BWAPI::Unit *>::const_iterator itss = BWAPI::Broodwar->self()->getUnits().begin(); itss != BWAPI::Broodwar->self()->getUnits().end(); ++itss)
			{		

			if ((*itss)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{
			(*itss)->rightClick(*pn);
			}
			break; //�Ѹ����� ���ֱ� ����.

			}



			}

			}
			}

			}

			*/







			/*  cig2013 ��ũ�� ����

			if(armyManager->myDPS() > 6) // �������� �����ƿ��� 6���� ũ��(������ ���ݸ������ �������� ���ƿ��� �� ����)
			dd = false;
			if(this->armyManager->myDPS() > 6) // �������� �����ƿ��� 6���� ũ��(������ ���ݸ������ �������� ���ƿ��� �� ����)
			dd = false;

			//�������� ���ƿ���
			if(dd)
			{

			for (std::set<BWAPI::Unit *>::const_iterator its2 = BWAPI::Broodwar->self()->getUnits().begin(); its2 != BWAPI::Broodwar->self()->getUnits().end(); ++its2)
			{		

			if ((*its2)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{

			std::set<BWAPI::Unit *>::const_iterator dark2 = its2;
			if((*dark2)->isUnderAttack())
			{
			//d = false;
			//d5 = false;
			int i=0;

			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{		
			if((*its)->getType().groundWeapon().damageAmount() >= 8) //�������ָ� ��������
			{
			//	BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();

			BWAPI::Position poss = BWTA::getStartLocation(BWAPI::Broodwar->self())->getPosition();


			//(*its)->rightClick(poss); �������� ���ƿ��°� ����.
			}

			}
			//   BWAPI::Position chokePosition=myBorderVector[i]->getCenter();
			//Position *poss = new Position(2100,2100);	

			//���� ��ũ����Ʈ�� ���ƿ���


			//		BWAPI::Position chokePosition=myBorderVector[i]->getCenter();
			//		i++;
			//	 if (i>=(int)myBorderVector.size())

			//      i=0;


			for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
			{		

			if ((*its)->getType() == BWAPI::UnitTypes::Protoss_Dragoon)
			{
			BWAPI::Position posss = (*its)->getPosition();

			//(*dark2)->rightClick(posss); �������� ���ƿ��°� ����.


			//dd = false;
			//	ddd = false;

			}
			}	
			}
			}
			}
			//	 dd = false;
			//		ddd = false;
			}

			*/





			/*
			// �����佺�϶�
			if(Broodwar->enemy()->getRace() == Races::Protoss)  
			{


			//���� ���̸� ����

			for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
			{			
			if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
			{
			std::set<BWAPI::Unit *>::const_iterator zealot = it;
			BWAPI::Position pos = this->informationManager->getEnemyStartLocation()->getPosition();
			if ((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot || (*it)->getType() == BWAPI::UnitTypes::Protoss_Dragoon || (*it)->getType() == BWAPI::UnitTypes::Protoss_Dark_Templar)
			{                   std::set<BWAPI::Unit *>::const_iterator alot = it;


			for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
			{


			if(spendManager->getUnitCount()->zealot >= 10)
			(*alot)->attack(pos);
			}
			}
			}
			}

			}


			//

			*/
		}
		//�� �׶��϶�

		if(false)  //�ϴ� ����
		{
			if(Broodwar->enemy()->getRace() == Races::Terran)
			{
				//	if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Shuttle >= 3)



				/*		for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
				{		
				a = 0;

				if((*it)->getType() == BWAPI::UnitTypes::Protoss_Shuttle)
				{

				a++;
				}

				}*/


				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) < 3)
				{
					//�����¿��
					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Shuttle) >= 3)
					{

						for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
						{		
							if((*it)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
							{

								for (std::set<BWAPI::Unit *>::const_iterator it2 = BWAPI::Broodwar->self()->getUnits().begin(); it2 != BWAPI::Broodwar->self()->getUnits().end(); ++it2)
								{		


									if ((*it2)->getType() == BWAPI::UnitTypes::Protoss_Shuttle)
									{

										(*it)->load(*it2);
									}
								}
							}
						}
					}

					//�����¿��

					if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Shuttle) >= 3)
					{

						for (std::set<BWAPI::Unit *>::const_iterator it = BWAPI::Broodwar->self()->getUnits().begin(); it != BWAPI::Broodwar->self()->getUnits().end(); ++it)
						{		
							if((*it)->getType() == BWAPI::UnitTypes::Protoss_Reaver)
							{

								for (std::set<BWAPI::Unit *>::const_iterator it2 = BWAPI::Broodwar->self()->getUnits().begin(); it2 != BWAPI::Broodwar->self()->getUnits().end(); ++it2)
								{		


									if ((*it2)->getType() == BWAPI::UnitTypes::Protoss_Shuttle)
									{

										(*it)->load(*it2);
									}
								}
							}
						}
					}
				}



				//���Ϸ� 6�� �̻��� �� ���� ��ũ�� �� ä���
				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Pylon) >= 5)
					this->buildOrderManager->build(100,UnitTypes::Protoss_Scarab,800);


				//��������
				/*
				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) >= 3) 
				{
				for (std::set<BWAPI::Unit *>::const_iterator it7 = BWAPI::Broodwar->self()->getUnits().begin(); it7 != BWAPI::Broodwar->self()->getUnits().end(); ++it7)
				{	

				if ((*it7)->getType() == BWAPI::UnitTypes::Protoss_Reaver)
				{
				BWAPI::Position pos11 = informationManager->getEnemyStartLocation()->getPosition();
				(*it7)->attack(pos11);
				}
				}
				}

				*/



				//����Ʈ 3�� �̻��϶� ����
				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Gateway) >= 3) 
				{
					//BWAPI::Position pos[99999];
					int al = 0;

					for (std::set<BWAPI::Unit *>::const_iterator it3 = BWAPI::Broodwar->self()->getUnits().begin(); it3 != BWAPI::Broodwar->self()->getUnits().end(); ++it3)
					{	

						if ((*it3)->getType() == BWAPI::UnitTypes::Protoss_Shuttle)
						{
							if(ddddd)
							{

								BWAPI::Position pos10 = informationManager->getEnemyStartLocation()->getPosition();

								//	this->defenseManager->update().chokepoint2;
								(*it3)->rightClick(BWTA::getNearestChokepoint(pos10)->getCenter(),true);
								(*it3)->rightClick(pos10,true);

								/*  �� �ո���  �˾Ƴ��� �ҽ�
								BWAPI::Position pos101 = informationManager->getEnemyStartLocation()->getPosition();

								Position pp = BWTA::getNearestChokepoint(pos10)->getCenter();
								BWTA::getNearestBaseLocation(pp)->getPosition();

								*/






							}
						}
					}
					ddddd=false;

					//	if((*it3)->isMoving())
					//	ddddd = false;





					for (std::set<BWAPI::Unit *>::const_iterator it3 = BWAPI::Broodwar->self()->getUnits().begin(); it3 != BWAPI::Broodwar->self()->getUnits().end(); ++it3)

					{	
						if ((*it3)->getType() == BWAPI::UnitTypes::Protoss_Shuttle)
						{

							for (std::set<BWAPI::Unit *>::const_iterator n = Broodwar->enemy()->getUnits().begin(); n != BWAPI::Broodwar->enemy()->getUnits().end(); ++n)
							{

								if((*n)->getType() == BWAPI::UnitTypes::Terran_Bunker || (*n)->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode || (*n)->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode || (*n)->getType() == BWAPI::UnitTypes::Terran_Missile_Turret)
									//if((*n)->getType() == BWAPI::UnitTypes::Terran_SCV)
								{

									//BWAPI::Position pos10 = informationManager->getEnemyStartLocation()->getPosition();

									BWAPI::Position pos10 = informationManager->getEnemyStartLocation()->getPosition();
									//pos[al] = (*n)->getPosition();
									//al++;
									BWAPI::Position pos = (*n)->getPosition();
									//ddddd=false;

									if((*it3)->getPosition().x() > BWTA::getNearestChokepoint(pos10)->getCenter().x() - 900 && (*it3)->getPosition().x() < BWTA::getNearestChokepoint(pos10)->getCenter().x() + 900 && (*it3)->getPosition().y() > BWTA::getNearestChokepoint(pos10)->getCenter().y() - 900 && (*it3)->getPosition().y() < BWTA::getNearestChokepoint(pos10)->getCenter().y() + 900)
									{
										if((*it3)->getDistance(*n)<180)
										{


											for (std::set<BWAPI::Unit *>::const_iterator it4 = BWAPI::Broodwar->self()->getUnits().begin(); it4 != BWAPI::Broodwar->self()->getUnits().end(); ++it4)

											{	
												if ((*it4)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
												{


													(*it3)->unload(*it4);

												}

												if ((*it4)->getType() == BWAPI::UnitTypes::Protoss_Reaver)
												{


													(*it3)->unload(*it4);

												}
												//(*it3)->getDistance(*n);
												//	Broodwar->drawTextScreen(5,30,"I have %d units:", (*it3)->getDistance(*n));
											}							

										}
									}


									//				std::set<BWAPI::Unit *>::const_iterator dark = its;

								}

							}



						}
					}



				}

			}
		}


		if (Broodwar->isReplay()) return;
		if (!this->analyzed) return;

		//�κ�ƽ�� �������ؼ�.  cig2013 �̰� ����?
		if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) > 3 && Broodwar->self()->minerals() <= 215 ) //��� 4���� �̻��̰�, �̳׶��� 215 �����̸� �������� �Ŵ����� ����
		{
			;
		}
		else
		{
			this->buildManager->update();
			this->buildOrderManager->update();
		}

		this->baseManager->update();


		this->workerManager->update();//chc

		//this->techManager->update();
		this->upgradeManager->update();

		//if(my_auto_build) // ������尡 true�̸� �׶����� ���Ϸ� �ڵ����� ������
		//this->supplyManager->update(); //chc

		this->moodManager->update();
		this->spendManager->update();
		this->scoutManager->update();
		if (!this->informationManager->getEnemyBases().empty() && Broodwar->getFrameCount() > 3000)
		{
			//if(!total_attack)  //total_attack�̸� ���潺�Ŵ��� ��. ��ũ����Ʈ�� �̵��ϴ°� ������.

			//���ݰ��� ���潺�Ŵ��� ����

			if(Broodwar->enemy()->getRace() == Races::Zerg) //
			{

				if(zerg_first_attack == false && defense_ing == false) // ���� ����� �������� ��. �׸��� �������� �ƴ� ��
					this->defenseManager->update();

				//�̰� Ȯ��
				if(BWAPI::Broodwar->self()->allUnitCount(BWAPI::UnitTypes::Protoss_Dragoon) >= 1)
					zerg_first_attack = false;

				if(BWAPI::Broodwar->self()->supplyUsed()/2>135)
					zerg_first_attack = true;

			}

			else if(Broodwar->enemy()->getRace() == Races::Protoss)
			{
				if (!(BWAPI::Broodwar->self()->supplyUsed()/2 > 143 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 185) && defense_ing == false) //���ݽ� �׸��� �������� �ƴ� �� ���潺�Ŵ��� Ŵ
				{
					this->defenseManager->update();
				}

			}

			else if(Broodwar->enemy()->getRace() == Races::Terran)
			{
				if(!(BWAPI::Broodwar->self()->supplyUsed()/2 > 135 && high_templer_loaded_complete || BWAPI::Broodwar->self()->supplyUsed()/2 > 185) && defense_ing == false) //���ݽ� �׸��� �������� �ƴ� �� ���潺�Ŵ��� Ŵ
				{
					this->defenseManager->update();

				}
			}

			/*
			if (!this->spyManager->isInitialized())
			this->spyManager->initialize();
			this->spyManager->update();
			*/  //chc


		}



		//�ո������� ���� ���� �ϱ�

		//����
		/*
		if(very_early_rush && !my_exten)
		for (std::set<BWAPI::Unit *>::const_iterator its = BWAPI::Broodwar->self()->getUnits().begin(); its != BWAPI::Broodwar->self()->getUnits().end(); ++its)
		{
		if((*its)->getType() == BWAPI::UnitTypes::Protoss_Zealot)
		{
		(*its)->attack(my_ex1);
		}
		}


		*/


		//this->enhancedUI->update();
		this->borderManager->update();
		//this->underAttackManager->update();
		this->armyManager->update();
		this->arbitrator.update();

		if ((Broodwar->mapName().compare(1,11,"Destination")  == 0) && !destinationMineralSpotted)
		{
			destinationMineralSpotted = true;
			Position *p;

			//Low position
			if (BWAPI::Broodwar->self()->getStartLocation().y() > 50)
			{
				p = new Position(1312,3856);
			}
			//High position
			else
			{
				p = new Position(1760,208);
			}
			for each (BWAPI::Unit *u in Broodwar->getAllUnits())
			{
				if ((u->getType() == BWAPI::UnitTypes::Resource_Mineral_Field) && (u->getPosition().x() == p->x()) && (u->getPosition().y() == p->y()))
				{
					workerManager->setDestinationMineral(u);
					break;
				}
			}
			delete p;
		}



		if (debugMode)
		{
			/*
			Broodwar->drawTextScreen(420,30,"DPS: %.2f", armyManager->myDPS());
			Broodwar->drawTextScreen(420,40,"Zealots:        %3d%% / %3d%%", (int)(spendManager->getUnitCount()->zealotRatio*100), (int)(spendManager->getUnitCount()->zealotIdealRatio*100));
			Broodwar->drawTextScreen(420,50,"Dragoons:      %3d%% / %3d%%", (int)(spendManager->getUnitCount()->dragoonRatio*100), (int)(spendManager->getUnitCount()->dragoonIdealRatio*100));
			Broodwar->drawTextScreen(420,60,"Corsairs:       %3d%% / %3d%%", (int)(spendManager->getUnitCount()->corsairRatio*100), (int)(spendManager->getUnitCount()->corsairIdealRatio*100));
			Broodwar->drawTextScreen(420,70,"Dark Templars: %3d%% / %3d%%", (int)(spendManager->getUnitCount()->darkTemplarRatio*100), (int)(spendManager->getUnitCount()->darkTemplarIdealRatio*100));

			*/
		}



		//Broodwar->drawTextScreen(5,0,"MY dps :   %dEnemy dps :%d ", this->armyManager->myDPS(), this->armyManager->enemyDPS());



		/*chc ���κ� ���̻��� �ϴ°� .. ���߿� 
		if ((Broodwar->self()->allUnitCount(UnitTypes::Protoss_Probe) < 5))
		this->buildOrderManager->buildAdditional(1,UnitTypes::Protoss_Probe,90);

		*/
		/*
		//chc
		for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
		{
		if ((*i)->getType().isWorker())
		{
		//BWAPI::Unit* u = b->builderUnit;
		Position *q = new Position(1760,208);;
		(*i)->rightClick(*q);
		}
		}
		//
		*/
		//chc

		if(Broodwar->enemy()->getRace() == Races::Protoss)
			if (Broodwar->self()->allUnitCount(UnitTypes::Protoss_Probe) ==  9) //�������� �ð� �����ֱ� cig2013-- 9�� ����
			{		
				this->scoutManager->setScoutCount(1);

			}

			if(Broodwar->enemy()->getRace() == Races::Terran)
				if (Broodwar->self()->allUnitCount(UnitTypes::Protoss_Probe) ==  9) //�������� �ð� �����ֱ� cig2013-- 9�� ����
				{		
					this->scoutManager->setScoutCount(1);
				}


				if(Broodwar->enemy()->getRace() == Races::Zerg)
					if (Broodwar->self()->allUnitCount(UnitTypes::Protoss_Probe) ==  9) //�������� �ð� �����ֱ� cig2013-- 9�� ����
					{		
						this->scoutManager->setScoutCount(1);
					}





					std::set<Unit*> units=Broodwar->self()->getUnits();
					if (this->showManagerAssignments)
					{
						for(std::set<Unit*>::iterator i=units.begin();i!=units.end();i++)
						{
							if (this->arbitrator.hasBid(*i))
							{
								int x=(*i)->getPosition().x();
								int y=(*i)->getPosition().y();
								std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*,double>*, double> > bids=this->arbitrator.getAllBidders(*i);
								int y_off=0;
								bool first = false;
								const char activeColor = '\x07', inactiveColor = '\x16';
								char color = activeColor;
								for(std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*,double>*, double> >::iterator j=bids.begin();j!=bids.end();j++)
								{
									//Broodwar->drawTextMap(x,y+y_off,"%c%s: %d",color,j->first->getShortName().c_str(),(int)j->second);
									y_off+=15;
									color = inactiveColor;
								}
							}		
						}
					}
	}
}
void Protoss_Multi::onUnitDestroy(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) return;
	this->arbitrator.onRemoveObject(unit);
	this->buildManager->onRemoveUnit(unit);
	this->techManager->onRemoveUnit(unit);
	this->upgradeManager->onRemoveUnit(unit);
	this->workerManager->onRemoveUnit(unit);  
	this->scoutManager->onRemoveUnit(unit);
	this->spyManager->onRemoveUnit(unit);
	this->defenseManager->onRemoveUnit(unit);
	this->informationManager->onUnitDestroy(unit);
	this->baseManager->onRemoveUnit(unit);
	this->underAttackManager->onRemoveUnit(unit);
	this->armyManager->onRemoveUnit(unit);
}

void Protoss_Multi::onUnitDiscover(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) return;
	this->informationManager->onUnitDiscover(unit);
	this->unitGroupManager->onUnitDiscover(unit);
}
void Protoss_Multi::onUnitEvade(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) return;
	this->informationManager->onUnitEvade(unit);
	this->unitGroupManager->onUnitEvade(unit);
}

void Protoss_Multi::onUnitMorph(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) return;
	this->unitGroupManager->onUnitMorph(unit);
}
void Protoss_Multi::onUnitRenegade(BWAPI::Unit* unit)
{
	if (Broodwar->isReplay()) return;
	this->unitGroupManager->onUnitRenegade(unit);
}



void Protoss_Multi::onSendText(std::string text)
{
	if (Broodwar->isReplay())
	{
		Broodwar->sendText("%s",text.c_str());
		return;
	}
	UnitType type=UnitTypes::getUnitType(text);
	if (text=="debug")
	{
		if (this->showManagerAssignments==false)
		{
			this->showManagerAssignments=true;
			this->buildOrderManager->setDebugMode(true);
			this->scoutManager->setDebugMode(true);
			this->spyManager->setDebugMode(true);
			debugMode = true;
		}
		else
		{
			this->showManagerAssignments=false;
			this->buildOrderManager->setDebugMode(false);
			this->scoutManager->setDebugMode(true); //chc
			this->spyManager->setDebugMode(false);
			debugMode = false;
		}
		Broodwar->printf("%s",text.c_str());
		return;
	}
	if (text=="expand")
	{
		this->baseManager->expand();
		Broodwar->printf("%s",text.c_str());
		return;
	}
	if (type!=UnitTypes::Unknown)
	{
		this->buildOrderManager->buildAdditional(1,type,300);
	}
	else
	{
		TechType type=TechTypes::getTechType(text);
		if (type!=TechTypes::Unknown)
		{
			this->techManager->research(type);
		}
		else
		{
			UpgradeType type=UpgradeTypes::getUpgradeType(text);
			if (type!=UpgradeTypes::Unknown)
			{
				this->upgradeManager->upgrade(type);
			}
			else
				Broodwar->printf("You typed '%s'!",text.c_str());
		}
	}
	Broodwar->sendText("%s",text.c_str());
}


