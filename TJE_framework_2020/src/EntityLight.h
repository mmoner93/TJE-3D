#ifndef ENTITYLIGHT_H
#define ENTITYLIGHT_H

#include "light.h"
#include "EntityGameObject.h"

class EntityLight:public EntityGameObject
{
public:

	Light* light;
	

	EntityLight(Light* l,Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, float sc = 1.0, float til = 1.0):EntityGameObject(t, s, m, mat, nS, sc, til){
		light = l;
		model->translateGlobal(light->position.x, light->position.y, light->position.z);
	}


	void moveLight(Vector3 position) {
		light->position = position;
		model->translateGlobal(position.x, position.y, position.z);
	}


};


#endif 