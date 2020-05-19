#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
#include "EntityGameObject.h"
class Scene
{
public:

	EntityLight* lightScene;
	EntityGameObject* suelo;
	EntityGameObject* cielo;
	std::vector<EntityGameObject*> mapaObjects;
	std::vector<EntityGameObject*> Enemys; //esto seguramente cambiara a entityEnemy cuando tengan comportamiento y tal.

	Scene(EntityLight* l, EntityGameObject* s, EntityGameObject* ci) {
		lightScene = l;
		suelo = s;
		cielo = ci;
	}

	void addObject(EntityGameObject* temp);

	void addEnemy(EntityGameObject* temp);
	void pintarScene();


};


#endif 