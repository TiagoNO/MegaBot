#include "Expand.h"
#include <math.h>
using namespace BWAPI;

typedef struct InfoMinerais
{
	int PosiX;
	int PosiY;
	int Id;
	int NumBase;
}InfoMineral;

typedef struct CelulaMinerais
{
	InfoMineral Info;
	struct CelulaMinerais *prox;
}CelulaM;

typedef struct InfoBases
{
	int PosiX;
	int PosiY;
	int Id;
	int Trabalhadores;
	int CampoMinerais;
	int NumBase;
	bool BaseCriada;
	int TrabPorMineral;
}InfoBase;

typedef struct CelulasLista
{
	InfoBase Info;
	CelulaM *Minerais;
	struct CelulasLista *prox;
}Celula;

int dist(int x1,int y1,int x2,int y2)
{
	int a = ((x1-x2)*(x1-x2));
	int b = ((y1-y2)*(y1-y2));
	return (int)sqrt((double)a+b);
}

CelulaM * InicializaMinerais()
{
	CelulaM *NovoMineral;
	NovoMineral = (CelulaM *)malloc(sizeof(CelulaM));
	NovoMineral->Info.Id = -1;
	NovoMineral->Info.NumBase = -1;
	NovoMineral->Info.PosiX = -1;
	NovoMineral->Info.PosiY = -1;
	NovoMineral->prox = NULL;
	return NovoMineral;
}

void AdicionaMinerais(CelulaM *CelulaFinal,InfoMineral Info)
{
	CelulaM *NovoMineral;
	NovoMineral = (CelulaM *)malloc(sizeof(CelulaM));
	NovoMineral->Info.Id = Info.Id;
	NovoMineral->Info.PosiX = Info.PosiX;
	NovoMineral->Info.PosiY = Info.PosiY;
	NovoMineral->Info.NumBase = Info.NumBase;
	NovoMineral->prox = NULL;
	CelulaFinal->prox = NovoMineral;
}
Celula * InicializaBase()
{
	Celula *Bases;
	Bases = (Celula *)malloc(sizeof(Celula));
	Bases->Info.Trabalhadores = 0;
	Bases->Info.CampoMinerais = 0;
	Bases->Info.NumBase = 1;
	Bases->Info.TrabPorMineral = 0;
	Bases->Info.BaseCriada = true;
	Bases->Minerais = InicializaMinerais();
	Bases->Info.Id = -1;
	Bases->Minerais->Info.NumBase = Bases->Info.NumBase;
	Bases->Minerais->prox = NULL;
	Bases->prox = NULL;
	return Bases;
}

void AdicionaBase(Celula *CelulaFinal,InfoBase Info)
{
	Celula *NovaBase;
	NovaBase = (Celula *)malloc(sizeof(Celula));
	NovaBase->Info.Id = Info.Id;
	NovaBase->Info.PosiX = Info.PosiX;
	NovaBase->Info.PosiY = Info.PosiY;
	NovaBase->Info.BaseCriada = Info.BaseCriada;
	NovaBase->Info.CampoMinerais = Info.CampoMinerais;
	NovaBase->Info.NumBase = Info.NumBase;
	NovaBase->Info.Trabalhadores = Info.Trabalhadores;
	NovaBase->Info.TrabPorMineral = Info.TrabPorMineral;
	CelulaFinal->prox = NovaBase;
	NovaBase->Minerais = InicializaMinerais();
	NovaBase->Minerais->Info.Id = Info.Id;
	NovaBase->Minerais->Info.NumBase = NovaBase->Info.NumBase;
	NovaBase->Minerais->Info.PosiX = Info.PosiX;
	NovaBase->Minerais->Info.PosiY = Info.PosiY;
	NovaBase->prox = NULL;
}

void ImprimirBases(Celula *Bases)
{
	Celula *aux;
	CelulaM *aux2;
	aux = Bases;
	while(aux != NULL)
	{
		Broodwar->drawCircle(CoordinateType::Map,aux->Info.PosiX*32,aux->Info.PosiY*32,15,Colors::Red,false);
		Broodwar->sendText("Base: %i %i %i",aux->Info.PosiX,aux->Info.PosiY,aux->Info.BaseCriada);
		aux2 = aux->Minerais;
		while(aux2 != NULL)
		{
			Broodwar->sendText("Mineral: %i %i",aux2->Info.Id,aux2->Info.NumBase);
			aux2 = aux2->prox;
		}
		aux = aux->prox;
	}
}
int NaBase(Celula *Bases,Unit *Mineral)
{
	int achou = 0,achou2 = 0;
	int NumBases = 1;
	Celula *aux;
	aux = Bases;
	while(aux->prox != NULL)
	{
		Broodwar->sendText("(%i %i  - %i %i)%i",aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y(),dist(aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y()));
		if(dist(aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y()) <= 20) // pesquisa se o mineral esta proximo de alguma base
		{
			achou = 1;
			break;
		}
		NumBases++;
		aux = aux->prox;
	}
	if(dist(aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y()) <= 20) // verifica o ultimo na lista
	{
		Broodwar->sendText("(%i %i  - %i %i)%i",aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y(),dist(aux->Info.PosiX,aux->Info.PosiY,Mineral->getTilePosition().x(),Mineral->getTilePosition().y()));
		achou = 1;
	}
	if(achou) // se achou a base onde o mineral possa estar
	{
		CelulaM *aux2;
		aux2 = aux->Minerais;
		while(aux2->prox != NULL)  // verifica se ele já esta na base
		{
			if(aux2->Info.Id == Mineral->getID())
			{
				achou2 = 1;
				break;
			}
			aux2 = aux2->prox;
		}
		if(aux2->Info.Id == Mineral->getID()) // verifica o ultimo item da lista de minerais da base 
		{
			achou2 = 1;
		}
		if(achou2)  // se ele já esta na base, apenas retorna
		{
			return 0;
		}
		else if(!achou2)  // se ele não esta na base, então devemos adicionar ele ao final da lista de minerais da base
		{
			InfoMinerais Info;
			Info.Id = Mineral->getID();
			Info.PosiX = Mineral->getTilePosition().x();
			Info.PosiY = Mineral->getTilePosition().y();
			Info.NumBase = NumBases;
			AdicionaMinerais(aux2,Info);
			return 1;
		}
	}
	else if(!achou)  // // se ele não esta perto de nenhuma base, então iremos adicionar na lista de bases esse novo mineral
	{
		InfoBase Info;
		Info.PosiX = Mineral->getTilePosition().x();
		Info.PosiY = Mineral->getTilePosition().y();
		Info.BaseCriada = false;
		Info.CampoMinerais = 1;
		Info.Trabalhadores = 0;
		Info.Id = Mineral->getID();
		Info.NumBase = NumBases++;
		Info.TrabPorMineral = 0;
		AdicionaBase(aux,Info);
		return 2;
	}
}

TilePosition ProcurarBase(Celula *Bases)
{
	Celula *aux;
	aux = Bases;
	TilePosition aux2;
	while(aux != NULL)
	{
		if(aux->Info.BaseCriada == false)
		{
			aux2 = TilePosition(aux->Info.PosiX,aux->Info.PosiY);
			return aux2;
		}
		aux = aux->prox;
	}
	aux2 = TilePositions::None;
	return aux2;
}

bool VerificaExistenciaBase(Celula *Bases)
{
	Celula *aux;
	aux = Bases;
	while(aux != NULL)
	{
		if(aux->Info.BaseCriada == false)
		{
			return true;
		}
		aux = aux->prox;
	}
	return false;
}

Celula * TaxaTrabalhadores(Celula *Bases,Unit *u)
{
	Celula *aux;
	aux = Bases;
	while(aux != NULL)
	{
		if(aux->Info.Id == u->getID())
		{
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}

TilePosition PesquisarNovaBase(Celula *Bases)
{
	Celula *aux;
	aux = Bases;
	while(aux != NULL)
	{
		if(aux->Info.BaseCriada == false)
		{
			return TilePosition(aux->Info.PosiX,aux->Info.PosiY);
		}
		aux = aux->prox;
	}
	return TilePosition(0,0);
}

void BalancearBases(Celula *Bases)
{

}


bool hasAnalysed;
bool analysisJustFinished;
BWTA::Region* baseHome;
BWTA::Region* enemyBase;
int NumBases;
Celula *Bases;
int IdExplorador = -1;
bool Construido;
int Trabalhadores;
int PotencialUnidades;
int Construtor;
TilePosition NovaBase;
bool achou;
bool Posicao;
int lastFrame;

void Expand::onStart()
{
  NumBases = 1;
  Bases = InicializaBase();
  Bases->Info.NumBase = 1;
  Bases->Info.CampoMinerais = 8;
  Bases->Info.BaseCriada = true;
  Construido = false;
  achou = false;
  Trabalhadores = 4;
  PotencialUnidades = 9;
  Construtor = -1;
  achou = false;
  Posicao = false;

  Broodwar->printf("The map is %s, a %d player map",Broodwar->mapName().c_str(),Broodwar->getStartLocations().size());
  // Enable some cheat flags
  Broodwar->enableFlag(Flag::UserInput);
  // Uncomment to enable complete map information
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  //read map information into BWTA so terrain analysis can be done in another thread
  BWTA::readMap();
  hasAnalysed=false;
  analysisJustFinished=false;

  show_bullets=false;
  show_visibility_data=false;

  if (Broodwar->isReplay())
  {
    Broodwar->printf("The following players are in this replay:");
    for(std::set<Player*>::iterator p=Broodwar->getPlayers().begin();p!=Broodwar->getPlayers().end();p++)
    {
      if (!(*p)->getUnits().empty() && !(*p)->isNeutral())
      {
        Broodwar->printf("%s, playing as a %s",(*p)->getName().c_str(),(*p)->getRace().getName().c_str());
      }
    }
  }
  else
  {
    Broodwar->printf("The match up is %s v %s",
      Broodwar->self()->getRace().getName().c_str(),
      Broodwar->enemy()->getRace().getName().c_str());

    //send each worker to the mineral field that is closest to it
    for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
    {
      if ((*i)->getType().isWorker())
      {
		if(IdExplorador == -1)
		{
			IdExplorador = (*i)->getID();
			int x = rand()%(Broodwar->mapWidth()*32);
			int y = rand()%(Broodwar->mapHeight()*32);
			Position movimento = Position(x,y);
			Broodwar->sendText("% %i (x,y)",x,y);
			(*i)->move(movimento);
		}
		if(Construtor == -1 && (*i)->getID() != IdExplorador)
		{
			Construtor = (*i)->getID();
		}
		Bases->Info.Trabalhadores++;
        Unit* closestMineral=NULL;
        for(std::set<Unit*>::iterator m=Broodwar->getMinerals().begin();m!=Broodwar->getMinerals().end();m++)
        {
          if (closestMineral==NULL || (*i)->getDistance(*m)<(*i)->getDistance(closestMineral))
            closestMineral=*m;
        }
        if (closestMineral!=NULL && (*i)->getID() != IdExplorador)
          (*i)->rightClick(closestMineral);
      }
      else if ((*i)->getType().isResourceDepot())
      {
		Bases->Info.PosiX = (*i)->getTilePosition().x();
		Bases->Info.PosiY = (*i)->getTilePosition().y();
		Bases->Info.Id = (*i)->getID();
        //if this is a center, tell it to build the appropiate type of worker
        if ((*i)->getType().getRace()!=Races::Zerg)
        {
		  
		  Bases->Info.Trabalhadores++;
          (*i)->train(Broodwar->self()->getRace().getWorker());
        }
        else //if we are Zerg, we need to select a larva and morph it into a drone
        {
          std::set<Unit*> myLarva=(*i)->getLarva();
          if (myLarva.size()>0)
          {
            Unit* larva=*myLarva.begin();
            larva->morph(UnitTypes::Zerg_Drone);
			Bases->Info.Trabalhadores++;
		  }
        }
		Bases->Info.TrabPorMineral = Bases->Info.Trabalhadores/Bases->Info.CampoMinerais;
      }
    }
  }
}

void Expand::onEnd(bool isWinner)
{
  if (isWinner)
  {
    //log win to file
  }
}

void Expand::onFrame()
{
  //ImprimirBases(Bases);
  //localMineral = PesquisarNovaBase();
  if (show_visibility_data)
    drawVisibilityData();

  if (show_bullets)
    drawBullets();
  
  if (Broodwar->isReplay())
    return;

  drawStats();
  if (hasAnalysed && Broodwar->getFrameCount()%30==0)
  {
    //order one of our workers to guard our chokepoint.
    for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
    {
      if ((*i)->getType().isWorker())
      {
		  //get the chokepoints linked to our baseHome region
        std::set<BWTA::Chokepoint*> chokepoints= baseHome->getChokepoints();
        double min_length=10000;
        BWTA::Chokepoint* choke=NULL;

        //iterate through all chokepoints and look for the one with the smallest gap (least width)
        for(std::set<BWTA::Chokepoint*>::iterator c=chokepoints.begin();c!=chokepoints.end();c++)
        {
          double length=(*c)->getWidth();
          if (length<min_length || choke==NULL)
          {
            min_length=length;
            choke=*c;
          }
        }
        //order the worker to move to the center of the gap
        (*i)->rightClick(choke->getCenter());
        break;
      }
    }
  }
  if (hasAnalysed)
    drawTerrainData();

  if (analysisJustFinished)
  {
    Broodwar->printf("Finished analyzing map.");
    analysisJustFinished=false;
  }
  //ImprimirBases(Bases);
  for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
  {
	//Broodwar->sendText("%i %i",(*i)->getID(),IdExplorador);
	if ((*i)->getType().isWorker())
    {
		if(Construtor == -1)
		{
			Construtor = (*i)->getID();
		}
		if(IdExplorador == (*i)->getID() && (*i)->isIdle())
		{
			int x = rand()%(Broodwar->mapWidth()*32);
			int y = rand()%(Broodwar->mapHeight()*32);
			Position movimento = Position(x,y);
			Broodwar->sendText("%i %i (x,y)",x,y);
			(*i)->move(movimento);
		}
		if(Broodwar->self()->minerals() >= Broodwar->self()->getRace().getCenter().mineralPrice() && !Construido)
		{
			NovaBase = PesquisarNovaBase(Bases);
			//Broodwar->sendText("%i (%i,%i)",Construido,NovaBase.x(),NovaBase.y());
			if(NovaBase != TilePosition(0,0))
			{
				Broodwar->sendText("Base %i %i",NovaBase.x(),NovaBase.y());
				Construido = true;
			}
		}
		if((*i)->isIdle())
		{
			Unit *closestMineral = NULL;
			for(std::set<Unit*>::iterator m=Broodwar->getMinerals().begin();m!=Broodwar->getMinerals().end();m++)
			{
				if (closestMineral == NULL || (*i)->getDistance(*m)<(*i)->getDistance(closestMineral))
					closestMineral=*m;
			}
			if(closestMineral != NULL && (*i)->getID() != IdExplorador && (*i)->getID() != Construtor)
			{
				(*i)->gather(closestMineral);
			}
			if((*i)->getID() == Construtor && !Construido)
			{
				(*i)->gather(closestMineral);
			}
		}
		if(!(*i)->isCarryingMinerals() && !(*i)->isCarryingGas())
		{
			if(Broodwar->self()->allUnitCount(UnitTypes::AllUnits) > PotencialUnidades - 3)
			{
				int x = Bases->Info.PosiX;
				int y = Bases->Info.PosiY;
				x = x + Broodwar->self()->getRace().getSupplyProvider().tileWidth()  + ((rand()%15));
				y = y + Broodwar->self()->getRace().getSupplyProvider().tileHeight() + ((rand()%15));
				Broodwar->drawCircleMap(x,y,10,Colors::Red,false);
				if(Broodwar->self()->getRace() == Races::Terran && Broodwar->self()->minerals() > UnitTypes::Terran_Supply_Depot.mineralPrice() + 100)
				{
					if(!(*i)->build(TilePosition(x,y),UnitTypes::Terran_Supply_Depot))
					{
					}
					else
					{

						PotencialUnidades = PotencialUnidades + 8;
					}
						
				}
				else if(Broodwar->self()->getRace() == Races::Protoss && Broodwar->self()->minerals() > UnitTypes::Protoss_Pylon.mineralPrice() + 100)
				{
					if(Broodwar->self()->getRace() == Races::Protoss)
					{
						if(!(*i)->build(TilePosition(x,y),UnitTypes::Protoss_Pylon))
						{
						}
						else
						{
							PotencialUnidades = PotencialUnidades + 8;
						}
					}
				}
			}
		}
		if((*i)->getID() == Construtor)
		{
			Broodwar->drawCircle(CoordinateType::Map,(*i)->getPosition().x(),(*i)->getPosition().y(),10,Colors::Red,false);
			if(Construido)
			{
				TilePosition aux;
				Broodwar->drawCircle(CoordinateType::Map,NovaBase.x(),NovaBase.y(),10,Colors::Red,false);
				if((*i)->isIdle() && !Posicao)
				{
					if(NovaBase.x() > Broodwar->mapWidth()/2)
					{
						if(NovaBase.y() > Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + (-1)*rand()%10,NovaBase.y() + (-1)*rand()%10);
						}
						else if(NovaBase.y() <= Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + (-1)*rand()%10,NovaBase.y() + rand()%10);
						}
					}
					else if(NovaBase.x() <= Broodwar->mapWidth()/2)
					{
						if(NovaBase.y() > Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + rand()%10,NovaBase.y() + (-1)*rand()%10);
						}
						else if(NovaBase.y() <= Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + rand()%10,NovaBase.y() + rand()%10);
						}
					}
					if(dist((*i)->getTilePosition().x(),(*i)->getTilePosition().y(),NovaBase.x(),NovaBase.y()) <= 4 && achou)
					{
						NovaBase = aux;
						Posicao = true;
						Broodwar->sendText("oaoaosasoaos");
					}
				}
				else
				{
					if(NovaBase.x() > Broodwar->mapWidth()/2 && !achou)
					{
						if(NovaBase.y() > Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + (-1)*rand()%5,NovaBase.y() + (-1)*rand()%5);
						}
						else if(NovaBase.y() <= Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + (-1)*rand()%5,NovaBase.y() + rand()%5);
						}
					}
					else if(NovaBase.x() <= Broodwar->mapWidth()/2 && !achou)
					{
						if(NovaBase.y() > Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + rand()%5,NovaBase.y() + (-1)*rand()%5);
						}
						else if(NovaBase.y() <= Broodwar->mapHeight()/2)
						{
							aux = TilePosition(NovaBase.x() + rand()%5,NovaBase.y() + rand()%5);
						}
					}
					if(dist((*i)->getTilePosition().x(),(*i)->getTilePosition().y(),NovaBase.x(),NovaBase.y()) >= 4 && !achou)
					{
						Broodwar->drawCircle(CoordinateType::Map,aux.x()*32,aux.y()*32,10,Colors::Red,false);
						Broodwar->sendText("%i",dist((*i)->getTilePosition().x(),(*i)->getTilePosition().y(),NovaBase.x(),NovaBase.y()));
						(*i)->move(Position(aux.x()*32,aux.y()*32));
					}
					if(dist((*i)->getTilePosition().x(),(*i)->getTilePosition().y(),NovaBase.x(),NovaBase.y()) < 4 && !achou)
					{
						achou = true;
						(*i)->stop();
					}
				}
				Broodwar->drawCircle(CoordinateType::Map,aux.x()*32,aux.y()*32,10,Colors::Red,false);
				if(Posicao)
				{
					(*i)->build(aux,Broodwar->self()->getRace().getCenter());
					Posicao = false;
					achou = false;
					Construido = false;
					Construtor = -1;
				}				
			}

		}
	}
	if((*i)->getType().isResourceDepot() && Trabalhadores < 60 && !(*i)->isBeingConstructed() && (*i)->isCompleted())
	{
		Celula *aux;
		aux = TaxaTrabalhadores(Bases,(*i));
		if(aux->Info.TrabPorMineral < 2 && (*i)->isIdle() && aux != NULL)
		{
			if(Broodwar->self()->minerals() >= Broodwar->self()->getRace().getWorker().mineralPrice())
			{
				if((*i)->train(Broodwar->self()->getRace().getWorker()))
				{
					aux->Info.Trabalhadores++;
					aux->Info.TrabPorMineral = aux->Info.Trabalhadores/aux->Info.CampoMinerais;
					Trabalhadores++;
					Broodwar->sendText("%i %i %i",aux->Info.TrabPorMineral,aux->Info.Trabalhadores,Trabalhadores);
					aux = NULL;
					free(aux);
				}
			}		
		}
	}
  }
}

void Expand::onSendText(std::string text)
{
  if (text=="/show bullets")
  {
    show_bullets = !show_bullets;
  } else if (text=="/show players")
  {
    showPlayers();
  } else if (text=="/show forces")
  {
    showForces();
  } else if (text=="/show visibility")
  {
    show_visibility_data=!show_visibility_data;
  } else if (text=="/analyze")
  {
    if (hasAnalysed == false)
    {
      Broodwar->printf("Analyzing map... this may take a minute");
      CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BWTA_AnalyzeThread, NULL, 0, NULL);
    }
  } else
  {
    Broodwar->printf("You typed '%s'!",text.c_str());
    Broodwar->sendText("%s",text.c_str());
  }
}

void Expand::onReceiveText(BWAPI::Player* player, std::string text)
{
  Broodwar->printf("%s said '%s'", player->getName().c_str(), text.c_str());
}

void Expand::onPlayerLeft(BWAPI::Player* player)
{
  Broodwar->sendText("%s left the game.",player->getName().c_str());
}

void Expand::onNukeDetect(BWAPI::Position target)
{
  if (target!=Positions::Unknown)
    Broodwar->printf("Nuclear Launch Detected at (%d,%d)",target.x(),target.y());
  else
    Broodwar->printf("Nuclear Launch Detected");
}

void Expand::onUnitDiscover(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
  {
    //Broodwar->sendText("A %s [%x] has been discovered at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
	if(unit->getType().isMineralField())
	{
		Broodwar->drawCircle(BWAPI::CoordinateType::Screen,unit->getPosition().x(),unit->getPosition().y(),100,Colors::Green,false);
		int retorno;
		retorno = NaBase(Bases,unit);
		if(retorno == 0)
		{
			Broodwar->sendText("Já foi adicionado a essa base!");
		}
		else if(retorno == 1)
		{
			Broodwar->sendText("Inexistente nessa base, Foi adicionada a ela!");
		}
		else if(retorno == 2)
		{
			Broodwar->sendText("Nova base encontrada! Adicionada a lista de bases!");
		}
	}
  }
}

void Expand::onUnitEvade(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    Broodwar->sendText("A %s [%x] was last accessible at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Expand::onUnitShow(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    Broodwar->sendText("A %s [%x] has been spotted at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
  Broodwar->sendText("oi");
}

void Expand::onUnitHide(BWAPI::Unit* unit)
{
 // if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //Broodwar->sendText("A %s [%x] was last seen at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Expand::onUnitCreate(BWAPI::Unit* unit)
{
  if (Broodwar->getFrameCount()>1)
  {
    if (!Broodwar->isReplay())
      Broodwar->sendText("A %s [%x] has been created at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
	if(unit->getType() == Broodwar->self()->getRace().getCenter())
	{
		BalancearBases(Bases);
	}
    else
    {
      /*if we are in a replay, then we will print out the build order
      (just of the buildings, not the units).*/
      if (unit->getType().isBuilding() && unit->getPlayer()->isNeutral()==false)
      {
        int seconds=Broodwar->getFrameCount()/24;
        int minutes=seconds/60;
        seconds%=60;
        Broodwar->sendText("%.2d:%.2d: %s creates a %s",minutes,seconds,unit->getPlayer()->getName().c_str(),unit->getType().getName().c_str());
      }
    }
  }
}

void Expand::onUnitDestroy(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    Broodwar->sendText("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Expand::onUnitMorph(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay())
    Broodwar->sendText("A %s [%x] has been morphed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
  else
  {
    /*if we are in a replay, then we will print out the build order
    (just of the buildings, not the units).*/
    if (unit->getType().isBuilding() && unit->getPlayer()->isNeutral()==false)
    {
      int seconds=Broodwar->getFrameCount()/24;
      int minutes=seconds/60;
      seconds%=60;
      Broodwar->sendText("%.2d:%.2d: %s morphs a %s",minutes,seconds,unit->getPlayer()->getName().c_str(),unit->getType().getName().c_str());
    }
  }
}

void Expand::onUnitRenegade(BWAPI::Unit* unit)
{
  if (!Broodwar->isReplay())
    Broodwar->sendText("A %s [%x] is now owned by %s",unit->getType().getName().c_str(),unit,unit->getPlayer()->getName().c_str());
}

void Expand::onSaveGame(std::string gameName)
{
  Broodwar->printf("The game was saved to \"%s\".", gameName.c_str());
}

DWORD WINAPI BWTA_AnalyzeThread()
{
  BWTA::analyze();

  //self start location only available if the map has base locations
  if (BWTA::getStartLocation(BWAPI::Broodwar->self())!=NULL)
  {
    baseHome       = BWTA::getStartLocation(BWAPI::Broodwar->self())->getRegion();
  }
  //enemy start location only available if Complete Map Information is enabled.
  if (BWTA::getStartLocation(BWAPI::Broodwar->enemy())!=NULL)
  {
    enemyBase = BWTA::getStartLocation(BWAPI::Broodwar->enemy())->getRegion();
  }
  hasAnalysed   = true;
  analysisJustFinished = true;
  return 0;
}

void Expand::drawStats()
{
  std::set<Unit*> myUnits = Broodwar->self()->getUnits();
  Broodwar->drawTextScreen(5,0,"I have %d units:",myUnits.size());
  std::map<UnitType, int> unitTypeCounts;
  for(std::set<Unit*>::iterator i=myUnits.begin();i!=myUnits.end();i++)
  {
    if (unitTypeCounts.find((*i)->getType())==unitTypeCounts.end())
    {
      unitTypeCounts.insert(std::make_pair((*i)->getType(),0));
    }
    unitTypeCounts.find((*i)->getType())->second++;
  }
  int line=1;
  for(std::map<UnitType,int>::iterator i=unitTypeCounts.begin();i!=unitTypeCounts.end();i++)
  {
    Broodwar->drawTextScreen(5,16*line,"- %d %ss",(*i).second, (*i).first.getName().c_str());
    line++;
  }
}

void Expand::drawBullets()
{
  std::set<Bullet*> bullets = Broodwar->getBullets();
  for(std::set<Bullet*>::iterator i=bullets.begin();i!=bullets.end();i++)
  {
    Position p=(*i)->getPosition();
    double velocityX = (*i)->getVelocityX();
    double velocityY = (*i)->getVelocityY();
    if ((*i)->getPlayer()==Broodwar->self())
    {
      Broodwar->drawLineMap(p.x(),p.y(),p.x()+(int)velocityX,p.y()+(int)velocityY,Colors::Green);
      Broodwar->drawTextMap(p.x(),p.y(),"\x07%s",(*i)->getType().getName().c_str());
    }
    else
    {
      Broodwar->drawLineMap(p.x(),p.y(),p.x()+(int)velocityX,p.y()+(int)velocityY,Colors::Red);
      Broodwar->drawTextMap(p.x(),p.y(),"\x06%s",(*i)->getType().getName().c_str());
    }
  }
}

void Expand::drawVisibilityData()
{
  for(int x=0;x<Broodwar->mapWidth();x++)
  {
    for(int y=0;y<Broodwar->mapHeight();y++)
    {
      if (Broodwar->isExplored(x,y))
      {
        if (Broodwar->isVisible(x,y))
          Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Green);
        else
          Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Blue);
      }
      else
        Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Red);
    }
  }
}

void Expand::drawTerrainData()
{
  //we will iterate through all the base locations, and draw their outlines.
  for(std::set<BWTA::BaseLocation*>::const_iterator i=BWTA::getBaseLocations().begin();i!=BWTA::getBaseLocations().end();i++)
  {
    TilePosition p=(*i)->getTilePosition();
    Position c=(*i)->getPosition();

    //draw outline of center location
    Broodwar->drawBox(CoordinateType::Map,p.x()*32,p.y()*32,p.x()*32+4*32,p.y()*32+3*32,Colors::Blue,false);

    //draw a circle at each mineral patch
    for(std::set<BWAPI::Unit*>::const_iterator j=(*i)->getStaticMinerals().begin();j!=(*i)->getStaticMinerals().end();j++)
    {
      Position q=(*j)->getInitialPosition();
      Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Cyan,false);
    }

    //draw the outlines of vespene geysers
    for(std::set<BWAPI::Unit*>::const_iterator j=(*i)->getGeysers().begin();j!=(*i)->getGeysers().end();j++)
    {
      TilePosition q=(*j)->getInitialTilePosition();
      Broodwar->drawBox(CoordinateType::Map,q.x()*32,q.y()*32,q.x()*32+4*32,q.y()*32+2*32,Colors::Orange,false);
    }

    //if this is an island expansion, draw a yellow circle around the base location
    if ((*i)->isIsland())
      Broodwar->drawCircle(CoordinateType::Map,c.x(),c.y(),80,Colors::Yellow,false);
  }

  //we will iterate through all the regions and draw the polygon outline of it in green.
  for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
  {
    BWTA::Polygon p=(*r)->getPolygon();
    for(int j=0;j<(int)p.size();j++)
    {
      Position point1=p[j];
      Position point2=p[(j+1) % p.size()];
      Broodwar->drawLine(CoordinateType::Map,point1.x(),point1.y(),point2.x(),point2.y(),Colors::Green);
    }
  }

  //we will visualize the chokepoints with red lines
  for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
  {
    for(std::set<BWTA::Chokepoint*>::const_iterator c=(*r)->getChokepoints().begin();c!=(*r)->getChokepoints().end();c++)
    {
      Position point1=(*c)->getSides().first;
      Position point2=(*c)->getSides().second;
      Broodwar->drawLine(CoordinateType::Map,point1.x(),point1.y(),point2.x(),point2.y(),Colors::Red);
    }
  }
}

void Expand::showPlayers()
{
  std::set<Player*> players=Broodwar->getPlayers();
  for(std::set<Player*>::iterator i=players.begin();i!=players.end();i++)
  {
    Broodwar->printf("Player [%d]: %s is in force: %s",(*i)->getID(),(*i)->getName().c_str(), (*i)->getForce()->getName().c_str());
  }
}

void Expand::showForces()
{
  std::set<Force*> forces=Broodwar->getForces();
  for(std::set<Force*>::iterator i=forces.begin();i!=forces.end();i++)
  {
    std::set<Player*> players=(*i)->getPlayers();
    Broodwar->printf("Force %s has the following players:",(*i)->getName().c_str());
    for(std::set<Player*>::iterator j=players.begin();j!=players.end();j++)
    {
      Broodwar->printf("  - Player [%d]: %s",(*j)->getID(),(*j)->getName().c_str());
    }
  }
}

void Expand::onUnitComplete(BWAPI::Unit *unit)
{
  if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    Broodwar->sendText("A %s [%x] has been completed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}
