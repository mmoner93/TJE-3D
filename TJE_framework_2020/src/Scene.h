#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
#include "EntityGameObject.h"
#include "EntityPlayer.h"
#include "GameMap.h"
#include "enumStructs.h"
class Scene
{
public:
	EntityPlayer* myPlayer;
	EntityLight* lightScene;
	EntityGameObject* suelo;
	EntityGameObject* cielo;
	std::vector<EntityGameObject*> mapaObjects;
	std::vector<EntityGameObject*> Enemys; //esto seguramente cambiara a entityEnemy cuando tengan comportamiento y tal.
	GameMap* mapGame = NULL;
	Scene(EntityLight* l, EntityGameObject* s, EntityGameObject* ci, EntityPlayer* pl) {
		lightScene = l;
		suelo = s;
		cielo = ci;
		myPlayer = pl;

		mapGame = new GameMap(256, 256);
		mapGame->loadMapWithMap("data/myMaps/escenaEntregar.map");
	}

	void addObject(EntityGameObject* temp);
	
	void LoadMap(std::vector<Entity*> EntityVector);
	void loadEnemys(std::map<std::string, Entity*> enemysMap);

	void pintarScene();
	
};


#endif 