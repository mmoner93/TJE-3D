#ifndef STAGEPLAY_H
#define STAGEPLAY_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
class StagePlay :public Stage
{
public:

	StagePlay() :Stage("Play") {
		iniciado = true;
	};

	virtual void render();
	virtual void update(double dt);
	virtual void init();
};


#endif