#include "StageMenu.h"


void StageMenu::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press P to Select LVL", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press S to Shop", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press L to Load/Save", Vector3(1, 1, 1), 2);
	if (intro){
		renderUI(0, introTexture);
	}
	else {
		renderUI(0, uiTexture);
	}
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenu::update(double dt) {
	if (intro == false) {
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
		if (Input::wasKeyPressed(SDL_SCANCODE_P)) {
			if (optionSelected == 1) {
				Stage::changeState("SaveLoad");
			}
			else if (optionSelected == 2) {
				Stage::changeState("Shop");
			}
			else if (optionSelected == 3) {
				Stage::changeState("SelectLVL");
			}



			//Stage::current_state->init();
		}
	}
	else
	{
		if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
			intro = false;
		}
	}
	


}
void StageMenu::init() {
	select1 = Texture::Get("data/UI/menu/selected1.png");
	select2 = Texture::Get("data/UI/menu/selected2.png");
	select3 = Texture::Get("data/UI/menu/selected3.png");
	introTexture = Texture::Get("data/UI/intro.png");
	uiTexture = select1;

}