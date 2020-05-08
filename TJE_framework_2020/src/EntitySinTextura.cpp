#include "EntitySinTextura.h"



void EntityST::render() {

}

void EntityST::renderFlat(float x, float y) {
	Camera* camera = Camera::current;

	Matrix44 modelo;

	//enable shader
	shader->enable();


	modelo.translate(x * 10, 0, y * 10);
	modelo.scale(scale, scale, scale);
	shader->setMatrix44("u_model", modelo); //upload info to the shader
	shader->setMatrix44("u_viewprojection", camera->viewprojection_matrix); //upload info to the shader
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	
	//shaderFlat->setTexture("nomal_texture", textureNorrmal, 1); //set texture in slot 1


	shader->setUniform3("positionCamera", camera->eye);
	
	mesh->render(GL_TRIANGLES, 0);

	shader->disable();



}



void EntityST::update(float seconds_elapsed) {



}