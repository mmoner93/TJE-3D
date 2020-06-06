#include "EntityTorreArreglo.h"

void EntityTowerArreglo::render(Light* light) {
	EntityGameObject::render(light);

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
		//temp->model = *(temp->model) * normPointsSP[i];
		temp->render(light);

	}

}
void EntityTowerArreglo::update(float seconds_elapsed) {

}
void EntityTowerArreglo::onReceveidShootPegamento(Vector3 temp, Vector3 norm) {
	pointsSPegamento.push_back(temp);
	switchLight();

}

void EntityTowerArreglo::switchLight() {
	switch (estado) {
	case GREEN:break;
	case ORANGE:estado = GREEN;
		EntityGameObject::mesh = meshGreen;
		break;
	case RED:estado = ORANGE;
		EntityGameObject::mesh = meshOrange; break;
	default:break;
	}
}