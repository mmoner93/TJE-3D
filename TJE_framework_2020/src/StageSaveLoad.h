#ifndef STAGESAVELOAD_H
#define STAGESAVELOAD_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
#include "texture.h"

class StageSaveLoad :public Stage
{
public:

	Texture* select1 = NULL;
	Texture* select2 = NULL;
	Texture* select3 = NULL;
	Texture* uiTexture = NULL;
	int optionSelected = 1;


	std::string slot1S;
	std::string slot2S;
	std::string slot3S;

	bool sobreEscribir = false;
	bool cargado = false;
	StageSaveLoad() :Stage("SaveLoad") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();
	void saveGameInfo(int option);
	bool loadGameInfo(int option);
	void checkPartidas();
};


#endif