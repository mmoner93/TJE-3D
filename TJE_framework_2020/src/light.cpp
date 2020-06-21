#include "light.h"



Light::Light()
{
	position.set(50, 50, 0);
	diffuse_color.set(0.6f,0.6f,0.6f);
	specular_color.set(0.6f, 0.6f, 0.6f);
}

void Light::uploadToShader(Shader* shader) {
	shader->setUniform3("lightPosition", position);
	shader->setUniform3("lightDiffuse", diffuse_color);
	shader->setUniform3("lightSpecular", specular_color);
}
