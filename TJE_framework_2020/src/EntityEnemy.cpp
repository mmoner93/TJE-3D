#include "EntityEnemy.h"
#include "Stage.h"
#include "StagePlay.h"
#include "AStar.hpp"
#include "pathfinders.h"


void EntityEnemy::loalAnim(int enemy) {
	if (enemy == 2) {
		idle = Animation::Get("data/animations/companion/animations_idle.skanim");
		walk = Animation::Get("data/animations/companion/animations_walking.skanim");
		run = Animation::Get("data/animations/companion/animations_running.skanim");
		animated = true;
	}
	if (enemy == 4) {
		idle = Animation::Get("data/animations/mechatrooper/animations_idle.skanim");
		walk = Animation::Get("data/animations/mechatrooper/animations_mutant_walking.skanim");
		run = Animation::Get("data/animations/mechatrooper/animations_running.skanim");
		animated = true;
	}
	if (enemy == 5) {
		idle = Animation::Get("data/animations/fieldfighter/animations_idle.skanim");
		walk = Animation::Get("data/animations/fieldfighter/animations_walking.skanim");
		run = Animation::Get("data/animations/fieldfighter/animations_running.skanim");
		animated = true;
	}
	if (enemy == 7) {
		idle = Animation::Get("data/animations/mechagolem/animations_idle.skanim");
		walk = Animation::Get("data/animations/mechagolem/animations_walking.skanim");
		run = Animation::Get("data/animations/mechagolem/animations_running.skanim");
		animated = true;
	}
	if (enemy == 8) {
		idle = Animation::Get("data/animations/mecha01/animations_idle.skanim");
		walk = Animation::Get("data/animations/mecha01/animations_walking.skanim");
		run = Animation::Get("data/animations/mecha01/animations_running.skanim");
		animated = true;
	}
	if (enemy == 9) {
		idle = Animation::Get("data/animations/companion/animations_idle_big.skanim");
		walk = Animation::Get("data/animations/companion/animations_walking_big.skanim");
		run = Animation::Get("data/animations/companion/animations_running_big.skanim");
		animated = true;
	}
	if (enemy == 10) {
		idle = Animation::Get("data/animations/mechatrooper/animations_idle big.skanim");
		walk = Animation::Get("data/animations/mechatrooper/animations_walking big.skanim");
		run = Animation::Get("data/animations/mechatrooper/animations_running big.skanim");
		animated = true;
	}
	if (enemy == 11) {
		idle = Animation::Get("data/animations/fieldfighter/animations_idle_big.skanim");
		walk = Animation::Get("data/animations/fieldfighter/animations_walking_big.skanim");
		run = Animation::Get("data/animations/fieldfighter/animations_running_big.skanim");
		animated = true;
	}
	if (enemy == 12) {
		idle = Animation::Get("data/animations/mechagolem/animations_idle_big.skanim");
		walk = Animation::Get("data/animations/mechagolem/animations_walking_big.skanim");
		run = Animation::Get("data/animations/mechagolem/animations_running_big.skanim");
		animated = true;
	}
	if (enemy == 13) {
		idle = Animation::Get("data/animations/mecha01/animations_idle_big.skanim");
		walk = Animation::Get("data/animations/mecha01/animations_walking_big.skanim");
		run = Animation::Get("data/animations/mecha01/animations_running_big.skanim");
		animated = true;
	}
	blendWalkRun = new Skeleton();

}



void EntityEnemy::renderAnimated(Light* light) {

	Camera* camera = Camera::current;
	Vector3 ambientLight(0.3, 0.3, 0.3);
	Matrix44 m = *model;

	//animations
	float t = fmod(Game::instance->time, idle->duration) / idle->duration;
	idle->assignTime(Game::instance->time);
	t = fmod(Game::instance->time, walk->duration) / walk->duration;
	walk->assignTime(t * walk->duration);
	t = fmod(Game::instance->time, run->duration) / run->duration;
	run->assignTime(t * run->duration);
	// timeanim -> duration1
	// xtime    -> duration 2
	// x = (timeanim*duration 2)/duration1
	float speedFactor = 0.5; // (vel_x + vel_y).length() * 0.5;
	if (speedFactor < 1)
	{
		blendSkeleton(&idle->skeleton, &walk->skeleton, 0.5, blendWalkRun);
	}
	else
	{
		blendSkeleton(&walk->skeleton, &run->skeleton, 0.5, blendWalkRun);
	}
	


	//enable shader
	shader->enable();

	//m.scale(scale, scale, scale);
	//upload uniforms
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_texture", textura, 0);
	shader->setUniform("u_model", m);
	shader->setUniform("u_time", Game::instance->time);
	Vector3 light_direction = light->position - model->getTranslation();
	shader->setUniform("u_light_direction", light_direction);
	shader->setUniform("u_camera_position", camera->eye);
	shader->setFloat("u_tilling", tilling);


	//blendSkeleton(&walk->skeleton, &run->skeleton, 0.5, blendWalkRun);
	if (actualState == E_REPAIR  || actualState ==STUNNED) {
		mesh->renderAnimated(GL_TRIANGLES, &idle->skeleton);
	}
	else {
		mesh->renderAnimated(GL_TRIANGLES, blendWalkRun); 
	}
	



	shader->disable();

}


void EntityEnemy::render(Light* light) {

	//al personaje
	

	if (animated == true)
	{
		renderAnimated(light);
	}
	else
	{
		EntityGameObject::render(light);
	}
	
	//EntityGameObject::render(light);

	/*Mesh points_mesh;
	points_mesh.vertices = pointsSP;
	if (pointsSP.size()) {
		renderPoints(&points_mesh);
	}*/

	//para disparos normales
	for (int i=0; i < pointsSP.size(); i++) {
	
		EntityGameObject* temp = new EntityGameObject(disparoTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), disparoMesh, NULL, "Game",1.0f);
		
		Vector3 mov = model->getTranslation();
		//temp->model->setIdentity();
		
		
		*(temp->model) = *model;
	
		Vector3 push_away = normalize(normPointsSP[i] - pointsSP[i]);
		Vector3 proe = pointsSP[i] - normalize(normPointsSP[i])*0.1;

		temp->model->translate(pointsSP[i].x, pointsSP[i].y, pointsSP[i].z);
		temp->model->scale(0.5f, 0.5f,0.5f);
		
		temp->render(light);
		
	}


	//para disparos Pegamento
	for (int i = 0; i < pointsSPegamento.size(); i++) {

		EntityGameObject* temp = new EntityGameObject(disparoPegamentoTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), disparoMeshPegamento, NULL, "Game", 1.0f);
		//temp->model->translate(pointsSP[i].x, pointsSP[i].y, pointsSP[i].z);
		Vector3 mov = model->getTranslation();
		temp->model->setIdentity();
		//temp->model->translate(mov.x, mov.y, mov.z);
		//Matrix44 modelTemp = *(temp->model) * *model;
		*(temp->model) = *model;
		//Vector3 proe = pointsSP[i] + normPointsSP[i];
		//Vector3 push_away = normalize(normPointsSP[i] - pointsSPegamento[i]);
		Vector3 proe = pointsSPegamento[i];// -normalize(normPointsSP[i]) * 0.1;
		//temp->model->translate(pointsSP[i].x, pointsSP[i].y, pointsSP[i].z);
		temp->model->translate(proe.x, proe.y, proe.z);
		//temp->model = *(temp->model) * normPointsSP[i];
		temp->render(light);

	}

	if (shield > 0.0f && is_node) {
		EntityGameObject* temp = new EntityGameObject(shieldTexture, Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs"), shieldMesh, NULL, "Game", 1.0f);
		Vector3 mov = model->getTranslation();
		temp->model->setIdentity();
	   * (temp->model) = *model;
	    temp->model->translate(0, 2.5, 0);
		
		temp->model->rotate(45* time_shield_rotate * DEG2RAD, Vector3(0, 1, 0));
		temp->model->scale(0.5f, 0.5f, 0.5f);
		temp->render(light);
	}




}



void EntityEnemy::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
   
	if (aLive) {
		queHacer(seconds_elapsed, objects);

		if (timeNextCalcCaminoIa >0.0) {
			timeNextCalcCaminoIa -= seconds_elapsed;
		}
			
		timeNextAttack -= seconds_elapsed;
		if (timeStuned > 0.0) {
			timeStuned -= seconds_elapsed;
		}
		if (timeStuned <= 0.0 && actualState==STUNNED) {
			pointsSPegamento.clear();
			actualState = ANDAR_TONTO;
		}
		if (actualState != STUNNED && actualState != E_REPAIR) {
			atacar();
		}
		mirarSiPisoPegamento();
		time_shield_rotate += seconds_elapsed;


		if (shield <= 0.0f & is_node && actualState!= E_REPAIR) {
			timeNextShield -= seconds_elapsed;
			if (timeNextShield <= 0.0f) {
				timeNextShield = timeNextShieldMax;
				shield = 4.0f;
			}
			
		}

	}
	
}










void EntityEnemy::calcularCaminoIA() {
	EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;
	Vector3 yo = model->getTranslation();
	Vector3 playerTe = player->model->getTranslation();

	if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)playerTe.z ,(int)playerTe.x }))) {
		if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)yo.z ,(int)yo.x }))) {
			auto path = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->findPath({ (int)yo.z ,(int)yo.x }, { (int)playerTe.z ,(int)playerTe.x });

			int con = 0;
			movs.clear();
			for (auto& coordinate : path) {

				movs.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
			}
		}
		else {
		

			EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;

			Vector3 director = player->model->getTranslation() - model->getTranslation();
			director = director.normalize();
			//std::cout << "el vector es : x " << director.x << " y :" << director.y << "z: " << director.z << std::endl;

			float distance = player->model->getTranslation().distance(model->getTranslation());


			Vector3 target_pos = model->getTranslation() + director * 0.1;


			Vector3 push_away = normalize(target_pos - model->getTranslation());
			push_away = model->getTranslation() - push_away*2.0;
			if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)push_away.z ,(int)push_away.x }))) {
				auto path = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->findPath({ (int)yo.z ,(int)yo.x }, { (int)playerTe.z ,(int)playerTe.x });

				int con = 0;
				movs.clear();
				for (auto& coordinate : path) {

					movs.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
				}
			}
		}

		
	}
	//calculando = false;


	

}
bool EntityEnemy::estoyEnUsoIACalc() {


	for (int i=0; i < ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->Enemys.size(); i++) {
	
		if (((StagePlay*)Stage::current_state)->gameSceneSP->Enemys[i]->calculando) {
			return true;
		}

	}

	return false;
	
}

void EntityEnemy::raroIA() {

	EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;

	//AStar::Generator temp = ((StagePlay*)Stage::current_state)->gameSceneSP->generatorIA;
	float distance = player->model->getTranslation().distance(model->getTranslation());

	//std::cout << "Generate path ... \n";
	// This method returns vector of coordinates from target to source.
	//auto path = generator.findPath({ (int) model->getTranslation().z, (int) model->getTranslation().x }, { (int)player->model->getTranslation().z, (int)player->model->getTranslation().x });

	
	std::cout << "Del player x "<< (int)player->model->getTranslation().x <<" y " << (int)player->model->getTranslation().y << " z " << (int)player->model->getTranslation().z << std::endl;
	
	if (distance < 30.0) {

		


	if (timeNextCalcCaminoIa <= 0.0) {
	
		//if (!estoyEnUsoIACalc()) {
		//	calculando = true;
			
		//}
		if (movs.size() == 0) {
			calcularCaminoIA();
		}
		
		timeNextCalcCaminoIa = initTimeNextCalcCaminoIa;
	}

	moveWithIaList();

		
    

	}


}






void EntityEnemy :: queHacer(float seconds_elapsed, std::vector<EntityGameObject*> objects) {

	EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;

	Vector3 playPos = player->model->getTranslation();
	Matrix44 inv = *player->model;
	Matrix44 invEnem = *model;
	inv.inverse();
	invEnem.inverse();
	playPos = invEnem * playPos;

	Vector3 enPos = model->getTranslation();


	enPos = invEnem * enPos;


	Vector3 director = playPos - enPos;


	//if (director.x != 0 && director.y != 0 && director.z != 0)
		//director = director.normalize();
	//std::cout << "el vector es : x " << director.x << " y :" << director.y << "z: " << director.z << std::endl;
	float target_angle = atan2(director.z, director.x);
	
	
	switch (actualState) {
	case STOP_R:
		break;
	case ANDAR_TONTO:
		
		

		if (checkTime(seconds_elapsed)) {
			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
			Vector3 target_pos = moveEnemy(seconds_elapsed, objects);
			//TRS

			//if (!has_collision) 
			position = target_pos;

			//player.model.setIdentity();

			model->setTranslation(position.x, position.y, position.z);
			
			

			//para rotar y que te mire---------------
			playPos = player->model->getTranslation();
			 inv = *player->model;
			 invEnem = *model;
			inv.inverse();
			invEnem.inverse();
			playPos = invEnem * playPos;

			 enPos = model->getTranslation();


			enPos = invEnem * enPos;


		  Vector3 director = playPos - enPos;
		  target_angle = atan2(director.z, director.x);

			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));

			//para rotar y que te mire--------------- END
		}
		//if (0.0 != target_angle) {
		//	angle = target_angle;
		//	model->rotate(angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
		//}
		
		break;
	case ANDAR_LISTO:
		if (checkTime(seconds_elapsed)) {
			raroIA();
		}
		break;
	case DESTRUIR_TORRE:
		if (checkTime(seconds_elapsed)) {
			goDestroyTower();
		}
		break;
	case E_REPAIR:
		break;
	case STUNNED:
		break;
	default:std::cout << "Estado de robot no localizado" << std::endl; break;
	}


}




void EntityEnemy::goDestroyTower() {
	Scene* temp = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP;

	int torre=temp->towerMasCerca(this);
	

	Vector3 towerPos=temp->TowersList[torre]->model->getTranslation();
	Vector3 yo = model->getTranslation();

	
	

	if (movs_tower.size() == 0) {
	
		if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)towerPos.z ,(int)towerPos.x })) &&
			!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)yo.z ,(int)yo.x }))) {

			auto path = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->findPath({ (int)yo.z ,(int)yo.x }, { (int)towerPos.z ,(int)towerPos.x });
			movs_tower.clear();
			for (auto& coordinate : path) {

				movs_tower.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
			}

		}
		else if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)towerPos.z ,(int)towerPos.x })) &&
			!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)yo.z-1 ,(int)yo.x-1 }))) {
			auto path = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->findPath({ (int)yo.z-1 ,(int)yo.x-1 }, { (int)towerPos.z ,(int)towerPos.x });
			movs_tower.clear();
			for (auto& coordinate : path) {

				movs_tower.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
			}
		}
		else {
			Vector3 director = towerPos - model->getTranslation();
			director = director.normalize();
			//std::cout << "el vector es : x " << director.x << " y :" << director.y << "z: " << director.z << std::endl;

			float distance = towerPos.distance(model->getTranslation());


			Vector3 target_pos = model->getTranslation() + director * 0.1;


			Vector3 push_away = normalize(target_pos - model->getTranslation());
			push_away = model->getTranslation() - push_away * 2.0;
			if (!(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->detectCollision({ (int)push_away.z ,(int)push_away.x }))) {
				auto path = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->generatorIA->findPath({ (int)yo.z ,(int)yo.x }, { (int)towerPos.z ,(int)towerPos.x });

				int con = 0;
				movs.clear();
				for (auto& coordinate : path) {

					movs.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
				}
			}

		
		}
	}
	
	

	moveWithIaListTower();

	/*if (movs_tower.size() > 0) {
		Vector3 movimiento = movs_tower.front();
		model->setTranslation(movimiento.x, movimiento.y, movimiento.z);
		movs_tower.pop_front();
		if (movs_tower.size() == 0) {
			temp->TowersList[torre]->breakTower();
			actualState = ANDAR_TONTO;
		}
	}*/
	if (movs_tower.size() == 0) {
		temp->TowersList[torre]->breakTower();
		actualState = ANDAR_TONTO;
	}
}

void EntityEnemy::moveWithIaList() {

	if (movs.size() > 0) {


		nextMovelist = movs.front();

		Vector3 director = nextMovelist - model->getTranslation();
		if (director.x != 0 && director.y != 0 && director.z != 0)
			director = director.normalize();
		if (abs(director.x)>=0.04 || abs(director.y) >= 0.04 || abs(director.z) >= 0.04) {
			Vector3 target_pos = model->getTranslation() + director*0.25 ;
			Vector3 director = nextMovelist - model->getTranslation();
			model->setTranslation(target_pos.x, target_pos.y, target_pos.z);

			float target_angle = atan2(director.z, director.x);

			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
		}
		else {
			Vector3 movimiento = movs.front();
			Vector3 director = nextMovelist - model->getTranslation();
			model->setTranslation(movimiento.x, movimiento.y, movimiento.z);
			
			float target_angle = atan2(director.z, director.x);

			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
			movs.pop_front();
		}

	}
	else {
		actualState = ANDAR_TONTO;
	}
}




void EntityEnemy::moveWithIaListTower() {

	if (movs_tower.size() > 0) {


		nextMovelist = movs_tower.front();

		Vector3 director = nextMovelist - model->getTranslation();
		if (director.x != 0 && director.y != 0 && director.z != 0)
			director = director.normalize();
		if (abs(director.x) >= 0.04 || abs(director.y) >= 0.04 || abs(director.z) >= 0.04) {
			Vector3 target_pos = model->getTranslation() + director * 0.25;
			Vector3 director = nextMovelist - model->getTranslation();
			model->setTranslation(target_pos.x, target_pos.y, target_pos.z);

			float target_angle = atan2(director.z, director.x);

			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
		}
		else {
			Vector3 movimiento = movs_tower.front();
			Vector3 director = nextMovelist - model->getTranslation();
			model->setTranslation(movimiento.x, movimiento.y, movimiento.z);

			float target_angle = atan2(director.z, director.x);

			model->rotate(target_angle * RAD2DEG * DEG2RAD, Vector3(0, 1, 0));
			movs_tower.pop_front();
		}

	}
	else {
		actualState = ANDAR_TONTO;
	}
}

Vector3  EntityEnemy::moveEnemy(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
	float speed = (float)seconds_elapsed * (float)200;
	int whatToMake = rand() % 4;
	enumEnemyMove moveTo = STOP;
	bool goodMove = false;
	Vector3 target_pos;
	//falta hacer front y right para que rote?
	//falta meter que rote? o arriba ?


	EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;

	Vector3 playPos = player->model->getTranslation();
	Matrix44 inv = *player->model;
	Matrix44 invEnem = *model;
	inv.inverse();
	invEnem.inverse();
	//playPos = invEnem * playPos;

	Vector3 enPos = model->getTranslation();
	
	
	//enPos = invEnem * enPos;


	Vector3 director = playPos - enPos;

	
	if(director.x!=0 && director.y != 0 && director.z != 0 )
	director = director.normalize();
	//std::cout << "el vector es : x " << director.x << " y :" << director.y << "z: " << director.z << std::endl;
	
	float distance = player->model->getTranslation().distance(model->getTranslation());
	

	target_pos = model->getTranslation() + director*0.018;
	

	if (distance < 30.0 && contadorCollisions < 5 ) {
		if (testCollision(target_pos, seconds_elapsed, objects)) {
			return target_pos;

		}
		else {

			contadorCollisions++;
		}

	}
	

	if (contadorCollisions == 5) {
		actualState = ANDAR_LISTO;
		contadorCollisions = 0;
	}


		if (actualDirection != STOP && contadorMovimientos<200) {
			switch (actualDirection) {
			case 3:
				actualDirection = UP;
				target_pos = model->getTranslation() + Vector3(0, 0, -1) * 10 * speed * seconds_elapsed;
				break;
			case 1:
				actualDirection = LEFT;
				target_pos = model->getTranslation() - Vector3(1, 0, 0) * 10 * speed * seconds_elapsed;
				break;
			case 2:
				actualDirection = RIGHT;
				target_pos = model->getTranslation() - Vector3(-1, 0, 0) * 10 * speed * seconds_elapsed;
				break;
			case 4:
				actualDirection = DOWN;
				target_pos = model->getTranslation() + Vector3(0, 0, +1) * 10 * speed * seconds_elapsed;
				break;

			}
			if (testCollision(target_pos, seconds_elapsed, objects)) {
				contadorMovimientos++;
				return target_pos;

			}

		}


		while (!goodMove) {
			whatToMake = rand() % 4;
			switch (whatToMake) {
			case 0:
				moveTo = UP;
				actualDirection = UP;
				target_pos = model->getTranslation() + Vector3(0, 0, -1) * 10 * speed * seconds_elapsed;
				break;
			case 1:
				moveTo = LEFT;
				actualDirection = LEFT;
				target_pos = model->getTranslation() - Vector3(1, 0, 0) * 10 * speed * seconds_elapsed;
				break;
			case 2:
				moveTo = RIGHT;
				actualDirection = RIGHT;
				target_pos = model->getTranslation() - Vector3(-1, 0, 0) * 10 * speed * seconds_elapsed;
				break;
			case 3:
				moveTo = DOWN;
				actualDirection = DOWN;
				target_pos = model->getTranslation() + Vector3(0, 0, +1) * 10 * speed * seconds_elapsed;
				break;

			}

			goodMove = testCollision(target_pos, seconds_elapsed, objects);



		}




	
	
	

	
		contadorCollisions = 0;
		contadorMovimientos = 0;
	    return target_pos;
		

}
//de momento lo dejo aqui. Se puede transladar cuando haga mecanica pensada de "pegamento" para reparar.
void EntityEnemy::renderPoints(Mesh* meshT)
{
	if (!shaderPuntos)
		return;

	Camera* camera = Camera::current;

	//enable shader
	shaderPuntos->enable();

	//upload uniforms
	shaderPuntos->setUniform("u_color", Vector4(1, 1, 1, 1));
	shaderPuntos->setUniform("u_viewprojection", camera->viewprojection_matrix);
	
	
	
	shaderPuntos->setUniform("u_model", *model);
	shaderPuntos->setFloat("u_tilling", 1.0);
	//shader->setUniform("u_time", time);
	meshT->render(GL_POINTS, -1);

	//disable shader
	shaderPuntos->disable();
}

bool EntityEnemy::testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects) {

	//calculamos el centro de la esfera de colisión del player elevandola hasta la cintura
	Vector3 character_center = target_pos + Vector3(0, 0.65, 0);
	bool has_collision = false;

	for (int i = 0; i < objects.size(); i++)
	{

		EntityGameObject* en = objects[i];

		Mesh* mesh = en->mesh;

		//para cada objecto de la escena...
		Vector3 coll;
		Vector3 collnorm;

		Vector3 objectPositio = en->model->getTranslation();

		float distance = objectPositio.distance(objectPositio);

		if (distance > 10) {
			continue;
		}

		//comprobamos si colisiona el objeto con la esfera (radio 3)
		if (mesh->testSphereCollision(*(en->model), character_center, 0.15, coll, collnorm) == false) {
			continue; //si no colisiona, pasamos al siguiente objeto
		}
		/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
			continue;*/
		has_collision = true;
		//std::cout << "He colisionao" << std::endl;
		//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
		//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
		//target_pos.y = 0;
		break;


	}

	return !has_collision;

}


bool EntityEnemy::checkTime(float seconds_elapsed) {
	timeNextMove -= seconds_elapsed;

	if (timeNextMove <= 0.0) {
		timeNextMove = timeTopNextMove;
		return true;
	}

	return false;


}

void EntityEnemy::onReceveidShoot(Vector3 temp, Vector3 norm) {

	pointsSP.push_back(temp);
	normPointsSP.push_back(norm);

	if (is_node) {
	
		if (shield <= 0.0f) {
			health -= 1.0;
			if (health <= 0.0) {
				aLive = false;
			}
		}
		else {
			shield -= 1.0f;
		}
	}
	else {
		health -= 1.0;
		if (health <= 0.0) {
			aLive = false;
		}
	}

	
}

void EntityEnemy::onReceveidShootPegamento(Vector3 temp, Vector3 norm) {
	pointsSPegamento.push_back(temp);
	if (is_node) {

		if (shield <= 0.0f) {
			num_pegamento_in++;
			if (num_pegamento_in >= 3) {
				actualState = E_REPAIR;
				((StagePlay*)Stage::getStage("Play"))->gameSceneSP->turnAllMiniosOff(id_principal);
			}
		}

		
	}
	else {
		actualState = STUNNED;
		timeStuned = timeStunedMax;
	}

}
void EntityEnemy::atacar() {
	if (timeNextAttack <= 0.0) {
		if (mirarSiPlayerCerca()) {
			std::cout << "ATACO" << std::endl;
			EntityPlayer* player = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;
			player->health -= 1.0f;
			timeNextAttack = timeNextAttackMax;
		}
	}
	

}

bool EntityEnemy::mirarSiPlayerCerca() {


	EntityPlayer* player=((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer;


	float distance=player->model->getTranslation().distance(model->getTranslation());

	//std::cout << "Distancia del player " << distance << std::endl;

	if (distance <= 2.0) {
		return true;
	}
	else {
		return false;
	}

}

void EntityEnemy::mirarSiPisoPegamento() {
	Scene* tempScene = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP;
	


	if (is_node) {
		if (shield <= 0.0f) {
			for (int i = 0; i < tempScene->EntitysImpactoPegamento.size(); i++) {

				if (tempScene->EntitysImpactoPegamento[i]->in_use) {
					float distance = model->getTranslation().distance(tempScene->EntitysImpactoPegamento[i]->model->getTranslation());
					if (distance <= 2.0) {
						Vector3 coll;
						Vector3 collnorm;
						if (mesh->testSphereCollision(*(model), tempScene->EntitysImpactoPegamento[i]->model->getTranslation(), 0.05, coll, collnorm, true) == false) {
							continue; //si no colisiona, pasamos al siguiente objeto
						}
						tempScene->EntitysImpactoPegamento[i]->in_use = false;
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < tempScene->EntitysImpactoPegamento.size(); i++) {

			if (tempScene->EntitysImpactoPegamento[i]->in_use) {
				float distance = model->getTranslation().distance(tempScene->EntitysImpactoPegamento[i]->model->getTranslation());
				if (distance <= 2.0) {
					Vector3 coll;
					Vector3 collnorm;
					if (mesh->testSphereCollision(*(model), tempScene->EntitysImpactoPegamento[i]->model->getTranslation(), 0.05, coll, collnorm, true) == false) {
						continue; //si no colisiona, pasamos al siguiente objeto
					}

					tempScene->EntitysImpactoPegamento[i]->in_use = false;
				}
			}


		}
	}


	
}

void EntityEnemy::contadorMovUp() {

	contadorMovimientos++;
	if (contadorMovimientos > 40) {
		contadorMovimientos = 0;
	}

}
void EntityEnemy::contadorCollUp() {


}


