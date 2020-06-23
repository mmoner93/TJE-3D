#include "StageEndLVL.h"
#include "StagePlay.h"
#include "Scene.h"
void StageEndLVL::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press E to Select LVL", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press S to Shop", Vector3(1, 1, 1), 2);
	//drawText(20, 60, "Press L to Load/Save", Vector3(1, 1, 1), 2);

	


	if (dead){
		renderUI(0, gameOver, 1);
	}
	else {
		
		renderUI(0, uiTexture, 1);
		drawText(420, 330, std::to_string(puntuacion ), Vector3(1, 1, 1), 2);
		drawText(420, 400, std::to_string(tiempoPartida), Vector3(1, 1, 1), 2);
		drawText(420,480, std::to_string((int)(puntuacion / 100)), Vector3(1, 1, 1), 2);
	}
	SDL_GL_SwapWindow(Game::instance->window);
}


void StageEndLVL::restart() {
	Scene* temp = ((StagePlay*)Stage::getStage("Play"))->gameSceneSP;
	int EnemigosBien = 0;
	int EnemigosMal = 0;
	int numEstrellas=0;

	puntuacion = 0;

	puntuacion+= temp->towersLeft()*1000;




	for (int i = 0; i < temp->Enemys.size();i++) {
	
		if (temp->Enemys[i]->aLive && temp->Enemys[i]->is_node && temp->Enemys[i]->actualState == E_REPAIR) {
			EnemigosBien+=500;
		}


		if (!temp->Enemys[i]->aLive && temp->Enemys[i]->is_node) {
		
			EnemigosMal -= 1000;
		}
	

		if (!temp->Enemys[i]->aLive && !temp->Enemys[i]->is_node) {

			EnemigosMal -= 200;
		}

	}


	if ((EnemigosBien/500) == temp->numEnemysNode && temp->towersLeft()==temp->numTowers) {
		
		uiTexture = three;
		numEstrellas = 3;
	
	}
	else if ((EnemigosBien / 500) < temp->numEnemysNode && temp->towersLeft() == temp->numTowers) {
	
		uiTexture = two;
		numEstrellas = 2;
	}
	else {
		uiTexture = one;
		numEstrellas = 1;
	}


	puntuacion += EnemigosBien+EnemigosMal;


	if (puntuacion >= 100) {
		temp->myPlayer->mejoras.coins += puntuacion / 100;
	}


	switch (temp->numLvl) {
	case 0:
		if (temp->myPlayer->mejoras.bestPuntuacion0 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion0 = numEstrellas;
		}
		break;
	case 1:
		if (temp->myPlayer->mejoras.bestPuntuacion1 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion1 = numEstrellas;
		}
		break;
	case 2:
		if (temp->myPlayer->mejoras.bestPuntuacion2 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion2 = numEstrellas;
		}
		break;
	case 3:
		if (temp->myPlayer->mejoras.bestPuntuacion3 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion3 = numEstrellas;
		}
		break;
	case 4:
		if (temp->myPlayer->mejoras.bestPuntuacion4 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion4 = numEstrellas;
		}
		break;
	case 5:
		if (temp->myPlayer->mejoras.bestPuntuacion5 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion5 = numEstrellas;
		}
		break;
	case 6:
		if (temp->myPlayer->mejoras.bestPuntuacion6 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion6 = numEstrellas;
		}
		break;
	case 7:
		if (temp->myPlayer->mejoras.bestPuntuacion7 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion7 = numEstrellas;
		}
		break;
	case 8:
		if (temp->myPlayer->mejoras.bestPuntuacion8 < numEstrellas) {
			temp->myPlayer->mejoras.bestPuntuacion8 = numEstrellas;
		}
		break;
	default:break;
	}

	


}

void StageEndLVL::update(double dt) {





	if (dead == false) {
		
		
		if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
			Stage::changeState("Menu");
		}
		if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
			Stage::changeState("Shop");
		}
	}
	else
	{
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			dead = false;
		}
	}
	


}
void StageEndLVL::init() {
	one = Texture::Get("data/UI/endLVL/puntuationone.png");
	two = Texture::Get("data/UI/endLVL/puntuationtwo.png");
	three = Texture::Get("data/UI/endLVL/puntuationthree.png");
	gameOver = Texture::Get("data/UI/endLVL/gameover.png");
	uiTexture = three;

}