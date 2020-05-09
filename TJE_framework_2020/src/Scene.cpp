#include "Scene.h"


void Scene::addObject(EntityGameObject* temp) {
	mapaObjects.push_back(temp);
}


void Scene::pintarScene() {

	suelo->renderTilling();


	for (int i = 0; i < mapaObjects.size(); i++) {

		mapaObjects[i]->renderConPhong(0, 0, lightScene->light);

	}


}