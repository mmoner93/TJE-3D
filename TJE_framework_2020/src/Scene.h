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

	Scene(EntityLight* l, EntityGameObject* s, EntityGameObject* ci) {
		lightScene = l;
		suelo = s;
		cielo = ci;
	}

	void addObject(EntityGameObject* temp);


	void pintarScene();


};


#endif 