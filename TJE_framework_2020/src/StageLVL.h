#ifndef STAGELVL_H
#define STAGELVL_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "enumStructs.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageLVL :public Stage
{
public:

	Texture* select1 = NULL;
	Texture* select2 = NULL;
	Texture* select3 = NULL;
	Texture* select21 = NULL;
	Texture* select22 = NULL;
	Texture* select23 = NULL;
	Texture* select31 = NULL;
	Texture* select32 = NULL;
	Texture* select33 = NULL;

	Texture* uiTexture = NULL;
	int optionSelected = 1;
	int optionSelectedFila = 1;
	StageLVL() :Stage("SelectLVL") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif