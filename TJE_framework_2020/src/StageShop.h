#ifndef STAGESHOP_H
#define STAGESHOP_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
#include "enumStructs.h"
class StageShop :public Stage
{
public:

	Texture* select11 = NULL;
	Texture* select12 = NULL;
	Texture* select13 = NULL;
	Texture* select14 = NULL;
	Texture* select21 = NULL;
	Texture* select22 = NULL;
	Texture* select23 = NULL;
	Texture* select24 = NULL;
	Texture* uiTexture = NULL;

	int optionSelectedFila = 1;
	int optionSelected = 1;
	StageShop() :Stage("Shop") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif