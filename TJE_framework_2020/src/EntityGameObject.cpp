#include "EntityGameObject.h"


void EntityGameObject::render() {

}


void EntityGameObject::renderConPhong(float x, float y , Light* light ) {

	Camera* camera = Camera::current;
	Vector3 ambientLight(0.3, 0.3, 0.3);
	Matrix44 m;

	//enable shader
	shader->enable();


	m.translate(x * 10, 0, y * 10);
	m.scale(scale, scale, scale);
	shader->setMatrix44("model", m); //upload info to the shader
	shader->setMatrix44("viewprojection", camera->viewprojection_matrix); //upload info to the shader

	shader->setTexture("color_texture", textura); //set texture in slot 0
	//shaderFlat->setTexture("nomal_texture", textureNorrmal, 1); //set texture in slot 1


	shader->setUniform3("positionCamera", camera->eye);
	shader->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shader);
	material->uploadToShader(shader);
	mesh->render(GL_TRIANGLES, 0);

	shader->disable();

}



void EntityGameObject::update(float seconds_elapsed) {



}