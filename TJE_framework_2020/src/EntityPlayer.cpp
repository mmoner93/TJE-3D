#include "EntityPlayer.h"
#include "Stage.h"
#include "StagePlay.h"

void EntityPlayer::loalAnim() {
	dancing = Animation::Get("data/animations_dancing.skanim");
	walk = Animation::Get("data/animations_walking.skanim");
	//run = Animation::Get("data/personajes/animations_rifle_run.skanim");
	//walk->assignTime(Game::instance->time);
	//run->assignTime(Game::instance->time);
	blendWalkRun = new Skeleton();
	
}

void EntityPlayer::renderAnimated(Light* light) {

	Camera* camera = Camera::current;
	Vector3 ambientLight(0.3, 0.3, 0.3);
	Matrix44 m = *model;

	//enable shader
	shader->enable();

	//m.scale(scale, scale, scale);
	//upload uniforms
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_texture", textura, 0);
	shader->setUniform("u_model", m);
	shader->setUniform("u_time", Game::instance->time);
	shader->setFloat("u_tilling", tilling);
	Vector3 light_direction = light->position - model->getTranslation();
	shader->setUniform("u_light_direction", light_direction);
	shader->setUniform("u_ambient_light", Vector3(0.2, 0.2, 0.2));

	blendSkeleton(&walk->skeleton, &dancing->skeleton, 0.5, blendWalkRun);
	//blendSkeleton(&walk->skeleton, &run->skeleton, 0.5, blendWalkRun);
	mesh->renderAnimated(GL_TRIANGLES, blendWalkRun);
	walk->assignTime(Game::instance->time);
	dancing->assignTime(Game::instance->time);
	shader->disable();
}

void EntityPlayer::render(Light* light) {


	Game* GameI = Game::instance;
	Camera* camera = Camera::current;

	Vector3 eye = *model * Vector3(0, 0.6, -0.2);
	Vector3 front(0, 0, -1);
	Matrix44 PITCH;
	PITCH.setRotation(pitch * DEG2RAD, Vector3(1, 0, 0));
	front = PITCH.rotateVector(front);
	Matrix44 YAW;
	YAW.setRotation(yaw * DEG2RAD, Vector3(0, 1, 0));
	//std::cout << "El pitch es " << pitch << std::endl;
	front = YAW.rotateVector(front);
	Vector3 center = eye + front;
	Vector3 up = Vector3(0, 1, 0);

	if (!GameI->free_cam)
		camera->lookAt(eye, center, up); //position the camera and point to 0,0,0

	//std::cout << "El position es " << particle.pos.x  << "," << particle.pos.y << "," << particle.pos.z  << std::endl;
	//al personaje
	
	//EntityGameObject::render(light);
	renderAnimated(light);
	
	Matrix44* ter = new Matrix44(*model);

	//ter->scale(0.5, 0.5, 0.5);
	ter->translate(0.2, -0.1, (0.01 * pitch) - 0.5);
	ter->rotate(-180 * DEG2RAD, Vector3(0, 1, 0));
	ter->rotate(-pitch * DEG2RAD, Vector3(1, 0, 0));
	weapon->model = ter;

	weapon->render(light);
	
}



void EntityPlayer::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
	if (loadanim == false) {
		loalAnim();
		loadanim = true;
	}
	//dancing.assignTime(Game::instance->time);

	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	Matrix44 R;

	R.setRotation(yaw * DEG2RAD, Vector3(0, 1, 0));
	Vector3 front = R.rotateVector(Vector3(0, 0, -1));
	Vector3 right = R.rotateVector(Vector3(1, 0, 0));
	Vector3 target_pos = position;
	Vector3 delta;

	/*if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) target_pos = position + front * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) target_pos = position - front * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  target_pos = position - right * 10 * speed * seconds_elapsed;
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) target_pos = position + right * 10 * speed * seconds_elapsed;*/
	//if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
	//if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));


	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 8; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		delta = delta+Vector3(1, 0, 0);
	} 
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) delta = delta + Vector3(-1, 0, 0);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  delta = delta + Vector3(0, 0,-1 );
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) delta = delta + Vector3(0, 0, 1);
	if (Input::isKeyPressed(SDL_SCANCODE_C)) {
		shoot();
	}

	delta = delta * (speed + mejoras.velociti);
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
	angle = angle + vel_ang;



	//target_pos = testCollision(target_pos, seconds_elapsed, objects);

	target_pos = testCollision(position, seconds_elapsed, objects);
	//TRS

	//if (!has_collision) 
	position = target_pos;

	//player.model.setIdentity();

	model->setTranslation(position.x, position.y, position.z);

	model->rotate(yaw * DEG2RAD, Vector3(0, 1, 0));
}



Vector3 EntityPlayer::testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects) {

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
		
		if (distance > 20) {
			continue;
		}

		//comprobamos si colisiona el objeto con la esfera (radio 3)
		if (mesh->testSphereCollision(*(en->model), character_center, 0.15, coll, collnorm) == false) {
			continue; //si no colisiona, pasamos al siguiente objeto
		}
		/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
			continue;*/
		has_collision = true;
		std::cout << "He colisionao"<<std::endl;
		Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
		target_pos = position - push_away*((vel_x+vel_y).length() * 1.5);
		target_pos.y = 0;
		break;


	}

	return target_pos;

}


void EntityPlayer::shoot() {
	Game* GameI = Game::instance;
	Camera* camera = Camera::current;
	Vector3 pos = camera->center;
	pos.y = 0;
	Vector3 origin = camera->center;
	Vector3 dir = camera->getRayDirection(Input::mouse_position.x, Input::mouse_position.y, GameI->window_width, GameI->window_height);

	//para poner algo en el suelo
	//pos = RayPlaneCollision(Vector3(),Vector3(0,1,0),origin,dir);
	StagePlay* temp = (StagePlay*)Stage::current_state;
	bool control = true;
	Vector3 collnorm;

	for (int i = 0; i < temp->gameSceneSP->Enemys.size(); i++) {
		EntityGameObject* en = temp->gameSceneSP->Enemys[i];

		Mesh* mesh = en->mesh;

		if (mesh->testRayCollision(*en->model, origin, dir, pos, collnorm,99,true)) {
			temp->gameSceneSP->Enemys[i]->onReceveidShoot(pos);
			control = false;
			break;
		}

	}


	if (control) {
	
	
	for (int i = 0; i < temp->gameSceneSP->mapaObjects.size(); i++) {
		EntityGameObject* en = temp->gameSceneSP->mapaObjects[i];

		Mesh* mesh = en->mesh;

		if (mesh->testRayCollision(*en->model, origin, dir, pos, Vector3())) {
			temp->gameSceneSP->pointsSP.push_back(pos);
			break;
		}

	}
	}
	/*Mesh* mesh = Mesh::Get("data/personajes/ROBOT1.obj");

	if(mesh->testRayCollision(Matrix44(), origin, dir, pos, Vector3()) ){
		points.push_back(pos);
	}*/


}