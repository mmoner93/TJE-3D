#include "Scene.h"
#include "Stage.h"
#include "StagePlay.h"
void Scene::addObject(EntityGameObject* temp) {
	mapaObjects.push_back(temp);
}
void Scene::addEnemy(EntityEnemy* temp) {
	Enemys.push_back(temp);
}
void Scene :: updateScene(float seconds_elapsed) {

	for (int i = 0; i < Enemys.size(); i++) {


		Enemys[i]->update(seconds_elapsed,mapaObjects);

	}

}
void Scene::pintarScene() {
	glDisable(GL_DEPTH_TEST);
	 cielo->renderTilling();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	suelo->render(lightScene->light);
	myPlayer->render(lightScene->light);
	lightScene->render( lightScene->light);
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


	for (int i = 0; i < Enemys.size(); i++) {

		if (Enemys[i]->aLive) {
			Enemys[i]->render(lightScene->light);
		}
		

	}

	Mesh points_mesh;
	points_mesh.vertices = pointsSP;
	if (pointsSP.size()) {
		((StagePlay*)Stage::getStage("Play"))->renderPoints(Matrix44(), &points_mesh, 0);
	}


}

void Scene::cargarWallsInIA() {

	FILE* fp = fopen("mapaIAConfigA.txt", "rb");
	if (fp == NULL) {

	for (int x = 0; x < mapGame->width*9; ++x){
		for (int y = 0; y < mapGame->height*9; ++y)
		{

			Vector3 target_pos=Vector3((float)y,0, (float)x);
			//calculamos el centro de la esfera de colisión del player elevandola hasta la cintura
			Vector3 character_center = target_pos + Vector3(0, 0.65, 0);
			bool has_collision = false;

			for (int i = 0; i < mapaObjects.size(); i++)
			{

				EntityGameObject* en = mapaObjects[i];

				Mesh* mesh = en->mesh;

				//para cada objecto de la escena...
				Vector3 coll;
				Vector3 collnorm;


				//comprobamos si colisiona el objeto con la esfera (radio 3)
				if (mesh->testSphereCollision(*(en->model), character_center, 0.25, coll, collnorm) == false) {
					continue; //si no colisiona, pasamos al siguiente objeto
				}
				/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
					continue;*/
				has_collision = true;
				generatorIA->addCollision({ x, y });
				//std::cout << "He colisionao" << std::endl;
				//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
				//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
				//target_pos.y = 0;
				break;
			}
		}
	}



	FILE* fp = fopen("mapaIAConfigA.txt", "wb");
	fwrite(&generatorIA, sizeof(AStar::Generator), 1, fp);
	fclose(fp);


	}
	else {
		fread(&generatorIA, sizeof(AStar::Generator), 1, fp);

		fclose(fp);
	}


}

void Scene::cargarWallsInIA2() {

	FILE* fp = fopen("mapaIAConfig.bin", "rb");
	if (fp == NULL) {
	
		for (int x = 0; x < mapGame->width * 9; ++x) {
			for (int y = 0; y < mapGame->height * 9; ++y)
			{

				Vector3 target_pos = Vector3((float)y, 0, (float)x);
				//calculamos el centro de la esfera de colisión del player elevandola hasta la cintura
				Vector3 character_center = target_pos + Vector3(0, 0.65, 0);
				bool has_collision = false;

				for (int i = 0; i < mapaObjects.size(); i++)
				{

					EntityGameObject* en = mapaObjects[i];

					Mesh* mesh = en->mesh;

					//para cada objecto de la escena...
					Vector3 coll;
					Vector3 collnorm;


					//comprobamos si colisiona el objeto con la esfera (radio 3)
					if (mesh->testSphereCollision(*(en->model), character_center, 0.1, coll, collnorm) == false) {
						continue; //si no colisiona, pasamos al siguiente objeto
					}
					/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
						continue;*/
					has_collision = true;
					mapPARAIA[x + y * mapGame->width * 9] = 0;
					//std::cout << "He colisionao" << std::endl;
					//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
					//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
					//target_pos.y = 0;
					break;
				}
				if (!has_collision) {
					mapPARAIA[x + y * mapGame->width * 9] = 1;
				}

			}
		}



		FILE* fp = fopen("mapaIAConfig.bin", "wb");
		fwrite(&mapPARAIA, sizeof(mapPARAIA), 1, fp);
		fclose(fp);


	}
	else {
		fread(&mapPARAIA, sizeof(mapPARAIA), 1, fp);

		fclose(fp);
	}
		

	
	


	


}



void  Scene::LoadMap(std::vector<Entity*> EntityVector) {
	for (int x = 0; x < mapGame->width; ++x){
		for (int y = 0; y < mapGame->height; ++y)
		{
			//get cell info
			sCell& cell = mapGame->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;

			if (cell.type > 0 && cell.type <= NUM_ENTITIES) {
				EntityMesh* tempmesh = (EntityMesh*)EntityVector[cell.type];
				EntityGameObject* temp = new EntityGameObject(tempmesh->textura, tempmesh->shader, tempmesh->mesh, tempmesh->material, tempmesh->nameShader, 3.0f);



				if (cell.type == HANGAR_1) {
					temp->model->translate((float)((x+1) * 3.0), 0.05f, (float)((y + 1) * 3.0));
				}
				else {
					temp->model->translate((float)((x + 1) * 3.0), 0.0f, (float)((y + 1) * 3.0));
				}
				

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

	cargarWallsInIA();

}



void Scene::loadEnemys(std::map<std::string, Entity*> enemysMap) {

	//enemysMap.size()

	for (int i = 0; i < 1; i++) {
		EntityMesh* en;

		switch (i) {
		case 0:
			en = (EntityMesh*)enemysMap["Arachnoid"];

			break;
		case 1:

			en = (EntityMesh*)enemysMap["ReconBot"];
			break;
		case 2:

			en = (EntityMesh*)enemysMap["Companion"];
			break;
		case 3:

			en = (EntityMesh*)enemysMap["MobileStorageBot"];
			break;
		case 4:

			en = (EntityMesh*)enemysMap["MechaTrooper"];
			break;
		case 5:

			en = (EntityMesh*)enemysMap["FieldFighter"];
			break;
		case 6:

			en = (EntityMesh*)enemysMap["QuadrupedTank"];
			break;
		case 7:

			en = (EntityMesh*)enemysMap["MechaGolem"];
			break;
		case 8:

			en = (EntityMesh*)enemysMap["Mecha01"];
			break;
		}

		
		EntityEnemy* temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game",Vector3(0, 0, i * 10.0f), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);

		temp->model->translate((i + 1.0) * 10.0f, 0, (i+1.0) * 10.0f);

		addEnemy(temp);
	}


}
