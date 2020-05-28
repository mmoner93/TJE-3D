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


	StageLVL() :Stage("SelectLVL") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif