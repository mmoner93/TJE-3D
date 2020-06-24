#include "StagePlay.h"
#include "Stage.h"
#include "StageSaveLoad.h"
#include "Inventario.h"
#include <string.h>

struct sGameInfo {
	Inventario p1;;
};

sGameInfo slot1;
sGameInfo slot2;
sGameInfo slot3;
sGameInfo partidas[3] = { slot1 , slot2 , slot3 };


void StageSaveLoad::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	drawText(20, 20, "Save press S", Vector3(1, 1, 1), 2);
	drawText(20, 50, "Load press L", Vector3(1, 1, 1), 2);

	drawText(40, 100, "Slot1", Vector3(1, 1, 1), 2);
	drawText(40, 120, "Slot2", Vector3(1, 1, 1), 2);
	drawText(40, 140, "Slot3", Vector3(1, 1, 1), 2);

	drawText(160, 100, std::to_string(partidas[0].lastlvl), Vector3(1, 1, 1), 2);
	drawText(160, 120, std::to_string(partidas[1].lastlvl), Vector3(1, 1, 1), 2);
	drawText(160, 140, std::to_string(partidas[2].lastlvl), Vector3(1, 1, 1), 2);

	drawText(20, 300, "M go to Menu", Vector3(1, 1, 1), 2);
	*/



	if (cargado) {
		drawText(20, 20, "Game loaded", Vector3(1, 1, 1), 2);
		drawText(20, 50, "Press E to continue", Vector3(1, 1, 1), 2);
	}
	else if (sobreEscribir) {
		drawText(20, 20, "Want you to override the previous saved game?", Vector3(1, 1, 1), 2);
		drawText(20, 50, "Press Y [yes]     N [no]", Vector3(1, 1, 1), 2);
	}
	else {

		checkPartidas();
		renderUI(0, uiTexture, 1);
		drawText(100, 150, slot1S, Vector3(1, 1, 1), 2);
		drawText(100, 300, slot2S, Vector3(1, 1, 1), 2);
		drawText(100, 450, slot3S, Vector3(1, 1, 1), 2);
	}

	
	SDL_GL_SwapWindow(Game::instance->window);
	//print some state of the saved files
}
void StageSaveLoad::update(double dt) {
	
	if (cargado) {
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.estoyGuardadoEn = optionSelected;
			cargado = false;
		}

	}else if (sobreEscribir) { 
		if (Input::wasKeyPressed(SDL_SCANCODE_N)) {
			sobreEscribir = false;
		}

		if (Input::wasKeyPressed(SDL_SCANCODE_Y)) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.estoyGuardadoEn = optionSelected;
			saveGameInfo(optionSelected);
			sobreEscribir = false;
		}
	
	}
	else {
	
		if (Input::wasKeyPressed(SDL_SCANCODE_N)) {
			if (optionSelected == 1 && slot1S.compare("Empty")==0) {
				((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.estoyGuardadoEn = 1;
				saveGameInfo(optionSelected);
			}else if (optionSelected == 2 && slot2S.compare("Empty") == 0) {
				((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.estoyGuardadoEn = 2;
				saveGameInfo(optionSelected);
			}else if (optionSelected == 3 && slot3S.compare("Empty") == 0) {
				((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.estoyGuardadoEn = 3;
				saveGameInfo(optionSelected);
			}
			else {
				sobreEscribir = true;
			}




		}
		else if (Input::wasKeyPressed(SDL_SCANCODE_L))
		{

			if (loadGameInfo(optionSelected)) {
				cargado = true;
			}
			
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
			optionSelected -= 1;
			if (optionSelected < 1) {
				optionSelected = 3;
			}
		}
		else if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
			optionSelected += 1;
			if (optionSelected > 3) {
				optionSelected = 1;
			}
		}


		if (optionSelected == 1) {
			uiTexture = select1;
		}
		else if (optionSelected == 2) {
			uiTexture = select2;
		}
		else if (optionSelected == 3) {
			uiTexture = select3;
		}
	

		if (Input::wasKeyPressed(SDL_SCANCODE_M))
		{
			Stage::changeState("Menu");
		}
	}



	



}
void StageSaveLoad::init() {

	select1 = Texture::Get("data/UI/saveload/selected1.png");
	select2 = Texture::Get("data/UI/saveload/selected2.png");
	select3 = Texture::Get("data/UI/saveload/selected3.png");
	uiTexture = select1;
	


}


void StageSaveLoad::checkPartidas() {
	FILE* fp;
	for (int i = 1; i < 4; i++) {
	
		switch (i) {
		case 1:
			fp = fopen("savegame1.bin", "rb");
			if (fp == NULL) {
				slot1S = "Empty";
			}
			else {
				slot1S = "Saved";
				fclose(fp);
			}

			break;
		case 2:
			fp = fopen("savegame2.bin", "rb");
			if (fp == NULL) {
				
				slot2S = "Empty";
			}
			else {
				slot2S = "Saved";
				fclose(fp);
			}

			break;
		case 3:
			fp = fopen("savegame3.bin", "rb");
			if (fp == NULL) {
				
				slot3S = "Empty";
			}
			else {
				slot3S = "Saved";
				fclose(fp);
			}

			break;

		}
	}

	
}


void StageSaveLoad::saveGameInfo(int option)
{
	init();
	//fill here game_info with all game data
	//...
	//save to file
	FILE* fp;
	switch (option) {
	case 1:
		 fp = fopen("savegame1.bin", "wb");
		if (fp == NULL) {
			std::cout << "No puedo escribir savegame1" << std::endl;
		}
		else {
			slot1.p1 = ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras;
			fwrite(&slot1, sizeof(sGameInfo), 1, fp);
			fclose(fp);
			break;
		}
		
	case 2:
		 fp = fopen("savegame2.bin", "wb");
		if (fp == NULL) {
			std::cout << "No puedo escribir savegame2" << std::endl;
		}
		else {
			slot2.p1 = ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras;
			fwrite(&slot2, sizeof(sGameInfo), 1, fp);
			fclose(fp);
		}
		
		break;
	case 3:
		 fp = fopen("savegame3.bin", "wb");
		if (fp == NULL) {
			std::cout << "No puedo escribir savegame3" << std::endl;
		}
		else {
			slot3.p1 = ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras;
			fwrite(&slot3, sizeof(sGameInfo), 1, fp);
			fclose(fp);
		}
		
		break;

	}
	

	
}

bool StageSaveLoad::loadGameInfo(int option)
{
	FILE* fp;

	switch (option) {
	case 1:
		 fp = fopen("savegame1.bin", "rb");
		if (fp == NULL) {
			std::cout << "No puedo leer savegame1" << std::endl;
			return false;
		}
		else {
			fread(&slot1, sizeof(sGameInfo), 1, fp);
			fclose(fp);
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras = slot1.p1;
		}
		
		break;
	case 2:
		 fp = fopen("savegame2.bin", "rb");
		if (fp == NULL) {
			std::cout << "No puedo leer savegame2" << std::endl;
			return false;
		}
		else {
			fread(&slot2, sizeof(sGameInfo), 1, fp);
			fclose(fp);
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras = slot2.p1;
		}
		
		break;
	case 3:
		 fp = fopen("savegame3.bin", "rb");
		if (fp == NULL) {
			std::cout << "No puedo leer savegame3" << std::endl;
			return false;
		}
		else {
			fread(&slot3, sizeof(sGameInfo), 1, fp);
			fclose(fp);
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras = slot3.p1;
		}
		
		break;

	}


	return true;
}