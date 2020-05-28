#include "StageLVL.h"

int lvlOnScreen = 0;
int lvls[3] = { LVL1, LVL2, LVL3 };

void StageLVL::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawText(20, 20, "Press P to return to Play", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press M to exit to the main menu", Vector3(1, 1, 1), 2);

	drawText(330, 400, "D-->", Vector3(1, 1, 1), 2);
	drawText(270, 400, "<--A", Vector3(1, 1, 1), 2);
	drawText(298, 80, std::to_string(lvlOnScreen), Vector3(1, 1, 1), 2);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageLVL::update(double dt) {
	if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
		//Stage::current_state->init();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_P)) {
		Stage::changeState("Play");
		//new weapon ++
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		lvlOnScreen -= 1;
		if (lvlOnScreen < 0) {
			lvlOnScreen = 3;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_D)) {
		lvlOnScreen += 1;
		if (lvlOnScreen > 3) {
			lvlOnScreen = 0;
		}
	}

}
void StageLVL::init() {


}