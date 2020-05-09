#ifndef ENTITYGAMEOBJECT_H
#define ENTITYGAMEOBJECT_H

#include "Entity.h" 

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "camera.h"
#include "light.h"
class EntityGameObject :public Entity
{
public:
	Texture* textura=NULL;
	Shader* shader = NULL;
	Mesh* mesh = NULL;
	Material* material = NULL;
	Matrix44* model = NULL;
	float scale;
	EntityGameObject(Texture* t, Shader* s, Mesh* m, Material* mat,float sc=1.0) {
		textura = t;
		shader = s;
		mesh = m;
		material = mat;
		model = new Matrix44();
		scale = sc;
	}


	 virtual void render();
	 void renderConPhong(float x, float y, Light* light);
	 void update(float seconds_elapsed);



};


#endif 