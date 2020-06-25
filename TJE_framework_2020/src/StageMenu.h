#ifndef STAGEMENU_H
#define STAGEMENU_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
#include "texture.h"

class StageMenu :public Stage
{
public:

	Texture* select1 = NULL;
	Texture* select2 = NULL;
	Texture* select3 = NULL;
	Texture* select4 = NULL;
	Texture* select5 = NULL;
	Texture* uiTexture = NULL;
	Texture* introTexture = NULL;

	Texture* tutorial1 = NULL;
	Texture* tutorial2 = NULL;
	Texture* tutorial3 = NULL;
	Texture* controles = NULL;
	Camera* cameraSP;
	int optionSelected = 1;
	int cual = 0;

	int queMapa=1;
	bool mapaChose = false;
	StageMenu() :Stage("Menu") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();
	void elegirMapa();


};


#endif