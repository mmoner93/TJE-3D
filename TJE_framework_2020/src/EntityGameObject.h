#ifndef ENTITYGAMEOBJECT_H
#define ENTITYGAMEOBJECT_H

#include "EntityMesh.h" 

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "camera.h"
#include "light.h"
class EntityGameObject :public EntityMesh
{
public:
	Texture* textura=NULL;
	Shader* shader = NULL;
	Mesh* mesh = NULL;
	Material* material = NULL;
	Matrix44* model = NULL;
	std::string nameShader;
	float scale;
	float tilling;
	EntityGameObject(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS,float sc=1.0,float til=1.0):EntityMesh(t,s,m,mat,nS) {
		textura = t;
		shader = s;
		mesh = m;
		material = mat;
		model = new Matrix44();
		model->scale(sc, sc, sc);
		scale = sc;
		tilling = til;
		nameShader = nS;
	}


	 void render(Light* light);
	 void renderConPhong( Light* light);
	 void renderTilling();
	 void update(float seconds_elapsed);



};


#endif 