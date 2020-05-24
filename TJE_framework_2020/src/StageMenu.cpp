#include "StageMenu.h"


void StageMenu::render() {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press A to PLAY", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press S to SHOP", Vector3(1, 1, 1), 2);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenu::update(double dt) {
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		Stage::changeState("Play");
		//Stage::current_state->init();
	}
	else if (Input::isKeyPressed(SDL_SCANCODE_S)) {
		Stage::changeState("Shop");
		//Stage::current_state->init();
	}

}
void StageMenu::init() {


}