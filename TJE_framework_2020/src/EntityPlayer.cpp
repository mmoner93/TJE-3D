#include "EntityPlayer.h"
#include "Stage.h"
#include "StagePlay.h"


void EntityPlayer::loalAnim() {
	idle = Animation::Get("data/animations/animations_orc_idle.skanim");
	walk = Animation::Get("data/animations/animations_walking final.skanim");
	run = Animation::Get("data/animations/animations_running.skanim");
	//walk->assignTime(Game::instance->time);
	//run->assignTime(Game::instance->time);
	blendWalkRun = new Skeleton();
	
}

void EntityPlayer::renderAnimated(Light* light) {

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
	float speedFactor = (vel_x + vel_y).length() *0.5;
	if (speedFactor < 1)
	{
		blendSkeleton(&idle->skeleton, &walk->skeleton, speedFactor, blendWalkRun);
	}
	else
	{
		blendSkeleton(&walk->skeleton, &run->skeleton, speedFactor, blendWalkRun);
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
	mesh->renderAnimated(GL_TRIANGLES, blendWalkRun);

	

	shader->disable();
	radar();
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
		fixShoot();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_1)) {
		if (weaponUsing == PEGAMENTO) {
			weaponUsing = WEAPON1;
			weapon = weapons[WEAPON1];
		}
		else {
			weaponUsing = PEGAMENTO;
			weapon = weapons[PEGAMENTO];
		}
	}
	if (Input::isMousePressed(SDL_BUTTON_LEFT) && !shooting) {
		shooting = true;
		if (weaponUsing == PEGAMENTO) {
			fixShoot();
		}
		else {
			shoot();
		}
		

	}


	if (!Input::isMousePressed(SDL_BUTTON_LEFT) && shooting) {
		shooting = false;

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


	retrocesoShoot(seconds_elapsed);

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


void EntityPlayer::fixShoot() {
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

		if (mesh->testRayCollision(*en->model, origin, dir, pos, collnorm, 99, true)) {
			temp->gameSceneSP->Enemys[i]->onReceveidShootPegamento(pos, collnorm);
			control = false;
			break;
		}

	}
	EntityTowerArreglo* t = temp->gameSceneSP->towerTemp;
	if (t->mesh->testRayCollision(*t->model, origin, dir, pos, collnorm, 99, true)) {
		t->onReceveidShootPegamento(pos, collnorm);
		control = false;
	}

	


	if (control) {


		for (int i = 0; i < temp->gameSceneSP->mapaObjects.size(); i++) {
			EntityGameObject* en = temp->gameSceneSP->mapaObjects[i];

			Mesh* mesh = en->mesh;

			if (mesh->testRayCollision(*en->model, origin, dir, pos, collnorm)) {
				//temp->gameSceneSP->pointsSP.push_back(pos);
				
				temp->gameSceneSP->emplacePegamento(pos);
				break;
			}

		}
	}
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
			temp->gameSceneSP->Enemys[i]->onReceveidShoot(pos,collnorm);
			control = false;
			break;
		}

	}


	if (control) {
	
	
	for (int i = 0; i < temp->gameSceneSP->mapaObjects.size(); i++) {
		EntityGameObject* en = temp->gameSceneSP->mapaObjects[i];

		Mesh* mesh = en->mesh;

		if (mesh->testRayCollision(*en->model, origin, dir, pos, collnorm)) {
			//temp->gameSceneSP->disparosPoints.push_back(pos);
			//temp->gameSceneSP->normPointsSP.push_back(collnorm);
			temp->gameSceneSP->emplaceDisparo(pos);
			break;
		}

	}
	}
	//retroceso , pasar segun arma. Con escopeta tambien en pitch de forma random para que lado
	retrocesoOn = true;
	retrocesoLeft = 5.0f;
	/*Mesh* mesh = Mesh::Get("data/personajes/ROBOT1.obj");

	if(mesh->testRayCollision(Matrix44(), origin, dir, pos, Vector3()) ){
		points.push_back(pos);
	}*/


}

void EntityPlayer::renderUI(int type, Texture* tex, float opacity, std::vector<Vector3> listaPoints) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	Mesh quad;

	if (type == 0) {
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));

		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));

	}
	else if (type == 1) {
		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));

		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (type == 2) {
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (type == 3) {
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (type == 4) {
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 1));

	}
	else if (type == 5) {

		for (int i = 0; i < listaPoints.size(); i++) {
			Vector3 positionPoint = listaPoints[i];
			/*positionPoint.x = (((positionPoint.x - (-1.0f)) * (1.0f - (-1.0f))) / (20.0f - 0.0f)) + (-1.0f);
			positionPoint.y = (((positionPoint.y - (-1.0f)) * (1.0f - (-1.0f))) / (20.0f - 0.0f)) + (-1.0f);
			positionPoint.z = (((positionPoint.z - (-1.0f)) * (1.0f - (-1.0f))) / (20.0f - 0.0f)) + (-1.0f);*/
			
			quad.vertices.push_back(positionPoint);
			quad.uvs.push_back(Vector2(1, 1));
		}
		

		//quad.vertices.push_back(Vector3(-0.78, -0.45, 0));
		//quad.uvs.push_back(Vector2(1, 1));
		//quad.vertices.push_back(Vector3(-1, -0.7, 0));
		//quad.uvs.push_back(Vector2(1, 1));
		//quad.vertices.push_back(Vector3(-1, 0.5, 0));
		//quad.uvs.push_back(Vector2(1, 1));
		//quad.vertices.push_back(Vector3(0.0, 0.5, 0));
		//quad.uvs.push_back(Vector2(1, 1));
		/*quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 1));
		//quad.uvs.push_back(Vector2(1, 1));*/

	}

	Shader* shaderTEMP;
	if (type != 5) {
		shaderTEMP = Shader::Get("data/shaders/quad.vs", "data/shaders/texture old.fs");//flat.fs");
	}
	else {
		shaderTEMP = Shader::Get("data/shaders/quad.vs", "data/shaders/flat.fs");//flat.fs");
	}

	shaderTEMP->enable();
	shaderTEMP->setUniform("u_color", Vector4(1, 1, 1, 1));
	//shader->setUniform("u_texture", tex, 0);
	shaderTEMP->setFloat("u_opacity", opacity);
	if (type != 5) {
		quad.render(GL_TRIANGLES);
	}
	else {
		glPointSize(9.0f);
		quad.render(GL_POINTS);
	}

	shaderTEMP->disable();
}

void EntityPlayer::radar() {

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


	Vector3 persona = model->getTranslation();
	persona = *model * persona;
	std::cout << "YAW " << yaw * DEG2RAD << std::endl;
	std::vector<Vector3> tempVector;
	float numMirar = 40.f;
	StagePlay* temp = (StagePlay*)Stage::getStage("Play");
	for (int i = 0; i < temp->gameSceneSP->Enemys.size(); i++) {
		EntityGameObject* en = temp->gameSceneSP->Enemys[i];
		Vector3 objectPositio = en->model->getTranslation();
		
		

		float distance = objectPositio.distance(position);
		model->getRotationOnly();
		objectPositio = *model * objectPositio;



		Vector3 playerPos=model->getTranslation();
		if((persona.x+ numMirar >= objectPositio.x) && (persona.x - numMirar <= objectPositio.x)&&
			(persona.y + numMirar >= objectPositio.y) && (persona.y - numMirar <= objectPositio.y)&&
			(persona.z + numMirar >= objectPositio.z) && (persona.z - numMirar <= objectPositio.z)){

			//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
			//objectPositio = objectPositio-model->getTranslation()  ;
			std::cout << "Vector objectPositio Antes x " << objectPositio.x << " y " << objectPositio.y << " z " << objectPositio.z << std::endl;
			//objectPositio = *model * objectPositio;
			//Vector3 objectPositioT = YAW.rotateVector(objectPositio);
			//objectPositio = objectPositio-objectPositioT;
			//objectPositio = YAW.rotateVector(objectPositio);

			objectPositio.x = (((objectPositio.x - (persona.x - numMirar)) * (1.0f - (-1.0f))) / ((persona.x + numMirar) - (persona.x - numMirar))) + (-1.0f);
			objectPositio.y = (((objectPositio.y - (persona.y - numMirar)) * (1.0f - (-1.0f))) / ((persona.y + numMirar) - (persona.y- numMirar))) + (-1.0f);
			objectPositio.y = (((objectPositio.z - (persona.z - numMirar)) * (1.0f - (-1.0f))) / ((persona.z + numMirar) - (persona.z - numMirar))) + (-1.0f);
			//objectPositio.x = objectPositio.x * -1;

			

			//objectPositio = *model * objectPositio;

			//objectPositio.y = 0.0f;
			//objectPositio.y = objectPositio.y / 20.0f;
			//objectPositio.z = objectPositio.z / 20.0f;
			//objectPositio.x = objectPositio.x / 20.0f;

			std::cout << "Vector objectPositio Despues x " << objectPositio.x << " y " << objectPositio.y << " z " << objectPositio.z << std::endl;
			tempVector.push_back(objectPositio);
		}



	}
	Vector3 Prueba = model->getTranslation();
	std::cout << "Vector prueba Antes x " << Prueba.x << " y " << Prueba.y << " z " << Prueba.z << std::endl;
	persona.x = (((persona.x - (persona.x - numMirar)) * (1.0f - (-1.0f))) / ((persona.x + numMirar) - (persona.x - numMirar))) + (-1.0f);
	persona.y = (((persona.y - (persona.y - numMirar)) * (1.0f - (-1.0f))) / ((persona.y + numMirar) - (persona.y - numMirar))) + (-1.0f);
	persona.z = (((persona.z - (persona.z - numMirar)) * (1.0f - (-1.0f))) / ((persona.z + numMirar) - (persona.z - numMirar))) + (-1.0f);
	//Prueba.y = 0.0f;
	std::cout << "Vector prueba x " << Prueba.x << " y " << Prueba.y << " z " << Prueba.z << std::endl;
	tempVector.push_back(persona);


	/*Prueba = model->getTranslation();
	std::cout << "Vector prueba Antes x " << Prueba.x << " y " << Prueba.y << " z " << Prueba.z << std::endl;
	Prueba.x = (((Prueba.x - (model->getTranslation().x - 20.0f)) * (1.0f - (-1.0f))) / (model->getTranslation().x + 20.0f - (model->getTranslation().x - 20.0f))) + (-1.0f);
	Prueba.z = (((Prueba.y - (model->getTranslation().y - 20.0f)) * (1.0f - (-1.0f))) / (model->getTranslation().y + 20.0f - (model->getTranslation().y - 20.0f))) + (-1.0f);
	Prueba.y = (((Prueba.z- (model->getTranslation().z - 20.0f)) * (1.0f - (-1.0f))) / (model->getTranslation().z + 20.0f - (model->getTranslation().z - 20.0f))) + (-1.0f);
	Prueba.y = 0.0f;
	std::cout << "Vector prueba x " << Prueba.x << " y " << Prueba.y << " z " << Prueba.z << std::endl;
	tempVector.push_back(Prueba);*/


	if (tempVector.size() > 0) {
		renderUI(5, NULL, 1.0f, tempVector);
	}
	




}
void EntityPlayer::retrocesoShoot(float seconds_elapsed) {
	
	if (retrocesoOn) {
		retrocesoLeft -= 20.0f * seconds_elapsed;
		if (retrocesoLeft > 0.0f) {
			pitch -= 20.0f * seconds_elapsed;
		}
		

	}
	

}