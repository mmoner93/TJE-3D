#include "EntityTorreArreglo.h"

void EntityTowerArreglo::render(Light* light, Vector3 fog) {
	EntityGameObject::render(light,fog);

	//para disparos Pegamento
	for (int i = 0; i < pointsSPegamento.size(); i++) {

		EntityGameObject* temp = new EntityGameObject(disparoPegamentoTexture, shader, disparoMeshPegamento, NULL, "Game", 1.0f);
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
		temp->model->rotate(time_Shooted*90*DEG2RAD,Vector3(1,0,1));
		temp->model->scale(time_Shooted, time_Shooted, time_Shooted);
		//temp->model = *(temp->model) * normPointsSP[i];
		temp->render(light,fog);

	}

}

void EntityTowerArreglo::changeTime(float seconds_elapsed) {
	if (shooted) {
		time_Shooted -= seconds_elapsed;
		if (time_Shooted <= 0.f) {
			shooted = false;
			time_Shooted = 3.0f;
			pointsSPegamento.pop_back();
			switchLight();
		}
	}
}

void EntityTowerArreglo::update(float seconds_elapsed) {
	changeTime(seconds_elapsed);
}
void EntityTowerArreglo::onReceveidShootPegamento(Vector3 temp, Vector3 norm) {
	if (!shooted) {
		pointsSPegamento.push_back(temp);
		
		shooted = true;
	}
	
}

void EntityTowerArreglo::switchLight() {
	switch (estado) {
	case GREEN:break;
	case ORANGE:estado = GREEN;
		//EntityGameObject::mesh = meshGreen;
		EntityGameObject::textura = textureGreen;
		break;
	case RED:estado = ORANGE;
		//EntityGameObject::mesh = meshOrange;
		EntityGameObject::textura = textureOrange; break;
	default:break;
	}
}

void EntityTowerArreglo::breakTower() {

	estado = RED;
	EntityGameObject::textura = textureRed;
}
