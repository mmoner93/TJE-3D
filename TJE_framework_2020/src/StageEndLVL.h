#ifndef STAGEENDLVL_H
#define STAGEENDLVL_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
#include "texture.h"

class StageEndLVL :public Stage
{
public:

	Texture* one = NULL;
	Texture* two = NULL;
	Texture* three = NULL;
	Texture* gameOver = NULL;
	Texture* uiTexture = NULL;

	int optionSelected = 3;
	bool dead = false;

	StageEndLVL() :Stage("EndLVL") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif