#include "Stage.h"
#include "StageMenu.h"
#include "StagePlay.h"
#include "StageShop.h"
//include invetario h

int coins = 1000;
//invetario
void StageShop::render() {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);

	drawText(20, 20,  "S to + Speed", Vector3(1, 1, 1), 2);
	drawText(20, 40,  "L to + Live", Vector3(1, 1, 1), 2);
	drawText(20, 60,  "S to + Stunt Time", Vector3(1, 1, 1), 2);
	drawText(20, 80,  "G to + Grenades", Vector3(1, 1, 1), 2);
	//drawText(20, 100, "New Weapon", Vector3(1, 1, 1), 2);
	//hacer un selector de armas que te diga si la tienes comprada seleccionar, sino precio para comprar
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageShop::update(double dt) {
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		Stage::changeState("Play");
		//Stage::current_state->init();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.velociti += 1;
			//speed ++
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.velociti << std::endl;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_L)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.armaour += 1;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.armaour << std::endl;
			//Armour ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_T)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.stuntTime += 1;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.stuntTime << std::endl;
			//Stunt Time ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_G)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.grenades += 1;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.grenades << std::endl;
			//Granadas equipadas ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.selectedWeapon = 2;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.selectedWeapon << std::endl;
			//new weapon ++
		}
	}

}
void StageShop::init() {
	
	// crear inventario
}