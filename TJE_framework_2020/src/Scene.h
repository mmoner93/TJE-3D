#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
class Scene
{
public:

	EntityLight* lightScene;
	std::vector<Entity*> mapaObjects;

	Scene() {

	}

	void addObject(Entity* temp) {
		mapaObjects.push_back(temp);
	}


	void pintarScene() {
	
	
		for (int i = 0; i < mapaObjects.size(); i++) {
		

		
		}


	}


};


#endif 