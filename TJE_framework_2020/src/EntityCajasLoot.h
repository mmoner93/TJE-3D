#ifndef ENTITYCAJASLOOT_H
#define ENTITYCAJASLOOT_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"


class EntityCajaLoot :public EntityGameObject
{
public:
	Vector3 position;
	bool in_use;
	float time_passed = 0.0f;
	EntityCajaLoot( Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, float sc = 1.0, float til = 1.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		position = pos;
		in_use = true;
	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision( float seconds_elapsed);



};


#endif 