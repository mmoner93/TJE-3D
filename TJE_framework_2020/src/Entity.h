#ifndef ENTITY_H
#define ENTITY_H

#include "light.h"

class Entity
{
public:

	Entity() {
		
	}

	virtual void render(Light* light);
	virtual void update(float seconds_elapsed);



};


#endif 