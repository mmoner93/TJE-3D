#include "EntityGranade.h"
#include "Stage.h"
#include "StagePlay.h"

void EntityGranade::render(Light* light, Vector3 fog) {

	EntityGameObject::render(light,fog);

}
void EntityGranade::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
	time_passed += seconds_elapsed;
	Vector3 targe_pos;

		targe_pos = position + Vector3(dir.x, dir.y, dir.z) * seconds_elapsed * 15.0;
		targe_pos = targe_pos - Vector3(0, 1, 0) * time_passed * seconds_elapsed * 14.0;

	

	//Vector3 directorGravity = Vector3(model->getTranslation().x,-9999, model->getTranslation().z)-targe_pos;
	//directorGravity.normalize();

	targe_pos = testCollision(targe_pos, seconds_elapsed, objects);
	model->setTranslation(targe_pos.x, targe_pos.y, targe_pos.z);
	model->setFrontAndOrthonormalize(dir);

	//si toca suelo
	if (targe_pos.y <= 0.0f) {
		targe_pos.y = 0.0f;
		explosion(targe_pos);


		in_use = false;
	}
	position = targe_pos;
}

void EntityGranade::explosion(Vector3 posT) {


	for (int i = 0; i < 75; i++) {
		float x = (((random() - 0.0f) * (1.0f - (-1.0f))) / (1.0f - 0.0f)) + (-1.0f);
		float y = (((random() - 0.0f) * (1.0f - (-1.0f))) / (1.0f - 0.0f)) + (-1.0f);
		float z = (((random() - 0.0f) * (1.0f - (-1.0f)))/ (1.0f - 0.0f)) + (-1.0f);
		
		if (y < 0.0) {
			y = y * (-1);
		}

		//x = x * 0.5f;
		//y = y * 0.5f;
		//z = z * 0.5f;
		Vector3 dir = Vector3(x, y, z).normalize();
		dir.x = dir.x * 0.4f;
		dir.y = dir.y * 0.8f;
		dir.z = dir.z * 0.4f;
		//dir.normalize();
		((StagePlay*)Stage::getStage("Play"))->gameSceneSP->activateDisparoPegamento(posT, dir);

	
	
	}



}


Vector3 EntityGranade::testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects) {

	Vector3 character_center = target_pos + Vector3(0, 0.65, 0);
	bool has_collision = false;
	float distanceMin = 50.0f;
	Vector3 collMin;

	StagePlay* temp = (StagePlay*)Stage::getStage("Play");

	for (int i = 0; i < temp->gameSceneSP->Enemys.size(); i++) {


		if (temp->gameSceneSP->Enemys[i]->aLive) {
			EntityEnemy* en = temp->gameSceneSP->Enemys[i];

			Mesh* mesh = en->mesh;

			//para cada objecto de la escena...

			Vector3 collnorm;
			Vector3 coll;
			Vector3 objectPositio = en->model->getTranslation();

			float distance = objectPositio.distance(position);

			if (distance > 10) {
				continue;
			}

			//comprobamos si colisiona el objeto con la esfera (radio 3)
			if (mesh->testSphereCollision(*(en->model), target_pos, 0.05, coll, collnorm, true) == false) {
				continue; //si no colisiona, pasamos al siguiente objeto
			}




			std::cout << "Soy pos enemy x " << en->model->getTranslation().x << " y " << en->model->getTranslation().y << "z " << en->model->getTranslation().z << std::endl;


			has_collision = true;

			distanceMin = distance;
			collMin = coll;
			Matrix44 inv = *en->model;
			//inv.inverse();
			//collMin = inv * collMin
			explosion(target_pos);

			in_use = false;
			break;


			std::cout << "He colisionao" << std::endl;
			//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
			//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
			//target_pos.y = 0;
		}

	}



	for (int i = 0; i < temp->gameSceneSP->TowersList.size() ; i++) {



		EntityTowerArreglo* en = temp->gameSceneSP->TowersList[i];

		Mesh* mesh = en->mesh;

		//para cada objecto de la escena...

		Vector3 collnorm;
		Vector3 coll;
		Vector3 objectPositio = en->model->getTranslation();

		float distance = objectPositio.distance(position);

		if (distance > 10) {
			continue;
		}

		//comprobamos si colisiona el objeto con la esfera (radio 3)
		if (mesh->testSphereCollision(*(en->model), target_pos, 0.05, coll, collnorm, true) == false) {
			continue; //si no colisiona, pasamos al siguiente objeto
		}




		std::cout << "Soy pos enemy x " << en->model->getTranslation().x << " y " << en->model->getTranslation().y << "z " << en->model->getTranslation().z << std::endl;


		has_collision = true;

		distanceMin = distance;
		collMin = coll;
		Matrix44 inv = *en->model;
		//inv.inverse();
		//collMin = inv * collMin;
		explosion(target_pos);
		in_use = false;
		break;


		std::cout << "He colisionao" << std::endl;
		//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
		//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
		//target_pos.y = 0;


	}







	for (int i = 0; i < objects.size() && has_collision == false; i++)
	{

		EntityGameObject* en = objects[i];

		Mesh* mesh = en->mesh;

		//para cada objecto de la escena...

		Vector3 collnorm;
		Vector3 coll;
		Vector3 objectPositio = en->model->getTranslation();

		float distance = objectPositio.distance(position);

		if (distance > 10) {
			continue;
		}

		//comprobamos si colisiona el objeto con la esfera (radio 3)
		if (mesh->testSphereCollision(*(en->model), target_pos, 0.05, coll, collnorm) == false) {
			continue; //si no colisiona, pasamos al siguiente objeto
		}
		/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
			continue;*/
		has_collision = true;

		distanceMin = distance;
		collMin = coll;
		explosion(target_pos);

		in_use = false;
		break;

		std::cout << "He colisionao" << std::endl;
		//Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
		//target_pos = position - push_away * ((vel_x + vel_y).length() * 1.5);
		//target_pos.y = 0;





	}




	return target_pos;
}