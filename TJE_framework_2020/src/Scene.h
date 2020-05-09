#ifndef SCENE_H
#define SCENE_H

#include "EntityMesh.h"
#include "EntityLight.h"
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

	void addObject(EntityGameObject* temp) {
		mapaObjects.push_back(temp);
	}


	void pintarScene() {
	
		suelo->renderTilling();


		for (int i = 0; i < mapaObjects.size(); i++) {
		
			mapaObjects[i]->renderConPhong(0, 0, lightScene->light);

		}


	}


};


#endif 