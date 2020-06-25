#ifndef STAGEMENUINGAME_H
#define STAGEMENUINGAME_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageMenuInGame :public Stage
{
public:
	Texture* select1 = NULL;
	Texture* select2 = NULL;
	Texture* select3 = NULL;
	Texture* uiTexture = NULL;
	int optionSelected = 1;
	StageMenuInGame() :Stage("MenuInGame") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif