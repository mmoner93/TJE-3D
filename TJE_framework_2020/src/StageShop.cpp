#include "Stage.h"
#include "StageMenu.h"
#include "StagePlay.h"
#include "StageShop.h"
#include "enumStructs.h"
#include "texture.h"
#include <string>
//include invetario h

int coins = 1000;
int weaponOnScreen = 0;
int weapons[8] = { WEAPON1, WEAPON2, WEAPON3, WEAPON4, WEAPON5, WEAPON6, WEAPON7, WEAPON8 };
Texture* uiTexture = NULL;
//invetario
void StageShop::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderUI(0, uiTexture);
	drawText(130, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.armaour), Vector3(1, 1, 1), 2);
	drawText(390, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.grenades), Vector3(1, 1, 1), 2);
	drawText(660, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.selectedWeapon), Vector3(1, 1, 1), 2);
	drawText(130, 420, std::to_string(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.velociti), Vector3(1, 1, 1), 2);
	drawText(660, 420, std::to_string(((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.stuntTime), Vector3(1, 1, 1), 2);

	drawText(395, 570, std::to_string(weaponOnScreen), Vector3(1, 1, 1), 2);
	

	//drawText(20, 100, "New Weapon", Vector3(1, 1, 1), 2);
	//hacer un selector de armas que te diga si la tienes comprada seleccionar, sino precio para comprar
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageShop::update(double dt) {
	//if (Input::isKeyPressed(SDL_SCANCODE_P)) {
		//Stage::changeState("Play");
		//Stage::current_state->init();
	//}
	if (Input::isKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
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
	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.selectedWeapon = weaponOnScreen;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->gameSceneSP->myPlayer->mejoras.selectedWeapon << std::endl;
			//new weapon ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		weaponOnScreen -= 1;
		if (weaponOnScreen < 0) {
			weaponOnScreen = 8;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_D)) {
		weaponOnScreen += 1;
		if (weaponOnScreen > 8) {
			weaponOnScreen = 0;
		}
	}

}
void StageShop::init() {
	uiTexture = Texture::Get("data/UI/shop.png");
	// crear inventario
}