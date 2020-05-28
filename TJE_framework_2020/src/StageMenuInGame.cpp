#include "StageMenuInGame.h"


void StageMenuInGame::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press P to return to Play", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press R to Restart lvl", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press M to exit to the main menu", Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenuInGame::update(double dt) {
	if (Input::wasKeyPressed(SDL_SCANCODE_P)) {
		Stage::changeState("Play");
		//Stage::current_state->init();
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_R)) {
		//Restart lvl
		//Stage::current_state->init();
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
		//Stage::current_state->init();
	}


}
void StageMenuInGame::init() {


}