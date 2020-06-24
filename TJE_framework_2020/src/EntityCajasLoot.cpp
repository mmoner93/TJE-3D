#include "EntityCajasLoot.h"
#include "Stage.h"
#include "StagePlay.h"

void EntityCajaLoot::render(Light* light,Vector3 fog) {
	model->setTranslation(position.x, position.y, position.z);
	model->rotate(45 * time_passed * DEG2RAD, Vector3(0, 1, 0));
	model->scale(0.5f, 0.5f, 0.5f);
	EntityGameObject::render(light,fog);

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
		int cual;
		if (temp->gameSceneSP->myPlayer->health < 3.0f) {
			cual = rand() % 5;
			if (cual > 2) {
				cual = 2;
			}
		}
		else  {
			cual = rand() % 3;
			if (cual == 2) {
				cual = 0;
			}
		}

		 

		switch (cual)
		{
		case 0://balas
			temp->gameSceneSP->myPlayer->mejoras.ammoSaved[T_NORMAL] += 5;
			break;
		case 1://granada
			temp->gameSceneSP->myPlayer->mejoras.granadeSaved["pegamento"] += 1;
			break;
		case 2://vida
			temp->gameSceneSP->myPlayer->health += 5.0f;
			if (temp->gameSceneSP->myPlayer->health > temp->gameSceneSP->myPlayer->mejoras.maxHealth) {
				temp->gameSceneSP->myPlayer->health = temp->gameSceneSP->myPlayer->mejoras.maxHealth;
			}
			break;
		default:
			break;
		}

		Game::instance->samplesAudio["cofre"]->PlaySoundAmbient();
		in_use = false;
	}





	return Vector3(0, 0, 0);
}