#include "Stage.h"
#include "StageMenu.h"
#include "StagePlay.h"
#include "StageShop.h"
//include invetario h

int coins = 1000;
//invetario
void StageShop::render() {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);

	drawText(20, 20,  "+ Speed", Vector3(1, 1, 1), 2);
	drawText(20, 40,  "+ Armour", Vector3(1, 1, 1), 2);
	drawText(20, 60,  "+ Stunt Time", Vector3(1, 1, 1), 2);
	drawText(20, 80,  "+ Grenades", Vector3(1, 1, 1), 2);
	drawText(20, 100, "New Weapon", Vector3(1, 1, 1), 2);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageShop::update(double dt) {
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		Stage::changeState("Play");
		//Stage::current_state->init();
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		if (coins > 50) {
			//((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer.invetario. ;
			//speed ++
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		if (coins > 50) {
			//Armour ++
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_T)) {
		if (coins > 50) {
			//Stunt Time ++
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_G)) {
		if (coins > 50) {
			//Granadas equipadas ++
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_W)) {
		if (coins > 50) {
			//new weapon ++
		}
	}

}
void StageShop::init() {
	
	// crear inventario
}