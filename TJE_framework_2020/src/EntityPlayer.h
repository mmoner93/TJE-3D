#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
#include "Inventario.h"
#include "animation.h"
class EntityPlayer :public EntityGameObject
{
public:
	Vector3 position;
	float yaw;
	float pitch;
	EntityGameObject* weapon;
	Vector3 vel_x;
	Vector3 vel_y;
	float vel_ang;
	float angle;
	Inventario mejoras;
	Animation* dancing;
	Animation* run ;
	Animation* walk ;
	Skeleton* blendWalkRun ;
	bool loadanim = false;
	bool shooting = false;
	EntityPlayer(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, float sc = 1.0, float til = 1.0, float ya = 0.0, float pi = 0.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		
		yaw = ya;
		pitch = pi;
		weapon = NULL;
		angle = 0.0;
		vel_ang = 0.0;
		position = pos;
	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	void atachWeapon(EntityGameObject* wea) {
		weapon = wea;
	}
	void shoot();
	void fixShoot();
	void loalAnim();
	void renderAnimated(Light* light);




};


#endif 