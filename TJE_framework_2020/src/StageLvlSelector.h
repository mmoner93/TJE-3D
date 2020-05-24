#ifndef STAGELVLSELECTOR_H
#define STAGELVLSELECTOR_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"
class StageLvlSelector:public Stage
{
public:
	//aqui deberemos tener una lista de lvl. Por ende seguramente necesitaremos clase de lvls , para inicializar las escenas
	//con ciertos datos.


	//funciones necesarias
	/*
		-Restart lvl
		-Change lvl
		-init lvl
	
	*/

	StageLvlSelector() :Stage("LvlSelector") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();


};


#endif