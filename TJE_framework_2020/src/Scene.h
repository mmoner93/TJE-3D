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
	std::vector<EntityGameObject*> mapaObjects;

	Scene(EntityLight* l, EntityGameObject* s) {
		lightScene = l;
		suelo = s;
	}

	void addObject(EntityGameObject* temp);


	void pintarScene();


};


#endif 