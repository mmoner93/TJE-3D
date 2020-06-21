#ifndef STAGEEDITOR_H
#define STAGEEDITOR_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageEditor :public Stage
{
public:


	//some globals
	Shader* shaderBasic = NULL;
	Shader* shaderFlat = NULL;
	Shader* shaderPhong = NULL;
	Shader* shaderGame = NULL;
	//Animation* anim = NULL;

	Camera* camera;
	Game* gameI = NULL;
	Material* material = NULL;

	std::vector<Entity*> mapaObjects;//guardo la info de que dibujar segun type
	std::map<std::string, Entity*> enemysMap;//guardo la info de como dibujarlo
	Scene* gameScene = NULL;


	StageEditor() :Stage("Editor") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	 void init();


};


#endif