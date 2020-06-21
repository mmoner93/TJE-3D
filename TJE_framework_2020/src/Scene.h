#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
#include "EntityGameObject.h"
#include "EntityPlayer.h"
#include "GameMap.h"
#include "enumStructs.h"
#include "EntityEnemy.h"
#include "AStar.hpp"
#include "EntityImpactoDisparo.h"
#include "EntityTorreArreglo.h"
#include "EntityDisparo.h"
#include "EntityCajasLoot.h"
#include "EntityGranade.h"
class Scene
{
public:
	EntityPlayer* myPlayer;
	EntityLight* lightScene;
	EntityGameObject* suelo;
	EntityGameObject* cielo;
	std::vector<EntityGameObject*> mapaObjects;
	std::vector<EntityEnemy*> Enemys; 
	GameMap* mapGame = NULL;
	std::vector<Vector3> pointsSP;
	std::vector<Vector3> disparosPoints;
	std::vector<Vector3> normPointsSP;
	AStar::Generator* generatorIA;
	// Set 2d map size.
	uint8* mapPARAIA;
	Mesh* disparoMesh;
	Texture* disparoTexture;
	Mesh*  disparoMeshPegamento;
	Texture* disparoPegamentoTexture;

	Mesh* cajaLootMesh;
	Texture* cajaLootTexture;

	Mesh* granadeMesh;
	Texture* granadetTexture;


	int contadorIdDisparo = 0;
	int contadorIdDisparoPegamento = 0;
	int contadorIdDisparoPegamentoMovimiento = 0;
	int contadorIdDisparoMovimiento = 0;
	std::vector<EntityImpactoDisparo*> EntitysImpactoDisparo;
	std::vector<EntityImpactoDisparo*> EntitysImpactoPegamento;
	EntityTowerArreglo* towerTemp;
	std::vector<EntityTowerArreglo*> TowersList;



	float time_enemy_Tower = 2.0f;
	
	//std::vector<EntityImpactoDisparo*> EntitysDisparo;
	std::vector<EntityDisparo*> disparosMove;
	std::vector<EntityDisparo*> disparosPegamentoMove;
	EntityDisparo* disparo;

	std::vector<EntityCajaLoot*> cajasLoot;
	EntityGranade* granadesMove;


	/*Para controlar lvl*/
	int numLvl;
	int numEnemysNode;
	int numEnemysByNode;
	int numTowers;
	Vector3 initPosPlayer = Vector3(10, 0, 10);
	float time_enemy_Tower_Max = 10.0f;
	int numCajasLoot;

	Scene(int num,EntityLight* l, EntityGameObject* s, EntityGameObject* ci, EntityPlayer* pl) {
		numLvl = num;
		lightScene = l;
		suelo = s;
		cielo = ci;
		myPlayer = pl;

		mapGame = new GameMap(256, 256);

		switch (numLvl) {
		case 0:
			numEnemysNode = 1;
			numEnemysByNode = 1;
			numTowers = 1;
			numCajasLoot = 20;
			initPosPlayer = Vector3(10,0,10);
			mapGame->loadMapWithMap("data/myMaps/escenaEntregar.map");
			time_enemy_Tower_Max = 10.0f;
			break;
		case 1:
			numEnemysNode = 20;
			numEnemysByNode = 0;
			numTowers = 2;
			numCajasLoot = 20;
			initPosPlayer = Vector3(10, 0, 10);
			mapGame->loadMapWithMap("data/myMaps/mymap3.map");
			time_enemy_Tower_Max = 10.0f;
			break;
		case 2:
			numEnemysNode = 3;
			numEnemysByNode = 6;
			numTowers = 4;
			numCajasLoot = 20;
			mapGame->loadMapWithMap("data/myMaps/escenaEntregar.map");
			time_enemy_Tower_Max = 10.0f;

			break;
		}

		
		generatorIA = new AStar::Generator();
		//pongo *9 por que es como lo he escalado de momento .
		generatorIA->setWorldSize({mapGame->width * 9, mapGame->height * 9 });
		
		// You can use a few heuristics : manhattan, euclidean or octagonal.
		generatorIA->setHeuristic(AStar::Heuristic::euclidean);
		generatorIA->setDiagonalMovement(true);
		mapPARAIA = new uint8[mapGame->width * 9 * mapGame->height * 9];
		disparoMesh = Mesh::Get("data/impactos/impacto.OBJ");
		disparoMeshPegamento = Mesh::Get("data/impactos/impactoPegamento.OBJ");
		disparoTexture = Texture::Get("data/impactos/impacto.png");
		disparoPegamentoTexture = Texture::Get("data/impactos/impactogris.png");
		cajaLootMesh= Mesh::Get("data/itemsUse/chest2.OBJ");
		cajaLootTexture = Texture::Get("data/itemsUse/chest2.png");

		granadeMesh = Mesh::Get("data/itemsUse/granade.OBJ");
		 
		granadetTexture= Texture::Get("data/itemsUse/granade.png");
		

		granadesMove = new EntityGranade(0,granadetTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), granadeMesh, NULL, "game", Vector3(0, 0, 0));

		//disparo = new EntityDisparo(disparoTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"),disparoMesh,NULL,"game",Vector3(0,0,0),T_PEGAMENTO);
		
		//towerTemp->model->translateGlobal(15, 0, 15);
	}

	void addObject(EntityGameObject* temp);
	void addEnemy(EntityEnemy* temp);
	void LoadMap(std::vector<Entity*> EntityVector);
	void loadEnemys(std::map<std::string, Entity*> enemysMap);

	void pintarScene();
	void updateScene(float seconds_elapsed);
	void cargarWallsInIA();
	void cargarWallsInIA2();

	void initListDisparos();
	bool loadWalls();

	void writeWalls();

	void pintarDisparos();
	void emplaceDisparo(Vector3 pos);
	void emplacePegamento(Vector3 pos);
	int idMasBajo();
	int idMasBajoPegamento();
	int idMasBajoPegamentoMovimiento();
	int idMasBajoMovimiento();
	void activateGranade(Vector3 origin, Vector3 dir);
	void activateDisparo(Vector3 origin,Vector3 dir);
	void activateDisparoPegamento(Vector3 origin, Vector3 dir);

	void pintarTowerArreglo();
	void pintarCajasLoot();
	void pintarGranades();
	void spawnTower();
	void spawnCajasLoot();
	int towerMasCerca(EntityEnemy* enem);
	void tocaRomper(float seconds_elapsed);
	int someEnemyAlive();
	int enemyAliveRandom();
	bool someTowerActive();
	int TowerAliveRandom();
	int someTowerAlive();
	int EnemyMasCerca(EntityTowerArreglo* torre);

	void turnAllMiniosOff(int id_padre);

	bool checkEndLvl();
	void restartLvl(std::map<std::string, Entity*>);

};


#endif 