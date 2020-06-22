#include "StageMenuInGame.h"
#include "StagePlay.h"

void StageMenuInGame::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderUI(0, uiTexture, 1);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenuInGame::update(double dt) {

	
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
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			if (optionSelected == 1) {
				((StagePlay*)Stage::getStage("Play"))->gameSceneSP->restartLvl(((StagePlay*)Stage::getStage("Play"))->enemysMapSP);
				Stage::changeState("Play");
			}
			else if (optionSelected == 2) {
				Stage::changeState("Menu");
			}
			else if (optionSelected == 3) {
				Stage::changeState("Play");
			}



			//Stage::current_state->init();
		}
	




}
void StageMenuInGame::init() {

	select1 = Texture::Get("data/UI/MenuInGame/selected_1.png");
	select2 = Texture::Get("data/UI/MenuInGame/selected_2.png");
	select3 = Texture::Get("data/UI/MenuInGame/selected_3.png");
	uiTexture = select1;
}