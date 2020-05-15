#include "Scene.h"


void Scene::addObject(EntityGameObject* temp) {
	mapaObjects.push_back(temp);
}


void Scene::pintarScene() {
	glDisable(GL_DEPTH_TEST);
	 cielo->renderTilling();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	suelo->renderEspecial();

	for (int i = 0; i < mapaObjects.size(); i++) {

		if (mapaObjects[i]->nameShader == "basic") {
			mapaObjects[i]->renderTilling();
		}
		else if (mapaObjects[i]->nameShader == "phong") {
			mapaObjects[i]->renderConPhong(0, 0, lightScene->light);
		}
		else if (mapaObjects[i]->nameShader == "game") {
			mapaObjects[i]->renderEspecial();
		}
		

	}


}