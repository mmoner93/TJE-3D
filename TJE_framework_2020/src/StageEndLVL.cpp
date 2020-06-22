#include "StageEndLVL.h"


void StageEndLVL::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press P to Select LVL", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press S to Shop", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press L to Load/Save", Vector3(1, 1, 1), 2);
	if (dead){
		renderUI(0, gameOver, 1);
	}
	else {
		renderUI(0, uiTexture, 1);
	}
	SDL_GL_SwapWindow(Game::instance->window);
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
		if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
			dead = false;
			Stage::changeState("Menu");
		}
		else if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
			dead = false;
			Stage::changeState("Shop");
		}
		else if (Input::wasKeyPressed(SDL_SCANCODE_R)) {
			dead = false;
			//Stage::changeState("Shop");
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