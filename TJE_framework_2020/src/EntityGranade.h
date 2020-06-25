#ifndef ENTITYGRANADE_H
#define ENTITYGRANADE_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"


class EntityGranade :public EntityGameObject
{
public:
	Vector3 position;
	float vel;
	float angle;
	bool in_use;
	Vector3 dir;
	Vector3 init_pos;
	float time_passed = 0.0f;
	int id;

	EntityGranade(int ida, Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos,  float sc = 1.0, float til = 1.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		id = ida;
		angle = 0.0;
		vel = 0.1;
		position = pos;
		in_use = false;

	}


	void render(Light* light, Vector3 fog);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	void explosion(Vector3 posT);


};


#endif 