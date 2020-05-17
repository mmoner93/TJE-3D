#ifndef ENTITYLIGHT_H
#define ENTITYLIGHT_H

#include "light.h"
#include "EntityGameObject.h"

class EntityLight
{
public:

	EntityGameObject* gameMesh;
	Light* light;
	

	EntityLight(EntityGameObject* gM,Light* l){
		gameMesh = gM;
		light = l;
	}




};


#endif 