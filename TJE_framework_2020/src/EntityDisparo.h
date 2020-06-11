#ifndef ENTITYDISPARO_H
#define ENTITYDISPARO_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
#include "Inventario.h"

class EntityDisparo :public EntityGameObject
{
public:
	Vector3 position;
	float vel;
	float angle;
	enumTipoDisparo tipo = T_NONE;
	bool in_use;
	Vector3 dir;
	Vector3 init_pos;
	EntityDisparo(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, enumTipoDisparo tip, float sc = 1.0, float til = 1.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		tipo = tip;
		angle = 0.0;
		vel = 0.1;
		position = pos;
		in_use = false;

	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	


};


#endif 