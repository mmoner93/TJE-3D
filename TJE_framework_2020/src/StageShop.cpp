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

	int coste = tempP->mejoras.maxHealth - 9.0;
	if (tempP->mejoras.maxHealth < MAX_PLAYER_LIFE_SHOP) {
		drawText(60, 200, "(Actual " + std::to_string((int)(tempP->mejoras.maxHealth)) + "/20) "+ std::to_string(coste*5) +" coins to lvlup", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(60, 200, "MAX", Vector3(1, 1, 1), 1);
	}

	
	if ((int)(tempP->mejoras.ammoSaved[T_NORMAL]) < MAX_PLAYER_BALAS_SHOP) {
		drawText(280, 200, "Balas " + std::to_string((int)(tempP->mejoras.ammoSaved[T_NORMAL])) + " /1 gold", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(280, 200, "MAX ", Vector3(1, 1, 1), 1);
	}
	


	
	if (tempP->mejoras.mejora_Mapa ==2) {
		drawText(430, 200, "Mejora radar comprada", Vector3(1, 1, 1), 1);
	}
	else if (tempP->mejoras.mejora_Mapa == 1) {
		drawText(430, 200, "Mejora radar 400 coins", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(430,200, "Mejora radar 200 coins", Vector3(1, 1, 1), 1);
	}
	
	if (tempP->mejoras.maxPegamento < MAX_PLAYER_GRANADE_SHOP) {
		drawText(630, 200, "Granadas " + std::to_string((int)(tempP->mejoras.granadeSaved["pegamento"])), Vector3(1, 1, 1), 1);
	}
	else {
		drawText(630, 200, "MAX " , Vector3(1, 1, 1), 1);

	}

	


	 coste = tempP->mejoras.maxPegamento - 4.0;
	if (tempP->mejoras.maxPegamento < MAX_PLAYER_PEGAMENTO_SHOP) {
		drawText(630, 430, "(Actual " + std::to_string((int)(tempP->mejoras.maxPegamento))+ "/10) " + std::to_string(coste * 10) + " coins to lvlup", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(630, 430, "MAX" , Vector3(1, 1, 1), 1);
	
	}

	coste = tempP->mejoras.velociti+1;
	if (tempP->mejoras.velociti < MAX_PLAYER_VEL_SHOP) {
		drawText(90, 430, "(Actual " + std::to_string((int)(tempP->mejoras.velociti)) + "/5) " + std::to_string(coste * 10) + " coins to lvlup", Vector3(1, 1, 1), 1);
	}
	else {
		drawText(90, 430, "MAX", Vector3(1, 1, 1), 1);
	}


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
				int coste = tempP->mejoras.maxHealth - 9.0;

				if (tempP->mejoras.coins >= (5*coste) && tempP->mejoras.maxHealth < MAX_PLAYER_LIFE_SHOP) {
					tempP->mejoras.coins -= (5 * coste);
					tempP->mejoras.maxHealth += 1;
				}
				
			}
			else if (optionSelectedFila == 2) {

				int coste = tempP->mejoras.velociti+1;
				if (tempP->mejoras.coins >= (10 * coste) && tempP->mejoras.velociti < MAX_PLAYER_VEL_SHOP) {
					tempP->mejoras.coins -= (10 * coste);
					tempP->mejoras.velociti += 1;
				}

				
			}

		}
		else if (optionSelected == 2) {
			if (optionSelectedFila == 1) {
				if (tempP->mejoras.coins >= 1 && tempP->mejoras.ammoSaved[T_NORMAL] < MAX_PLAYER_BALAS_SHOP) {
					tempP->mejoras.coins--;
					tempP->mejoras.ammoSaved[T_NORMAL] += 1;
				}
				
			}
			else if (optionSelectedFila == 2) {
				
			}

		}
		else if (optionSelected == 3) {
			if (optionSelectedFila == 1) {

				if (tempP->mejoras.mejora_Mapa == 0 && tempP->mejoras.coins >= 200) {
					tempP->mejoras.coins -= 200;
					tempP->mejoras.mejora_Mapa = 1;
				}else if (tempP->mejoras.mejora_Mapa == 1 && tempP->mejoras.coins >= 400) {
					tempP->mejoras.coins -= 400;
					tempP->mejoras.mejora_Mapa = 2;
				}

				
			}
			else if (optionSelectedFila == 2) {
				if (tempP->mejoras.coins >= 400 && tempP->mejoras.arma2Comprada == false) {
					tempP->mejoras.coins -= 400;
					tempP->mejoras.arma2Comprada = true;
				}
			}
		}
		else if (optionSelected == 4) {
			if (optionSelectedFila == 1) {
				
				if (tempP->mejoras.coins >= 5 && tempP->mejoras.granadeSaved["pegamento"] < MAX_PLAYER_GRANADE_SHOP) {
					tempP->mejoras.coins -= 5;
					tempP->mejoras.granadeSaved["pegamento"] += 1;
				}
				
			}
			else if (optionSelectedFila == 2) {
				int coste = tempP->mejoras.maxPegamento - 4;

				if (tempP->mejoras.coins >= (10 * coste) && tempP->mejoras.maxPegamento < MAX_PLAYER_PEGAMENTO_SHOP) {
					tempP->mejoras.coins -= (10 * coste);
					tempP->mejoras.maxPegamento += 1;
				}
			}

		}
	}





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
