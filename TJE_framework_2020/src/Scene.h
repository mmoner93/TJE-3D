#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
class Scene
{
public:

	EntityLight* lightScene;
	std::vector<EntityGameObject*> mapaObjects;

	Scene(EntityLight* l) {
		lightScene = l;
	}

	void addObject(EntityGameObject* temp) {
		mapaObjects.push_back(temp);
	}


	void pintarScene() {
	
	
		for (int i = 0; i < mapaObjects.size(); i++) {
		
			mapaObjects[i]->renderConPhong(0, 0, lightScene->light);

		}


	}


};


#endif 