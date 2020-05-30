#include "EntityEnemy.h"
#include "Stage.h"
#include "StagePlay.h"
#include "AStar.hpp"
#include "pathfinders.h"
void EntityEnemy::render(Light* light) {

	//al personaje
	EntityGameObject::render(light);
	
	Mesh points_mesh;
	points_mesh.vertices = pointsSP;
	if (pointsSP.size()) {
		renderPoints(&points_mesh);
	}

}



void EntityEnemy::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	
	Vector3 target_pos = position;
   /*Matrix44 R;

	R.setRotation(yaw * DEG2RAD, Vector3(0, 1, 0));
	Vector3 front = R.rotateVector(Vector3(0, 0, -1));
	Vector3 right = R.rotateVector(Vector3(1, 0, 0));
	
	Vector3 delta;*/

	/*if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) target_pos = position + front * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) target_pos = position - front * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  target_pos = position - right * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) target_pos = position + right * 10 * speed * seconds_elapsed;*/
	//if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
	//if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));


	/*if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 2; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		delta = delta + Vector3(1, 0, 0);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) delta = delta + Vector3(-1, 0, 0);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  delta = delta + Vector3(0, 0, -1);
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) delta = delta + Vector3(0, 0, 1);


	delta = delta * speed;
	yaw -= Input::mouse_delta.x * 0.1;

	pitch -= Input::mouse_delta.y * 0.1;
	if (pitch >= 90) {
		pitch = 89.9;
	}
	if (pitch <= -90) {
		pitch = -89.9;
	}


	//para particulas

	Vector3 front1 = Vector3(0, 0, -1);
	//Vector3 right1 = R.rotateVector(Vector3(1, 0, 0));
	Matrix44 R1;
	R1.rotate(angle * DEG2RAD, Vector3(0, 1, 0));
	front1 = R * front;
	vel_x = vel_x + delta.x * front;
	vel_x = vel_x - vel_x * 0.04;

	vel_y = vel_y + delta.z * right;
	vel_y = vel_y - vel_y * 0.04;

	vel_ang += yaw * seconds_elapsed;
	vel_ang = vel_ang - vel_ang * 0.02;
	position = position + vel_x * seconds_elapsed;
	position = position + vel_y * seconds_elapsed;
	angle = angle + vel_ang;*/



	//arget_pos = testCollision(target_pos, seconds_elapsed, objects);
	/*if (checkTime(seconds_elapsed)) {
		target_pos = moveEnemy(seconds_elapsed, objects);
		//TRS

		//if (!has_collision) 
		position = target_pos;

		//player.model.setIdentity();

		model->setTranslation(position.x, position.y, position.z);

		//model->rotate(yaw * DEG2RAD, Vector3(0, 1, 0));
	}*/

	/*if (checkTime(seconds_elapsed)) {

		//if (movs.size() < 1) {
			raroIA();
		//}
		//else {
		//

		//}
		

	}*/

	queHacer(seconds_elapsed,objects);

	timeNextCalcCaminoIa -= seconds_elapsed;
	atacar();

	//puntos = puntos * *model;
	
}

void EntityEnemy::calcularCaminoIA() {
	EntityPlayer* player = ((StagePlay*)Stage::current_state)->gameSceneSP->myPlayer;
	Vector3 yo = model->getTranslation();
	Vector3 playerTe = player->model->getTranslation();

	if (!(((StagePlay*)Stage::current_state)->gameSceneSP->generatorIA->detectCollision({ (int)playerTe.z ,(int)playerTe.x }))) {
		auto path = ((StagePlay*)Stage::current_state)->gameSceneSP->generatorIA->findPath({ (int)yo.z ,(int)yo.x }, { (int)playerTe.z ,(int)playerTe.x });

		int con = 0;
		movs.clear();
		for (auto& coordinate : path) {

			movs.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
		}
	}
	


	

}


void EntityEnemy::raroIA() {

	EntityPlayer* player = ((StagePlay*)Stage::current_state)->gameSceneSP->myPlayer;

	//AStar::Generator temp = ((StagePlay*)Stage::current_state)->gameSceneSP->generatorIA;
	float distance = player->model->getTranslation().distance(model->getTranslation());

	//std::cout << "Generate path ... \n";
	// This method returns vector of coordinates from target to source.
	//auto path = generator.findPath({ (int) model->getTranslation().z, (int) model->getTranslation().x }, { (int)player->model->getTranslation().z, (int)player->model->getTranslation().x });

	
	std::cout << "Del player x "<< (int)player->model->getTranslation().x <<" y " << (int)player->model->getTranslation().y << " z " << (int)player->model->getTranslation().z << std::endl;
	
	if (distance < 30.0) {

		


	if (timeNextCalcCaminoIa <= 0.0) {
	
		calcularCaminoIA();
		timeNextCalcCaminoIa = initTimeNextCalcCaminoIa;
	}



		if (movs.size() > 0) {
			Vector3 movimiento = movs.front();
			model->setTranslation(movimiento.x, movimiento.y, movimiento.z);
			movs.pop_front();
		}
		else {
			actualState = ANDAR_TONTO;
		}

		//con esto va , pero muy lento
	/*	if (((int)path.size() - 2) > 0) {
			model->setTranslation(path[path.size() - 2].y, 0.0, path[path.size() - 2].x);
		}
		else if((int)path.size()==1) {
			model->setTranslation(path[0].y, 0.0, path[0].x);
		}*/
	
	/*	for (auto& coordinate : path) {
			std::cout << coordinate.x << " " << coordinate.y << "\n";
			movs.push_front(Vector3(coordinate.y, 0.0, coordinate.x));
			//model->setTranslation(coordinate.y, 0.0, coordinate.x);
			//break;

		}*/
    

	}

	/*for (auto& coordinate : path) {
		std::cout << coordinate.x << " " << coordinate.y << "\n";

		model->setTranslation(coordinate.y, 0.0, coordinate.x);
		break;

	}*/

}


void EntityEnemy::raroIA2() {

	EntityPlayer* player = ((StagePlay*)Stage::current_state)->gameSceneSP->myPlayer;
	uint8* mapPARAIA = ((StagePlay*)Stage::current_state)->gameSceneSP->mapPARAIA;
	//here we must fill the map with all the info
	//...
	//when we want to find the shortest path, this array contains the shortest path, every value is the Nth position in the map, 100 steps max
	int output[100];

	//we call the path function, it returns the number of steps to reach target, otherwise 0
	int path_steps = AStarFindPathNoTieDiag(
		(int)model->getTranslation().z, (int)model->getTranslation().x, //origin (tienen que ser enteros)
		(int)player->model->getTranslation().z, (int)player->model->getTranslation().x, //target (tienen que ser enteros)
		mapPARAIA, //pointer to map data
		32*9, 32 * 9, //map width and height
		output, //pointer where the final path will be stored
		100); //max supported steps of the final path

//check if there was a path
	if (path_steps != -1)
	{
		for (int i = 0; i < path_steps; ++i) {
			std::cout << "X: " << (output[i] % ((StagePlay*)Stage::current_state)->gameSceneSP->mapGame->width * 9) << ", Y: " << floor(output[i] / (((StagePlay*)Stage::current_state)->gameSceneSP->mapGame->width * 9)) << std::endl;
			
		}
		model->setTranslation((float)floor(output[0] / (((StagePlay*)Stage::current_state)->gameSceneSP->mapGame->width * 9)), 0.0, (float)(output[0] % ((StagePlay*)Stage::current_state)->gameSceneSP->mapGame->width * 9));
	
	}





	/*for (auto& coordinate : path) {
		std::cout << coordinate.x << " " << coordinate.y << "\n";

		model->setTranslation(coordinate.y, 0.0, coordinate.x);
		break;

	}*/

}
void EntityEnemy :: queHacer(float seconds_elapsed, std::vector<EntityGameObject*> objects) {


	switch (actualState) {
	case STOP_R:
		break;
	case ANDAR_TONTO:
		if (checkTime(seconds_elapsed)) {
			Vector3 target_pos = moveEnemy(seconds_elapsed, objects);
			//TRS

			//if (!has_collision) 
			position = target_pos;

			//player.model.setIdentity();

			model->setTranslation(position.x, position.y, position.z);

			//model->rotate(yaw * DEG2RAD, Vector3(0, 1, 0));
		}
		break;
	case ANDAR_LISTO:
		if (checkTime(seconds_elapsed)) {
			raroIA();
		}
		break;
	default:std::cout << "Estado de robot no localizado" << std::endl; break;
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


	EntityPlayer* player = ((StagePlay*)Stage::current_state)->gameSceneSP->myPlayer;

	Vector3 director = player->model->getTranslation() - model->getTranslation();
	director = director.normalize();
	//std::cout << "el vector es : x " << director.x << " y :" << director.y << "z: " << director.z << std::endl;

	float distance = player->model->getTranslation().distance(model->getTranslation());


	/*
	if (actualDirection != STOP) {
		switch (actualDirection) {
		case 3:
			actualDirection = UP;
			target_pos = position + Vector3(0, 0, -1) * 1 * speed * seconds_elapsed;
			break;
		case 1:
			actualDirection = LEFT;
			target_pos = position - Vector3(1, 0, 0) * 1 * speed * seconds_elapsed;
			break;
		case 2:
			actualDirection = RIGHT;
			target_pos = position - Vector3(-1, 0, 0) * 1 * speed * seconds_elapsed;
			break;
		case 4:
			actualDirection = DOWN;
			target_pos = position + Vector3(0, 0, +1) * 1 * speed * seconds_elapsed;
			break;

		}
		if (testCollision(target_pos, seconds_elapsed, objects)) {
			return target_pos;
		}
		
	}
	
	*/

	target_pos = model->getTranslation() + director*0.1;


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
				target_pos = model->getTranslation() + Vector3(0, 0, -1) * 1 * speed * seconds_elapsed;
				break;
			case 1:
				actualDirection = LEFT;
				target_pos = model->getTranslation() - Vector3(1, 0, 0) * 1 * speed * seconds_elapsed;
				break;
			case 2:
				actualDirection = RIGHT;
				target_pos = model->getTranslation() - Vector3(-1, 0, 0) * 1 * speed * seconds_elapsed;
				break;
			case 4:
				actualDirection = DOWN;
				target_pos = model->getTranslation() + Vector3(0, 0, +1) * 1 * speed * seconds_elapsed;
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
				target_pos = model->getTranslation() + Vector3(0, 0, -1)   * speed * seconds_elapsed;
				break;
			case 1:
				moveTo = LEFT;
				actualDirection = LEFT;
				target_pos = model->getTranslation() - Vector3(1, 0, 0)   * speed * seconds_elapsed;
				break;
			case 2:
				moveTo = RIGHT;
				actualDirection = RIGHT;
				target_pos = model->getTranslation() - Vector3(-1, 0, 0)   * speed * seconds_elapsed;
				break;
			case 3:
				moveTo = DOWN;
				actualDirection = DOWN;
				target_pos = model->getTranslation() + Vector3(0, 0, +1)  * speed * seconds_elapsed;
				break;

			}

			goodMove = testCollision(target_pos, seconds_elapsed, objects);



		}




	
	
	

	

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

		float distance = objectPositio.distance(position);

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

void EntityEnemy::onReceveidShoot(Vector3 temp) {

	pointsSP.push_back(temp);

}

void EntityEnemy::atacar() {
	if (mirarSiPlayerCerca()) {
		std::cout << "ATACO"<<std::endl;
	}

}

bool EntityEnemy::mirarSiPlayerCerca() {


	EntityPlayer* player=((StagePlay*)Stage::current_state)->gameSceneSP->myPlayer;


	float distance=player->model->getTranslation().distance(model->getTranslation());

	//std::cout << "Distancia del player " << distance << std::endl;

	if (distance <= 2.0) {
		return true;
	}
	else {
		return false;
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


