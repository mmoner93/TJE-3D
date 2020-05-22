#include "EntityPlayer.h"

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
	std::cout << "El pitch es " << pitch << std::endl;
	front = YAW.rotateVector(front);
	Vector3 center = eye + front;
	Vector3 up = Vector3(0, 1, 0);

	if (!GameI->free_cam)
		camera->lookAt(eye, center, up); //position the camera and point to 0,0,0

	std::cout << "El position es " << particle.pos.x  << "," << particle.pos.y << "," << particle.pos.z  << std::endl;
	//al personaje
	EntityGameObject::render(light);

	Matrix44* ter = new Matrix44(*model);

	//ter->scale(0.5, 0.5, 0.5);
	ter->translate(0.2, -0.1, (0.01 * pitch) - 0.5);
	ter->rotate(-180 * DEG2RAD, Vector3(0, 1, 0));
	ter->rotate(-pitch * DEG2RAD, Vector3(1, 0, 0));
	weapon->model = ter;

	weapon->render(light);
	
}



void EntityPlayer::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
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


	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 2; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		delta = delta+Vector3(1, 0, 0);
	} 
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) delta = delta + Vector3(-1, 0, 0);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  delta = delta + Vector3(0, 0,-1 );
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
	R1.rotate(particle.angle * DEG2RAD, Vector3(0, 1, 0));
	front1 = R * front;
	particle.vel_x = particle.vel_x + delta.x * front;
	particle.vel_x = particle.vel_x - particle.vel_x * 0.04;

	particle.vel_y = particle.vel_y + delta.z * right;
	particle.vel_y = particle.vel_y - particle.vel_y * 0.04;

	particle.vel_ang += yaw * seconds_elapsed;
	particle.vel_ang = particle.vel_ang - particle.vel_ang * 0.02;
	particle.pos = particle.pos + particle.vel_x * seconds_elapsed;
	particle.pos = particle.pos + particle.vel_y * seconds_elapsed;
	particle.angle = particle.angle + particle.vel_ang;



	//target_pos = testCollision(target_pos, seconds_elapsed, objects);

	target_pos = testCollision(particle.pos, seconds_elapsed, objects);
	//TRS

	//if (!has_collision) 
	particle.pos = target_pos;

	//player.model.setIdentity();

	model->setTranslation(particle.pos.x, particle.pos.y, particle.pos.z);

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

		float distance = objectPositio.distance(particle.pos);
		
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
		target_pos = particle.pos - push_away*((particle.vel_x+particle.vel_y).length() * 1.5);
		target_pos.y = 0;
		break;


	}

	return target_pos;

}