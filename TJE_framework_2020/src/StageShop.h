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


	StageShop() :Stage("Shop") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif