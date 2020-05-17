#ifndef ENTITYMESH_H
#define ENTITYMESH_H

#include "Entity.h" 

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "camera.h"
#include "light.h"
class EntityMesh :public Entity
{
public:
	Texture* textura=NULL;
	Shader* shader = NULL;
	Mesh* mesh = NULL;
	Material* material = NULL;
	std::string nameShader;
	
	EntityMesh(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS) {
		textura = t;
		shader = s;
		mesh = m;
		material = mat;
		nameShader=nS;
	}


	 void render();
	 void renderConPhong(Light* light);
	 void update(float seconds_elapsed);



};


#endif 