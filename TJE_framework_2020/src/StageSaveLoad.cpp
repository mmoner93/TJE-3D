#include "StageSaveLoad.h"
#include <string.h>

struct sGameInfo {
	int lastlvl = 1;
	int num_weapons;
	float time_played;
	// time last saved? mirar fecha modificacion arxivo ? guardar fecha en partidas guardadas!
};

sGameInfo slot1;
sGameInfo slot2;
sGameInfo slot3;
sGameInfo partidas[3] = { slot1 , slot2 , slot3};


void StageSaveLoad::render() {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawText(20, 20, "Save press S", Vector3(1, 1, 1), 2);
	drawText(20, 50, "Load press L", Vector3(1, 1, 1), 2);

	drawText(40, 100, "Slot1", Vector3(1, 1, 1), 2);
	drawText(40, 120, "Slot2", Vector3(1, 1, 1), 2);
	drawText(40, 140, "Slot3", Vector3(1, 1, 1), 2);

	drawText(160, 100, std::to_string(partidas[0].lastlvl), Vector3(1, 1, 1), 2);
	drawText(160, 120, std::to_string(partidas[1].lastlvl), Vector3(1, 1, 1), 2);
	drawText(160, 140, std::to_string(partidas[2].lastlvl), Vector3(1, 1, 1), 2);


	SDL_GL_SwapWindow(Game::instance->window);
	//print some state of the saved files
}
void StageSaveLoad::update(double dt) {
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		saveGameInfo();
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_L))
	{
		loadGameInfo();
		//load game
		//namefile+"sslot"+.file

	}

}
void StageSaveLoad::init() {
	partidas[0].lastlvl = 12;
	partidas[1].lastlvl = 55;
	partidas[2].lastlvl = 32;

}

void StageSaveLoad::saveGameInfo()
{
	init();
	//fill here game_info with all game data
	//...
	//save to file
	FILE* fp = fopen("savegame.bin", "wb");
	fwrite(&slot1, sizeof(sGameInfo), 1, fp);
	fwrite(&slot2, sizeof(sGameInfo), 1, fp);
	fwrite(&slot3, sizeof(sGameInfo), 1, fp);

	fclose(fp);
}

bool StageSaveLoad::loadGameInfo()
{

	//load file
	FILE* fp = fopen("savegame.bin", "rb");
	if (fp == NULL) //no savegame found
		return false;

	fread(&slot1, sizeof(sGameInfo), 1, fp);
	fread(&slot2, sizeof(sGameInfo), 1, fp);
	fread(&slot3, sizeof(sGameInfo), 1, fp);
	fclose(fp);
	//transfer data from game_info to Game
//…

	return true;
}

