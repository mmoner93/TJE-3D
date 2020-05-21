#ifndef STAGEEDITOR_H
#define STAGEEDITOR_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
class StageEditor :public Stage
{
public:
	
	StageEditor() :Stage("Editor") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	 void init();

	void rellenarEnemys();
	void rellenarEntitys();
	void inicializarScena();


};


#endif