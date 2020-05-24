#ifndef ENTITYENEMY_H
#define ENTITYENEMY_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
class EntityEnemy :public EntityGameObject
{
public:
	Vector3 position;
	float yaw;
	float pitch;
	//EntityGameObject* weapon;
	Vector3 vel_x;
	Vector3 vel_y;
	float vel_ang;
	float angle;
	float timeTopNextMove = 0.5;
	float timeNextMove = 0.5;
	enumEnemyMove actualDirection= STOP;

	EntityEnemy(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, float sc = 1.0, float til = 1.0, float ya = 0.0, float pi = 0.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {

		yaw = ya;
		pitch = pi;
		//weapon = NULL;
		angle = 0.0;
		vel_ang = 0.0;
		position = pos;
	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 moveEnemy(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool checkTime(float seconds_elapsed);
};


#endif 