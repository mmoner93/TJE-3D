#include "material.h"



Material::Material()
{
	ambient.set(1,1,1); //reflected ambient light
	diffuse.set(1, 1, 1); //reflected diffuse light
	specular.set(1, 1, 1); //reflected specular light
	shininess = 30.0; //glosiness coefficient (plasticity)
}

void Material::uploadToShader(Shader* shader) {
	shader->setUniform3("matAmbient", ambient);
	shader->setUniform3("matDiffuse", diffuse);
	shader->setUniform3("matSpecular", specular);
	shader->setFloat("matShininess", shininess);
}
