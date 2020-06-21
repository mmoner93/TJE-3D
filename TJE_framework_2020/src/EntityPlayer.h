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
	Animation* idle;
	Animation* run ;
	Animation* walk ;
	Skeleton* blendWalkRun ;
	bool loadanim = false;
	bool shooting = false;
	enumWeapons weaponUsing;
	std::map<enumWeapons, EntityGameObject*> weapons;
	bool retrocesoOn = false;
	float retrocesoLeft = 0.0f;

	float health = 10.0;


	float time_next_pegamento_up=0.0f;
	float time_next_pegamento_up_max=5.0f;

	float time_next_shoot_weapon2 = 0.0f;
	float time_next_shoot_weapon2MAX = 0.2f;

	EntityPlayer(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, float sc = 1.0, float til = 1.0, float ya = 0.0, float pi = 0.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		
		yaw = ya;
		pitch = pi;
		weapon = NULL;
		angle = 0.0;
		vel_ang = 0.0;
		position = pos;
		weaponUsing = PEGAMENTO;
	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	void atachWeapon(enumWeapons name,EntityGameObject* wea) {
		if (weapons.size() == 0) {
			weapon = wea;
		}
		weapons[name]=  wea;
	}



	void chargePegamento(float seconds_elapsed);
	void shoot();
	void fixShoot();
	void shootGranade();
	void loalAnim();
	void renderAnimated(Light* light);
	void retrocesoShoot(float seconds_elapsed);
	void radar(); 
	void renderUI(int type, Texture* tex, float opacity, std::vector<Vector3> listaPoints);
	void changeWeapon();
	bool playerAlive();
};


#endif 