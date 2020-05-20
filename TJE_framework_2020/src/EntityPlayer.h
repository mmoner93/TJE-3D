#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
class EntityPlayer :public EntityGameObject
{
public:
	Vector3 position;
	float yaw;
	float pitch;
	EntityGameObject* weapon;

	EntityPlayer(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, float sc = 1.0, float til = 1.0, float ya = 0.0, float pi = 0.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		
		/*textura = t;
		shader = s;
		mesh = m;
		material = mat;
		model = new Matrix44();
		model->scale(sc, sc, sc);
		scale = sc;
		tilling = til;
		nameShader = nS;*/
		position = pos;
		yaw = ya;
		pitch = pi;
		weapon = NULL;

	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	void atachWeapon(EntityGameObject* wea) {
		weapon = wea;
	}
	void renderPlayer(Light* light);
};


#endif 