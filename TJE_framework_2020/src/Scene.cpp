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
	suelo->render(lightScene->light);
	myPlayer->render(lightScene->light);
	lightScene->gameMesh->render( lightScene->light);
	for (int i = 0; i < mapaObjects.size(); i++) {

	/*	if (mapaObjects[i]->nameShader == "basic") {
			mapaObjects[i]->renderTilling();
		}
		else if (mapaObjects[i]->nameShader == "phong") {
			mapaObjects[i]->renderConPhong( lightScene->light);
		}
		else if (mapaObjects[i]->nameShader == "game") {
			mapaObjects[i]->renderEspecial(lightScene->light);
		}*/
		mapaObjects[i]->render(lightScene->light);

	}


}



void  Scene::LoadMap(std::vector<Entity*> EntityVector) {
	for (int x = 0; x < mapGame->width; ++x)
		for (int y = 0; y < mapGame->height; ++y)
		{
			//get cell info
			sCell& cell = mapGame->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;

			if (cell.type > 0 && cell.type <= NUM_ENTITIES) {
				EntityMesh* tempmesh = (EntityMesh*)EntityVector[cell.type];
				EntityGameObject* temp = new EntityGameObject(tempmesh->textura, tempmesh->shader, tempmesh->mesh, tempmesh->material, tempmesh->nameShader, 3.0f);

				temp->model->translate(x * 3, 0.0f, y * 3);

				//podria hacer una función para indicar estas cosas. Roto las figuras para que cuadren en escenario (esquinas , paredes)
				if (cell.type == CORNER_IZQUIERDA_SUP) {
					temp->model->rotate(PI, Vector3(0, 1, 0));
				}

				if (cell.type == CORNER_IZQUIERDA_INF) {
					temp->model->rotate(PI / 2, Vector3(0, 1, 0));
				}

				if (cell.type == CORNER_DERECHA_SUP) {
					temp->model->rotate(-PI / 2, Vector3(0, 1, 0));
				}


				if (cell.type == WALL_SUP) {
					temp->model->rotate(PI / 2, Vector3(0, 1, 0));
				}

				if (cell.type == WALL_DER) {
					temp->model->rotate(PI, Vector3(0, 1, 0));
				}

				if (cell.type == WALL_INF) {
					temp->model->rotate(-PI / 2, Vector3(0, 1, 0));
				}


				addObject(temp);


			}



		}

}