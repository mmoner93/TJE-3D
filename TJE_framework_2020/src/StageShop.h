#ifndef STAGEMENU_H
#define STAGEMENU_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageMenu :public Stage
{
public:


	StageMenu() :Stage("Menu") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif