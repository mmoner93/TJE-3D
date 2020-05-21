#ifndef STAGEPLAY_H
#define STAGEPLAY_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
class StagePlay :public Stage
{
public:


	StagePlay() :Stage("Play") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();
	void addPoint();
	void rellenarEnemys();
	void rellenarEntitys();
	void inicializarScena();


	//son de pruebas que usaremos más adelante.
	void renderPoints(Matrix44 m, Mesh* mesh,int submesh = 0);

};


#endif