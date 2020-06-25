#include "Scene.h"
#include "Stage.h"
#include "StagePlay.h"
#include <time.h>
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

	for (int i = 0; i < TowersList.size(); i++) {


		TowersList[i]->update(seconds_elapsed);

	}
	tocaRomper(seconds_elapsed);

	for (int i = 0; i < disparosMove.size(); i++) {
		if (disparosMove[i]->in_use == true) {
			disparosMove[i]->update(seconds_elapsed, mapaObjects);
		}
	}

	for (int i = 0; i < disparosPegamentoMove.size(); i++) {
		if (disparosPegamentoMove[i]->in_use == true) {
			disparosPegamentoMove[i]->update(seconds_elapsed, mapaObjects);
		}
	}

	for (int i = 0; i < cajasLoot.size(); i++) {
		if (cajasLoot[i]->in_use == true) {
			cajasLoot[i]->update(seconds_elapsed, mapaObjects);
		}
	}

	for (int i = 0; i < granadesMove.size(); i++) {
		if (granadesMove[i]->in_use == true) {
			granadesMove[i]->update(seconds_elapsed, mapaObjects);
		}
	}


	time_In_Game += seconds_elapsed;

	if (time_walkie > 0.0f) {
		time_walkie -= seconds_elapsed;
	}


	updateDecoracion(seconds_elapsed);


}
void Scene::pintarScene() {
	glDisable(GL_DEPTH_TEST);
	cielo->renderTilling();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	suelo->render(lightScene->light,fog_color);

	lightScene->render( lightScene->light,fog_color);
	for (int i = 0; i < mapaObjects.size(); i++) {

		mapaObjects[i]->render(lightScene->light,fog_color);

	}


	for (int i = 0; i < Enemys.size(); i++) {

		Enemys[i]->render(lightScene->light, fog_color);

	}


	pintarDisparos();
	pintarTowerArreglo();
	pintarCajasLoot();
	pintarGranades();
	PintarDecoracion();
	myPlayer->render(lightScene->light,fog_color);
	if (vozOn && numLvl == 0) {
		time_walkie = 124.0f;
		tutorialChannel =Game::instance->samplesAudio["TutorialJefe"]->PlaySoundAmbient();

		vozOn = false;
	}

}

void Scene::spawnTower() {
	Texture* temp1 = Texture::Get("data/itemsUse/torre_finalgreen.png");
	Texture* temp2 = Texture::Get("data/itemsUse/torre_finalorange.png");
	Texture* temp3 = Texture::Get("data/itemsUse/torre_final.png");
	Mesh* tempa = Mesh::Get("data/itemsUse/torre_final.obj");

	srand(time(NULL));



	if (numLvl != 0) {

		for (int i = 0; i < numTowers; ) {
			int tempWidth = rand() % mapGame->width * 9;
			int tempHeight = rand() % mapGame->height * 9;

			if (!generatorIA->detectCollision({ tempWidth, tempHeight }) && tempWidth >= 10 && tempHeight >= 10 && tempHeight <= ((mapGame->width * 9) - 10) && tempWidth <= ((mapGame->width * 9) - 10)) {

				towerTemp = new EntityTowerArreglo(temp1, temp2, temp3, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), tempa, NULL, "Game", 1.0f);
				towerTemp->model->translateGlobal(float(tempHeight), 0, float(tempWidth));
				TowersList.push_back(towerTemp);
				i++;
			}

		}
	}
	else {
		towerTemp = new EntityTowerArreglo(temp1, temp2, temp3, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), tempa, NULL, "Game", 1.0f);
		towerTemp->model->translateGlobal(float(20), 0, float(100));
		TowersList.push_back(towerTemp);
	}






	/*for (int i = 0; i < mapGame->width * 9; i++) {

		for (int o = 0; o < mapGame->height * 9; o++) {

			generatorIA->detectCollision(i,o)
		}
	}*/



}


void Scene::spawnCajasLoot() {

	srand(time(NULL));

	EntityCajaLoot* temporal;

	for (int i = 0; i < numCajasLoot; ) {
		int tempWidth = rand() % mapGame->width * 9;
		int tempHeight = rand() % mapGame->height * 9;

		if (!generatorIA->detectCollision({ tempWidth, tempHeight }) && tempWidth >= 10 && tempHeight >= 10 && tempHeight <= ((mapGame->width * 9) - 10) && tempWidth <= ((mapGame->width * 9) - 10)) {

			temporal = new EntityCajaLoot(cajaLootTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), cajaLootMesh, NULL, "Game", Vector3(float(tempHeight), 0, float(tempWidth)));
			temporal->model->translateGlobal(float(tempHeight), 0, float(tempWidth));
			cajasLoot.push_back(temporal);
			i++;
		}

	}





}




void Scene::pintarDisparos() {


	disparosMoveM.clear();
	for (int i = 0; i < EntitysImpactoPegamento.size(); i++) {
		if (EntitysImpactoPegamento[i]->in_use == true) {
			//EntitysImpactoPegamento[i]->render(lightScene->light);
			disparosMoveM.push_back(*(EntitysImpactoPegamento[i]->model));
		}
	}
	for (int i = 0; i < disparosPegamentoMove.size(); i++) {
		if (disparosPegamentoMove[i]->in_use == true) {
			//disparosPegamentoMove[i]->render(lightScene->light);
			disparosMoveM.push_back(*(disparosPegamentoMove[i]->model));
		}
	}





	
	if (disparosMoveM.size() > 0) {
		Shader* shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
		shader->enable();
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);//camera->viewprojection_matrix);
		shader->setUniform("u_texture", disparoPegamentoTexture, 0);
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setFloat("u_tilling", 1.0);
		EntitysImpactoPegamento[0]->mesh->renderInstanced(GL_TRIANGLES, &(disparosMoveM[0]), (int)disparosMoveM.size());
		shader->disable();
	}




	disparosMoveM.clear();
	for (int i = 0; i < disparosMove.size(); i++) {

		if (disparosMove[i]->in_use == true) {
			//disparosMove[i]->render(lightScene->light);
			disparosMoveM.push_back(*(disparosMove[i]->model));
		}
	}

	for (int i = 0; i < EntitysImpactoDisparo.size(); i++) {
		if (EntitysImpactoDisparo[i]->in_use == true) {
			//EntitysImpactoDisparo[i]->render(lightScene->light);
			disparosMoveM.push_back(*(EntitysImpactoDisparo[i]->model));
		}
	}


	if (disparosMoveM.size() > 0) {
		Shader* shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
		shader->enable();
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);//camera->viewprojection_matrix);
		shader->setUniform("u_texture", disparoTexture, 0);
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setFloat("u_tilling", 1.0);
		disparosMove[0]->mesh->renderInstanced(GL_TRIANGLES, &(disparosMoveM[0]), (int)disparosMoveM.size());
		shader->disable();
	}




	//Mesh* dispa = Mesh::Get("data/kjdsnf");
	//dispa->renderInstanced(GL_TRIANGLES, &disparosMoveM[0], disparosMoveM.size());





}




int  Scene::idMasBajoPegamentoMovimiento() {
	int idmax = -1;//max id
	int idmin = MAXINT32;
	for (int i = 0; i < disparosPegamentoMove.size(); i++) {
		if (idmax < disparosPegamentoMove[i]->id) {
			idmax = disparosPegamentoMove[i]->id;
		}
		if (idmin > disparosPegamentoMove[i]->id) {
			idmin = disparosPegamentoMove[i]->id;
		}
	}
	for (int i = 0; i < disparosPegamentoMove.size(); i++) {
		if (disparosPegamentoMove[i]->id == idmin) {
			disparosPegamentoMove[i]->in_use = false;
			break;
		}
	}



	return idmax;

}

int  Scene::idMasBajoMovimiento() {
	int idmax = -1;//max id
	int idmin = MAXINT32;
	for (int i = 0; i < disparosMove.size(); i++) {
		if (idmax < disparosMove[i]->id) {
			idmax = disparosMove[i]->id;
		}
		if (idmin > disparosMove[i]->id) {
			idmin = disparosMove[i]->id;
		}
	}
	for (int i = 0; i < disparosMove.size(); i++) {
		if (disparosMove[i]->id == idmin) {
			disparosMove[i]->in_use = false;
			break;
		}
	}



	return idmax;

}

int  Scene::idMasBajoMovimientoGranade() {
	int idmax = -1;//max id
	int idmin = MAXINT32;
	for (int i = 0; i < disparosMove.size(); i++) {
		if (idmax < disparosMove[i]->id) {
			idmax = disparosMove[i]->id;
		}
		if (idmin > disparosMove[i]->id) {
			idmin = disparosMove[i]->id;
		}
	}
	for (int i = 0; i < disparosMove.size(); i++) {
		if (disparosMove[i]->id == idmin) {
			disparosMove[i]->in_use = false;
			break;
		}
	}



	return idmax;

}



int  Scene::idMasBajoPegamento() {
	int idmax = -1;//max id
	int idmin = MAXINT32;
	for (int i = 0; i < EntitysImpactoPegamento.size(); i++) {
		if (idmax < EntitysImpactoPegamento[i]->id) {
			idmax = EntitysImpactoPegamento[i]->id;
		}
		if (idmin > EntitysImpactoPegamento[i]->id) {
			idmin = EntitysImpactoPegamento[i]->id;
		}
	}
	for (int i = 0; i < EntitysImpactoPegamento.size(); i++) {
		if (EntitysImpactoPegamento[i]->id == idmin) {
			EntitysImpactoPegamento[i]->in_use = false;
			break;
		}
	}



	return idmax;

}


int  Scene::idMasBajo() {
	int idmax=-1;//max id
	int idmin = MAXINT32;
	for (int i = 0; i < EntitysImpactoDisparo.size(); i++) {
		if (idmax < EntitysImpactoDisparo[i]->id) {
			idmax = EntitysImpactoDisparo[i]->id;
		}
		if (idmin > EntitysImpactoDisparo[i]->id) {
			idmin = EntitysImpactoDisparo[i]->id;
		}
	}
	for (int i = 0; i < EntitysImpactoDisparo.size(); i++) {
		if (EntitysImpactoDisparo[i]->id== idmin) {
			EntitysImpactoDisparo[i]->in_use = false;
			break;
		}
	}



	return idmax;

}

void Scene::activateGranade(Vector3 origin, Vector3 dir) {



	bool control = true;
	for (int i = 0; i < granadesMove.size(); i++) {
		if (!granadesMove[i]->in_use) {
			granadesMove[i]->position = origin;
			granadesMove[i]->init_pos = origin;
			granadesMove[i]->model->setTranslation(origin.x, origin.y, origin.z);

			granadesMove[i]->in_use = true;
			granadesMove[i]->dir = dir;

			granadesMove[i]->time_passed = 0.0f;
			control = false;
			break;
		}
	}

	if (control) {
		int alto = idMasBajoMovimientoGranade();
		alto++;
		for (int i = 0; i < disparosMove.size(); i++) {
			if (!granadesMove[i]->in_use) {
				granadesMove[i]->position = origin;
				granadesMove[i]->init_pos = origin;
				granadesMove[i]->model->setTranslation(origin.x, origin.y, origin.z);
				granadesMove[i]->id = alto;
				granadesMove[i]->in_use = true;
				granadesMove[i]->dir = dir;

				granadesMove[i]->time_passed = 0.0f;
				control = false;
				break;
			}
		}
	}




}


int Scene::enemeysLeft() {
	int contador = 0;
	for (int i = 0; i < Enemys.size(); i++) {
		if ((!Enemys[i]->aLive && Enemys[i]->is_node)||(Enemys[i]->actualState==E_REPAIR && Enemys[i]->is_node)) {
			contador++;
		}
	}

	return contador;

}





int Scene::towersLeft() {
	int contador = 0;
	for (int i = 0; i < TowersList.size(); i++) {
		if (TowersList[i]->estado==GREEN) {
			contador++;
		}
	}

	return contador;
}


void Scene::activateDisparo(Vector3 origin, Vector3 dir) {
	bool control = true;
	for (int i = 0; i < disparosMove.size(); i++) {
		if (!disparosMove[i]->in_use) {
			disparosMove[i]->position = origin;
			disparosMove[i]->init_pos = origin;
			disparosMove[i]->model->setTranslation(origin.x, origin.y, origin.z);

			disparosMove[i]->in_use = true;
			disparosMove[i]->dir = dir;

			disparosMove[i]->time_passed = 0.0f;
			control = false;
			break;
		}
	}

	if (control) {
		int alto = idMasBajoMovimiento();
		alto++;
		for (int i = 0; i < disparosMove.size(); i++) {
			if (!disparosMove[i]->in_use) {
				disparosMove[i]->position = origin;
				disparosMove[i]->init_pos = origin;
				disparosMove[i]->model->setTranslation(origin.x, origin.y, origin.z);
				disparosMove[i]->id = alto;
				disparosMove[i]->in_use = true;
				disparosMove[i]->dir = dir;

				disparosMove[i]->time_passed = 0.0f;
				control = false;
				break;
			}
		}
	}

}

void Scene::activateDisparoPegamento(Vector3 origin, Vector3 dir) {
	bool control = true;
	for (int i = 0; i < disparosPegamentoMove.size(); i++) {
		if (!disparosPegamentoMove[i]->in_use) {
			disparosPegamentoMove[i]->position = origin;
			disparosPegamentoMove[i]->init_pos = origin;
			disparosPegamentoMove[i]->model->setTranslation(origin.x, origin.y, origin.z);

			disparosPegamentoMove[i]->in_use = true;
			disparosPegamentoMove[i]->dir = dir;

			disparosPegamentoMove[i]->time_passed = 0.0f;
			control = false;
			break;
		}
	}

	if (control) {
		int alto = idMasBajoPegamento();
		//if (alto == -1)
			//std::cout << "Ha salido -1";
		alto++;

		for (int i = 0; i < disparosPegamentoMove.size(); i++) {
			if (!disparosPegamentoMove[i]->in_use) {
				disparosPegamentoMove[i]->position = origin;
				disparosPegamentoMove[i]->init_pos = origin;
				disparosPegamentoMove[i]->model->setTranslation(origin.x, origin.y, origin.z);
				disparosPegamentoMove[i]->id = alto;
				disparosPegamentoMove[i]->in_use = true;
				disparosPegamentoMove[i]->dir = dir;

				disparosPegamentoMove[i]->time_passed = 0.0f;
				control = false;
				break;
			}
		}
	}
}


void Scene::emplaceDisparo(Vector3 pos) {
	bool control = true;
		for (int i = 0; i < EntitysImpactoDisparo.size(); i++) {
			if (!EntitysImpactoDisparo[i]->in_use) {
				EntitysImpactoDisparo[i]->in_use = true;
				EntitysImpactoDisparo[i]->model->translateGlobal(pos.x, pos.y, pos.z);
				control = false;
				break;
			}
		}

		if (control) {
			int alto = idMasBajo();
			alto++;
			for (int i = 0; i < EntitysImpactoDisparo.size(); i++) {
				if (!EntitysImpactoDisparo[i]->in_use) {
					EntitysImpactoDisparo[i]->in_use = true;
					EntitysImpactoDisparo[i]->id = alto;
					EntitysImpactoDisparo[i]->model->setTranslation(pos.x, pos.y, pos.z);
					control = false;
					break;
				}
			}
		}



}

void Scene::restartLvl(std::map<std::string, Entity*> enemysMapSP) {

	Enemys.clear();
	TowersList.clear();
	EntitysImpactoDisparo.clear();
	EntitysImpactoPegamento.clear();
	disparosMove.clear();
	disparosPegamentoMove.clear();
	cajasLoot.clear();
	loadEnemys(enemysMapSP);
	initListDisparos();
	spawnTower();
	spawnCajasLoot();
	time_In_Game = 0.0f;
	if (numLvl == 0) {
		vozOn = true;

	}
	myPlayer->health = myPlayer->mejoras.maxHealth;
	myPlayer->position=initPosPlayer;
}





void Scene::emplacePegamento(Vector3 pos) {
	bool control = true;
	for (int i = 0; i < EntitysImpactoPegamento.size(); i++) {
		if (!EntitysImpactoPegamento[i]->in_use) {
			EntitysImpactoPegamento[i]->in_use = true;
			EntitysImpactoPegamento[i]->model->translateGlobal(pos.x, pos.y, pos.z);
			control = false;
			break;
		}
	}

	if (control) {
		int alto = idMasBajoPegamento();
		alto++;
		for (int i = 0; i < EntitysImpactoPegamento.size(); i++) {
			if (!EntitysImpactoPegamento[i]->in_use) {
				EntitysImpactoPegamento[i]->in_use = true;
				EntitysImpactoPegamento[i]->id = alto;
				EntitysImpactoPegamento[i]->model->setTranslation(pos.x, pos.y, pos.z);
				control = false;
				break;
			}
		}
	}



}


void Scene::initListDecoracion() {

	for (int i = 0; i < MAX_DECORACION; i++) {

	}

	//decoracionList

}


void Scene::initListDisparos() {

	for (int i = 0; i < MAX_IMPACTO_DISPAROS; i++) {
		EntityImpactoDisparo* temp = new EntityImpactoDisparo(contadorIdDisparo, disparoTexture, ((StagePlay*)Stage::getStage("Play"))->shaderGameSP, disparoMesh, NULL, "Game", 1.0f);
		EntitysImpactoDisparo.push_back(temp);
		contadorIdDisparo++;
	}

	for (int i = 0; i < MAX_IMPACTO_DISPAROS_PEGAMENTO; i++) {
		EntityImpactoDisparo* temp = new EntityImpactoDisparo(contadorIdDisparoPegamento, disparoPegamentoTexture, ((StagePlay*)Stage::getStage("Play"))->shaderGameSP, disparoMeshPegamento, NULL, "Game", 1.0f);
		EntitysImpactoPegamento.push_back(temp);
		contadorIdDisparoPegamento++;
	}


	for (int i = 0; i < MAX_IMPACTO_DISPAROS_MOVIMIENTO; i++) {
		EntityDisparo* temp = new EntityDisparo(contadorIdDisparoMovimiento,disparoTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), disparoMesh, NULL, "game", Vector3(0, 0, 0), T_NORMAL);
		disparosMove.push_back(temp);
		contadorIdDisparoMovimiento++;
	}
	for (int i = 0; i < MAX_IMPACTO_DISPAROS_MOVIMIENTO; i++) {
		EntityDisparo* temp = new EntityDisparo(contadorIdDisparoPegamentoMovimiento, disparoPegamentoTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), disparoMeshPegamento, NULL, "game", Vector3(0, 0, 0), T_PEGAMENTO);
		disparosPegamentoMove.push_back(temp);
		contadorIdDisparoPegamentoMovimiento++;
	}


	for (int i = 0; i < MAX_GRANADE_IN_MOVE; i++) {
		EntityGranade* temp = new EntityGranade(0, granadetTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), granadeMesh, NULL, "game", Vector3(0, 0, 0));
		granadesMove.push_back(temp);
		contadorIdGranadeMovimiento++;
	}


}



void Scene::cargarWallsInIA() {


	if (!loadWalls()) {

	for (int x = 0; x < mapGame->width*9; ++x){
		for (int y = 0; y < mapGame->height*9; ++y)
		{

			Vector3 target_pos=Vector3((float)y,0, (float)x);
			//calculamos el centro de la esfera de colisi�n del player elevandola hasta la cintura
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


	writeWalls();



	}


}


std::vector<std::string> split_istringstream(std::string str) {
	std::vector<std::string> resultado;
	std::istringstream isstream(str);
	std::string palabra;

	while (isstream >> palabra) {
		resultado.push_back(palabra);
	}

	return resultado;
}


bool Scene::loadWalls() {

	std::string name = "mapaIA"+ std::to_string(numLvl) + "Config.txt";

	FILE* fp = fopen(name.c_str(), "rb");
	if (fp == NULL) {
		std::cout << "No se encuentra archivo mapaIAConfig.txt "  << std::endl;
		return false;
	}
	else {

		char mystring[10];

		int l = 0;
		while (!feof(fp)) {
			if (fgets(mystring, 10, fp) != NULL) {
				char* stringx;
				char* stringy;
				//char* token = strtok(mystring, ",");
				int o = 0;
				while (o<2)
				{
					if (o == 0) {
						stringx = strtok(mystring, ",");
					}else if(o == 1) {
						stringy = strtok(NULL, ",");
						stringy = strtok(stringy, "\n");
					}
					//cout << token << endl;

					o++;
				}

				generatorIA->addCollision({ atoi(stringx) , atoi(stringy) });

				//std::cout << "En walls x " << generatorIA->walls[l].x << " y " << generatorIA->walls[l].y << std::endl;
				l++;
			}

		}

		std::cout << "Size de lectura de walls : " << generatorIA->walls.size() << std::endl;
	}
	return true;

}





void Scene::writeWalls() {
	AStar::CoordinateList temp;
	std::string name = "mapaIA" + std::to_string(numLvl) + "Config.txt";

	FILE* fp = fopen(name.c_str(), "wb");
	for (int i = 0; i < generatorIA->walls.size();i++) {
		//temp.push_back(generatorIA->walls[i]);

		int o;

		std::string meter = std::to_string(generatorIA->walls[i].x )+","+ std::to_string(generatorIA->walls[i].y)+"\n";
		//std::string meter2 = ",";
		//std::string meter3 = meter+meter;
		fputs(meter.c_str(), fp);


	}

	fclose(fp);
	std::cout << "Archivo creado mapaIAConfig.txt " << std::endl;
	std::cout << "Size de escritura de walls : " << generatorIA->walls.size() << std::endl;
}


void Scene::cargarWallsInIA2() {

	FILE* fp = fopen("mapaIAConfig.bin", "rb");
	if (fp == NULL) {

		for (int x = 0; x < mapGame->width * 9; ++x) {
			for (int y = 0; y < mapGame->height * 9; ++y)
			{

				Vector3 target_pos = Vector3((float)y, 0, (float)x);
				//calculamos el centro de la esfera de colisi�n del player elevandola hasta la cintura
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

int Scene::EnemyMasCerca(EntityTowerArreglo* torre) {

	float distanceMin = 99999999999.f;
	int indexMin = -1;
	for (int i = 0; i < Enemys.size(); i++) {

		if (Enemys[i]->aLive && Enemys[i]->actualState!=E_REPAIR && Enemys[i]->actualState != STUNNED) {
			float distanceTemp = Enemys[i]->model->getTranslation().distance(torre->model->getTranslation());
			if (distanceTemp < distanceMin) {
				distanceMin = distanceTemp;
				indexMin = i;
			}
		}

	}

	if (distanceMin > 100) {
		indexMin = -1;
	}

	return indexMin;

}

int Scene::towerMasCerca(EntityEnemy* enem) {

	float distanceMin = 99999999999.f;
	int indexMin = -1;
	for (int i = 0; i < TowersList.size(); i++) {

		if (TowersList[i]->estado == GREEN || TowersList[i]->estado == ORANGE) {
			float distanceTemp = TowersList[i]->model->getTranslation().distance(enem->model->getTranslation());
			if (distanceTemp < distanceMin) {
				distanceMin = distanceTemp;
				indexMin = i;
			}
		}

	}

	return indexMin;

}
bool Scene::someTowerActive() {
	for (int i = 0; i < TowersList.size(); i++) {

		if (TowersList[i]->estado == GREEN || TowersList[i]->estado == ORANGE) {
			return true;

		}

	}

	return false;

}

void Scene::turnAllMiniosOff(int id_padre) {

	for (int i = 0; i < Enemys.size(); i++) {
		if (Enemys[i]->aLive && Enemys[i]->id_padre==id_padre) {
			Enemys[i]->actualState = E_REPAIR;
		}
	}



}



int Scene::someEnemyAlive() {
	for (int i = 0; i < Enemys.size(); i++) {
		if (Enemys[i]->aLive && Enemys[i]->actualState!=E_REPAIR && Enemys[i]->actualState != STUNNED) {
			return i;
		}
	}
	return -1;
}
int Scene::someTowerAlive() {
	for (int i = 0; i < TowersList.size(); i++) {
		if (TowersList[i]->estado == GREEN || TowersList[i]->estado == ORANGE) {
			return i;
		}
	}
	return -1;
}




int Scene::enemyAliveRandom() {
	bool controlT = true;
	int numberControl = 0;
	while (numberControl<10) {
		int cual = rand() % Enemys.size();
		if (Enemys[cual]->aLive) {
			return cual;
		}

		numberControl++;
	}


	return someEnemyAlive();

}



int Scene::TowerAliveRandom() {
	bool controlT = true;
	int numberControl = 0;
	while (numberControl < 10) {
		int cual = rand() % TowersList.size();
		if (TowersList[cual]->estado==GREEN || TowersList[cual]->estado == ORANGE) {
			return cual;
		}

		numberControl++;
	}


	return someTowerAlive();

}


void Scene::tocaRomper(float seconds_elapsed) {

	srand(time(NULL));
	time_enemy_Tower -= seconds_elapsed;
	if (someEnemyAlive()!=-1 && someTowerActive()) {

		if (time_enemy_Tower <= 0.0) {
			bool controlT = true;
			//while (controlT) {
				int cual = TowerAliveRandom() ;
				int enemyN = EnemyMasCerca(TowersList[cual]);
				if (enemyN != -1) {
					Enemys[enemyN]->actualState = DESTRUIR_TORRE;
				}
				time_enemy_Tower = time_enemy_Tower_Max;
				//controlT = false;
			//}

		}
	}
	if (time_enemy_Tower <= 0.0) {
		time_enemy_Tower = time_enemy_Tower_Max;
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


				//podria hacer una funci�n para indicar estas cosas. Roto las figuras para que cuadren en escenario (esquinas , paredes)
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

void Scene::initDecoracion() {
	EntityGameObject* temp;
	int z;
	int x;
	for (int i = 0; i < 11; i++) {
		temp = new EntityGameObject(Texture::Get("data/escena/nave.png"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs"), Mesh::Get("data/escena/nave.obj"), NULL, "game");
		switch (i) {
		case 0:
			z = 0;
			x = 0;
			break;
		case 1:
			z = 40;
			x = 0;
			break;
		case 2:
			z = 110;
			x = 0;
			break;
		case 3:
			z = 190;
			x = 0;
			break;
		case 4:
			z = 240;
			x = 0;
			break;
		case 5:
			z = 350;
			x = 0;
			break;
		case 6:
			x = 40;
			z = 0;
			break;
		case 7:
			x = 190;
			z = 0;
			break;
		case 8:
			x = 110;
			z = 0;
			break;
		case 9:
			x = 0;
			z = 0;
			break;
		case 10:
			x = 240;
			z = 0;
			break;
		case 11:
			x = 350;
			z = 0;
			break;
		}



		temp->model->setTranslation(x, 20, z);
		decoracionList.push_back(temp);
	
	}

}


void Scene::PintarDecoracion() {
	EntityGameObject* temp;


	disparosMoveM.clear();

	for (int i = 0; i < decoracionList.size(); i++) {
		
			//EntitysImpactoPegamento[i]->render(lightScene->light);
			disparosMoveM.push_back(*(decoracionList[i]->model));
		
	}


	if (disparosMoveM.size() > 0) {
		Shader* shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
		shader->enable();
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);//camera->viewprojection_matrix);
		shader->setUniform("u_texture", decoracionList[0]->textura, 0);
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setFloat("u_tilling", 1.0);
		decoracionList[0]->mesh->renderInstanced(GL_TRIANGLES, &(disparosMoveM[0]), (int)disparosMoveM.size());
		shader->disable();
	}

	

}

void Scene::updateDecoracion(float seconds_elapsed) {

	int y;

	for (int i = 0; i < decoracionList.size(); i++) {
		
		if (i >= 0 && i <= 5) {
			Vector3 posit= decoracionList[i]->model->getTranslation();

			if ((posit.z + seconds_elapsed * 10) > 370.0f) {
				posit.z = -170.0f;
			}
			switch (i) {
			case 0:
				y = 0;
				break;
			case 1:
				y = 40;
				break;
			case 2:
				y = 110;
				break;
			case 3:
				y = 190;
				break;
			case 4:
				y = 240;
				break;
			case 5:
				y = 350;
				break;
			}
			decoracionList[i]->model->setTranslation(y, 20, posit.z + seconds_elapsed * (10+i));
			decoracionList[i]->model->rotate(180 * DEG2RAD, Vector3(0, 1, 0));
			//std::cout << "POS " << posit.z + seconds_elapsed * 10 << std::endl;
			
		}
		else {
		
			Vector3 posit = decoracionList[i]->model->getTranslation();

			if ((posit.x + seconds_elapsed * 10) > 370.0f) {
				posit.x = -170.0f;
			}
			switch (i) {
			case 6:
				y = 0;
				break;
			case 7:
				y = 40;
				break;
			case 8:
				y = 110;
				break;
			case 9:
				y = 190;
				break;
			case 10:
				y = 240;
				break;
			case 11:
				y = 350;
				break;
			}
			decoracionList[i]->model->setTranslation(posit.x + seconds_elapsed * (10 + i), 20, y);
			decoracionList[i]->model->rotate(90 * DEG2RAD, Vector3(0, 1, 0));
			//std::cout << "POS " << posit.z + seconds_elapsed * 10 << std::endl;
		
		}
	}

}



bool Scene::checkEndLvl() {

	int control = 0;

	int contadorTowers = 0;
	for (int i = 0; i < TowersList.size(); i++) {

		if (TowersList[i]->estado == GREEN) {
			contadorTowers++;
		}

	}

	if (contadorTowers == TowersList.size()) {
		//return true;
		control++;
	}


	int contadorEnemys = 0;
	for (int i = 0; i < Enemys.size(); i++) {

		if (Enemys[i]->is_node && (Enemys[i]->actualState==E_REPAIR || !Enemys[i]->aLive)) {
			contadorEnemys++;
		}

	}

	if (contadorEnemys == numEnemysNode) {
		//return true;
		control++;
	}


	if (!myPlayer->playerAlive()) {
		return true;
	}


	if (control >= 2 ) {

		return true;
	}




	return false;

}


void Scene::loadEnemys(std::map<std::string, Entity*> enemysMap) {
	int enemy = 0;
	//enemysMap.size()
	srand(time(NULL));

	std::vector<int> nodosRobot;

	int i = 0;
	EntityMesh* en;
	while (i < numEnemysNode) {

		int cual = rand() % 5;
		nodosRobot.push_back(cual);
		switch (cual) {
		case 0:
			en = (EntityMesh*)enemysMap["CompanionBig"];
			enemy = 9;
			break;
		case 1:
			en = (EntityMesh*)enemysMap["MechaTrooperBig"];
			enemy = 10;
			break;
		case 2:
			en = (EntityMesh*)enemysMap["FieldFighterBig"];
			enemy = 11;

			break;
		case 3:
			en = (EntityMesh*)enemysMap["MechaGolemBig"];
			enemy = 12;
			break;
		case 4:
			en = (EntityMesh*)enemysMap["Mecha01Big"];
			enemy = 13;
			break;
		}


		bool controlBucle = true;
		EntityEnemy* temp;

		if (numLvl != 0) {
			while (controlBucle) {

				int tempWidth = rand() % (mapGame->width * 9);
				int tempHeight = rand() % (mapGame->height * 9);

				if (!generatorIA->detectCollision({ tempWidth, tempHeight }) && tempWidth >= 10 && tempHeight >= 10 && tempHeight <= ((mapGame->width * 9) - 10) && tempWidth <= ((mapGame->width * 9) - 10)) {
					temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(tempHeight), 0, float(tempWidth)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
					temp->model->translate(float(tempHeight), 0, float(tempWidth));
					if (enemy != 0) {
						temp->loalAnim(enemy);
					}
					temp->is_node = true;
					temp->actualState = ANDAR_TONTO;
					temp->id_principal = cual;
					controlBucle = false;
				}
			}


		}
		else {
			temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(100), 0, float(100)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
			temp->model->translate(float(100), 0, float(100));
			if (enemy != 0) {
				temp->loalAnim(enemy);
			}
			temp->is_node = true;
			temp->actualState = ANDAR_TONTO;
			temp->id_principal = cual;
		}



		//temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(10), 0, float(10)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
		//temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(10), 0, float(10)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
		//if (enemy != 0) {
		//	temp->loalAnim(enemy);
		//}
		//temp->model->setTranslation(float(10*(i+1)), 0, float(10* (i + 1)));
		//temp->actualState = ANDAR_TONTO;


		addEnemy(temp);


		i++;

	}



	 i = 0;
	while (i < nodosRobot.size()) {
		int o = 0;
		while (o< numEnemysByNode) {
			int cual = nodosRobot[i];

			switch (cual) {
			case 0:
				en = (EntityMesh*)enemysMap["Companion"];
				enemy = 2;
				break;
			case 1:
				en = (EntityMesh*)enemysMap["MechaTrooper"];
				enemy = 4;
				break;
			case 2:
				en = (EntityMesh*)enemysMap["FieldFighter"];
				enemy = 5;
				break;
			case 3:
				en = (EntityMesh*)enemysMap["MechaGolem"];
				enemy = 7;
				break;
			case 4:
				en = (EntityMesh*)enemysMap["Mecha01"];
				enemy = 8;

				break;
			}


			bool controlBucle = true;
			EntityEnemy* temp;

			if (numLvl != 0) {

				while (controlBucle) {

					int tempWidth = rand() % (mapGame->width * 9);
					int tempHeight = rand() % (mapGame->height * 9);

					if (!generatorIA->detectCollision({ tempWidth, tempHeight }) && tempWidth >= 10 && tempHeight >= 10 && tempHeight <= ((mapGame->width * 9) - 10) && tempWidth <= ((mapGame->width * 9) - 10)) {
						temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(tempHeight), 0, float(tempWidth)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
						temp->model->translate(float(tempHeight), 0, float(tempWidth));
						if (enemy != 0) {
							temp->loalAnim(enemy);
						}
						temp->is_node = false;
						temp->actualState = ANDAR_TONTO;
						temp->id_padre = nodosRobot[i];
						controlBucle = false;
					}
				}
			}
			else
			{
				temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(40), 0, float(40)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
				temp->model->translate(float(40), 0, float(70));
				if (enemy != 0) {
					temp->loalAnim(enemy);
				}
				temp->is_node = false;
				temp->actualState = ANDAR_TONTO;
				temp->id_padre = nodosRobot[i];

			}




			//temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(10), 0, float(10)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
			//temp = new EntityEnemy(en->textura, en->shader, en->mesh, en->material, "game", Vector3(float(10), 0, float(10)), ((StagePlay*)Stage::getStage("Play"))->shaderFlatSP);
			//if (enemy != 0) {
			//	temp->loalAnim(enemy);
			//}
			//temp->model->setTranslation(float(10*(i+1)), 0, float(10* (i + 1)));
			//temp->actualState = ANDAR_TONTO;


			addEnemy(temp);
			o++;

		}



		i++;

	}








}

void Scene::pintarCajasLoot() {

	/*for (int i = 0; i < cajasLoot.size(); i++) {
		if (cajasLoot[i]->in_use) {
			cajasLoot[i]->render(lightScene->light,fog_color);
		}

	}*/


	disparosMoveM.clear();

	for (int i = 0; i < cajasLoot.size(); i++) {
		if (cajasLoot[i]->in_use) {
			cajasLoot[i]->model->setTranslation(cajasLoot[i]->position.x, cajasLoot[i]->position.y, cajasLoot[i]->position.z);
			cajasLoot[i]->model->rotate(45 * cajasLoot[i]->time_passed * DEG2RAD, Vector3(0, 1, 0));
			cajasLoot[i]->model->scale(0.5f, 0.5f, 0.5f);
			disparosMoveM.push_back(*(cajasLoot[i]->model));
		}
		//EntitysImpactoPegamento[i]->render(lightScene->light);
	

	}


	if (disparosMoveM.size() > 0) {
		Shader* shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
		shader->enable();
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);//camera->viewprojection_matrix);
		shader->setUniform("u_texture", cajasLoot[0]->textura, 0);
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setFloat("u_tilling", 1.0);
		cajasLoot[0]->mesh->renderInstanced(GL_TRIANGLES, &(disparosMoveM[0]), (int)disparosMoveM.size());
		shader->disable();
	}

}



void Scene::pintarTowerArreglo() {

	for (int i = 0; i < TowersList.size(); i++) {
		TowersList[i]->render(lightScene->light,fog_color);
	}



}


void Scene::pintarGranades() {

	disparosMoveM.clear();
	for (int i = 0; i < granadesMove.size(); i++) {

		if (granadesMove[i]->in_use == true) {
			//disparosMove[i]->render(lightScene->light);
			disparosMoveM.push_back(*(granadesMove[i]->model));
		}
	}



	if (disparosMoveM.size() > 0) {
		Shader* shader = Shader::Get("data/shaders/instanced.vs", "data/shaders/texture.fs");
		shader->enable();
		shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);//camera->viewprojection_matrix);
		shader->setUniform("u_texture", granadetTexture, 0);
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setFloat("u_tilling", 1.0);
		granadeMesh->renderInstanced(GL_TRIANGLES, &(disparosMoveM[0]), (int)disparosMoveM.size());
		shader->disable();
	}



}
