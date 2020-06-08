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
	int contadorIdDisparo = 0;
	int contadorIdDisparoPegamento = 0;
	std::vector<EntityImpactoDisparo*> EntitysImpactoDisparo;
	std::vector<EntityImpactoDisparo*> EntitysImpactoPegamento;
	EntityTowerArreglo* towerTemp;
	std::vector<EntityTowerArreglo*> TowersList;


	float time_enemy_Tower = 2.0f;
	float time_enemy_Tower_Max=10.0f;



	Scene(EntityLight* l, EntityGameObject* s, EntityGameObject* ci, EntityPlayer* pl) {
		lightScene = l;
		suelo = s;
		cielo = ci;
		myPlayer = pl;

		mapGame = new GameMap(256, 256);
		mapGame->loadMapWithMap("data/myMaps/escenaEntregar.map");
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
	void pintarDisparosPegamento();
	void emplacePegamento(Vector3 pos);
	int idMasBajo();
	int idMasBajoPegamento();
	void pintarTowerArreglo();
	void spawnTower();
	int towerMasCerca(EntityEnemy* enem);
	void tocaRomper(float seconds_elapsed);
	int someEnemyAlive();
	int enemyAliveRandom();
	bool someTowerActive();
	int TowerAliveRandom();
	int someTowerAlive();
	int EnemyMasCerca(EntityTowerArreglo* torre);
};


#endif 