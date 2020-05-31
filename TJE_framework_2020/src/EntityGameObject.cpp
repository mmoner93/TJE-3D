#include "EntityGameObject.h"


void EntityGameObject::render(Light* light) {
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
	Vector3 light_direction = light->position - model->getTranslation();
	shader->setUniform("u_light_direction", light_direction);
	shader->setUniform("u_camera_position", camera->eye);
	shader->setFloat("u_tilling", tilling);
	shader->setUniform("u_ambient_light", Vector3(0.2, 0.2, 0.2));
	mesh->render(GL_TRIANGLES, -1);

	shader->disable();
}


void EntityGameObject::renderConPhong( Light* light ) {

	Camera* camera = Camera::current;
	Vector3 ambientLight(0.3, 0.3, 0.3);
	Matrix44 m = *model;

	//enable shader
	shader->enable();
	
	//m.scale(scale, scale, scale);
	shader->setMatrix44("model", m); //upload info to the shader
	shader->setMatrix44("viewprojection", camera->viewprojection_matrix); //upload info to the shader

	shader->setTexture("color_texture", textura, -1); //set texture in slot 0
	//shaderFlat->setTexture("nomal_texture", textureNorrmal, 1); //set texture in slot 1

	shader->setFloat("u_tilling", tilling);
	shader->setUniform3("positionCamera", camera->eye);
	shader->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shader);
	material->uploadToShader(shader);
	mesh->render(GL_TRIANGLES, -1);

	shader->disable();

}

//de momento no he modificado shader para que sea simple
void EntityGameObject::renderTilling() {

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

	shader->setFloat("u_tilling", tilling);
	
	mesh->render(GL_TRIANGLES, -1);

	shader->disable();

}



void EntityGameObject::update(float seconds_elapsed) {

	

}