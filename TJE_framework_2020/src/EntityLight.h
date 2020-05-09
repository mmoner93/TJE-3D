#ifndef ENTITYLIGHT_H
#define ENTITYLIGHT_H

#include "light.h"
#include "EntityMesh.h"

class EntityLight
{
public:

	EntityMesh* gameMesh;
	Light* light;
	

	EntityLight(EntityMesh* gM,Light* l){
		gameMesh = gM;
		light = l;
	}




};


#endif 