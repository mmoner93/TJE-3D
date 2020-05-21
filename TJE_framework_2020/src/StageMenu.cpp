#include "StageMenu.h"


void StageMenu::render() {
	
	glClearColor(0.0, 0.0, 0.0, 1.0);

	drawText(20, 20, "Press A...", Vector3(1, 1, 1), 2);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenu::update(double dt) {
	if (Input::isKeyPressed(SDL_SCANCODE_A)) {
		Stage::changeState("Play");
		//Stage::current_state->init();
	}

}
void StageMenu::init() {


}