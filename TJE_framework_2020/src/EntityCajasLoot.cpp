#include "EntityCajasLoot.h"
#include "Stage.h"
#include "StagePlay.h"

void EntityCajaLoot::render(Light* light) {
	model->setTranslation(position.x, position.y, position.z);
	model->rotate(45 * time_passed * DEG2RAD, Vector3(0, 1, 0));
	model->scale(0.5f, 0.5f, 0.5f);
	EntityGameObject::render(light);

}
void EntityCajaLoot::update(float seconds_elapsed, std::vector<EntityGameObject*> objects) {
	time_passed += seconds_elapsed;
	//Vector3 targe_pos;
	


	testCollision( seconds_elapsed);
	

	
}

Vector3 EntityCajaLoot::testCollision( float seconds_elapsed) {



	StagePlay* temp = (StagePlay*)Stage::getStage("Play");

	
    float distanceToPlayer = temp->gameSceneSP->myPlayer->model->getTranslation().distance(model->getTranslation());

	if (distanceToPlayer < 1.0f) {

		int cual = rand() % 3;

		switch (cual)
		{
		case 0://balas
			//temp->gameSceneSP->myPlayer->mejoras.ammo += 5;
			break;
		case 1://granada
			//temp->gameSceneSP->myPlayer->mejoras.grenades += 1;
			break;
		case 2://vida
			//temp->gameSceneSP->myPlayer->health += 5.0f;
			break;
		default:
			break;
		}

		
		in_use = false;
	}





	return Vector3(0, 0, 0);
}