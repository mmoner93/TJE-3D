#ifndef ENTITYSINTEXTURE_H
#define ENTITYSINTEXTURE_H

#include "Entity.h" 

#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "camera.h"
class EntityST :public Entity
{
public:
	Shader* shader = NULL;
	Mesh* mesh = NULL;
	Material* material = NULL;
	float scale=1.0f;
	//Matrix44 modelo;

	EntityST( Shader* s, Mesh* m,float sc, Material* mat) {

		shader = s;
		mesh = m;
		scale = sc;
		material = mat;
	}

	 void render();
	 void renderFlat(float x, float y);
	 void update(float seconds_elapsed);



};


#endif 