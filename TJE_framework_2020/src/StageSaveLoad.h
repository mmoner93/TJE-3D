#ifndef STAGESAVELOAD_H
#define STAGESAVELOAD_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageSaveLoad :public Stage
{
public:


	StageSaveLoad() :Stage("SaveLoad") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();
	void saveGameInfo();
	bool loadGameInfo();
};


#endif