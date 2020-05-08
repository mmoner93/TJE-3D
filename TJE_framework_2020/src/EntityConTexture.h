#ifndef ENTITYCONTEXTURE_H
#define ENTITYCONTEXTURE_H

#include "Entity.h" 

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "camera.h"
#include "light.h"
class EntityCT :public Entity
{
public:
	Texture* textura=NULL;
	Shader* shader = NULL;
	Mesh* mesh = NULL;
	Material* material = NULL;
	float scale=1.0f;

	EntityCT(Texture* t, Shader* s, Mesh* m,float sc, Material* mat) {
		textura = t;
		shader = s;
		mesh = m;
		scale = sc;
		material = mat;
	}

	  void render();
	 void renderConPhong(float x, float y, Light* light);
	 void update(float seconds_elapsed);



};


#endif 