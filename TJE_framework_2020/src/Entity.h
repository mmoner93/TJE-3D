#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:

	Entity() {
		
	}

	virtual void render();
	virtual void update(float seconds_elapsed);



};


#endif 