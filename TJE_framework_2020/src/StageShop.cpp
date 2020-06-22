#include "Stage.h"
#include "StageMenu.h"
#include "StagePlay.h"
#include "StageShop.h"
#include "enumStructs.h"
#include "texture.h"
#include <string>
#include "Scene.h"
#include "EntityPlayer.h"
//#include "Inventario.h"


//invetario
void StageShop::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderUI(0, uiTexture, 1);
	EntityPlayer* tempP = ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer;
	drawText(60, 200, "Actual "+std::to_string((int)(tempP->mejoras.maxHealth))+"/20 coins lvlup", Vector3(1, 1, 1), 1);

	drawText(280, 200, "Balas " + std::to_string((int)(tempP->mejoras.ammoSaved[T_NORMAL])) , Vector3(1, 1, 1), 1);
	
	if (tempP->mejoras.mejora_Mapa) {
		drawText(430, 200, "Mejora radar comprada", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(430,200, "Mejora radar 200 coins", Vector3(1, 1, 1), 1);
	}
	

	drawText(630, 200, "Granadas " + std::to_string((int)(tempP->mejoras.granadeSaved["pegamento"])), Vector3(1, 1, 1), 1);


	drawText(630, 430, "Max pegamento " + std::to_string((int)(tempP->mejoras.maxPegamento)), Vector3(1, 1, 1), 1);

	drawText(90, 430, "Velocidad " + std::to_string((int)(tempP->mejoras.velociti)), Vector3(1, 1, 1), 1);



	drawText(360, 300, "Monedas " + std::to_string((int)(tempP->mejoras.coins)), Vector3(1, 1, 1), 1);

	drawText(250, 570, "Comprada " , Vector3(1, 1, 1), 1);

	if (tempP->mejoras.arma2Comprada) {
		drawText(500, 570, "Comprada ", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(500, 570, "Comprar por 400 ", Vector3(1, 1, 1), 1);
	}
	

	/*drawText(130, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.armaour), Vector3(1, 1, 1), 2);
	drawText(390, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.grenades), Vector3(1, 1, 1), 2);
	drawText(660, 200, std::to_string(((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.selectedWeapon), Vector3(1, 1, 1), 2);
	drawText(130, 420, std::to_string(((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.velociti), Vector3(1, 1, 1), 2);
	drawText(660, 420, std::to_string(((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.stuntTime), Vector3(1, 1, 1), 2);*/

	//drawText(395, 570, std::to_string(weaponOnScreen), Vector3(1, 1, 1), 2);


	//drawText(20, 100, "New Weapon", Vector3(1, 1, 1), 2);
	//hacer un selector de armas que te diga si la tienes comprada seleccionar, sino precio para comprar
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageShop::update(double dt) {
	//if (Input::isKeyPressed(SDL_SCANCODE_P)) {
		//Stage::changeState("Play");
		//Stage::current_state->init();
	//}

	EntityPlayer* tempP = ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer;

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		optionSelected -= 1;
		if (optionSelected < 1) {
			optionSelected = 4;
		}
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_D)) {
		optionSelected += 1;
		if (optionSelected > 4) {
			optionSelected = 1;
		}
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
		optionSelectedFila -= 1;
		if (optionSelectedFila < 1) {
			optionSelectedFila = 2;
		}
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		optionSelectedFila += 1;
		if (optionSelectedFila > 2) {
			optionSelectedFila = 1;
		}
	}


	if (optionSelected == 1) {
		if (optionSelectedFila == 1) {
			uiTexture = select11;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select21;
		}

	}
	else if (optionSelected == 2) {
		if (optionSelectedFila == 1) {
			uiTexture = select12;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select22;
		}
	
	}
	else if (optionSelected == 3) {
		if (optionSelectedFila == 1) {
			uiTexture = select13;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select23;
		}
	}
	else if (optionSelected == 4) {
		if (optionSelectedFila == 1) {
			uiTexture = select14;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select24;
		}

	}

	if (Input::isKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_E)) {

		if (optionSelected == 1) {
			if (optionSelectedFila == 1) {
				tempP->mejoras.coins--;
				tempP->mejoras.maxHealth += 1;
			}
			else if (optionSelectedFila == 2) {
				tempP->mejoras.coins--;
				tempP->mejoras.velociti += 1;
			}

		}
		else if (optionSelected == 2) {
			if (optionSelectedFila == 1) {
				tempP->mejoras.coins--;
				tempP->mejoras.ammoSaved[T_NORMAL] += 1;
			}
			else if (optionSelectedFila == 2) {
				
			}

		}
		else if (optionSelected == 3) {
			if (optionSelectedFila == 1) {
				tempP->mejoras.coins -= 200;
				tempP->mejoras.mejora_Mapa = true;
			}
			else if (optionSelectedFila == 2) {
				tempP->mejoras.coins -= 400;
				tempP->mejoras.arma2Comprada = true;
			}
		}
		else if (optionSelected == 4) {
			if (optionSelectedFila == 1) {
				tempP->mejoras.coins--;
				tempP->mejoras.granadeSaved["pegamento"] += 1;
			}
			else if (optionSelectedFila == 2) {
				tempP->mejoras.coins--;
				tempP->mejoras.maxPegamento += 1;
			}

		}
	}






		/*

	if (Input::isKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
		//Stage::current_state->init();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.velociti += 1;
			//speed ++
			std::cout << ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.velociti << std::endl;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_L)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.armaour += 1;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.armaour << std::endl;
			//Armour ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_T)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.stuntTime += 1;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.stuntTime << std::endl;
			//Stunt Time ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_G)) {
		if (coins > 50) {
		//	((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.grenades += 1;
		//	std::cout << ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.grenades << std::endl;
			//Granadas equipadas ++
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
		if (coins > 50) {
			((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.selectedWeapon = weaponOnScreen;
			std::cout << ((StagePlay*)Stage::getStage("Play"))->Lvls[0]->myPlayer->mejoras.selectedWeapon << std::endl;
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
	*/
}
void StageShop::init() {

	select11 = Texture::Get("data/UI/shop/s11.png");
	select12 = Texture::Get("data/UI/shop/s12.png");
	select13 = Texture::Get("data/UI/shop/s13.png");
	select14 = Texture::Get("data/UI/shop/s14.png");
	select21 = Texture::Get("data/UI/shop/s21.png");
	select22 = Texture::Get("data/UI/shop/s22.png");
	select23 = Texture::Get("data/UI/shop/s23.png");
	select24 = Texture::Get("data/UI/shop/s24.png");
	uiTexture = select11;



	// crear inventario
}
