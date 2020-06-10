#include "StageLVL.h"
#include "StagePlay.h"
int lvlOnScreen = 0;
int lvls[3] = { LVL1, LVL2, LVL3 };

void StageLVL::render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderUI(0, uiTexture, 1);
	drawText(20, 20, "Press P to return to Play", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press M to exit to the main menu", Vector3(1, 1, 1), 2);

	drawText(298, 80, std::to_string(lvlOnScreen), Vector3(1, 1, 1), 2);
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageLVL::update(double dt) {
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) {
		optionSelected -= 1;
		if (optionSelected < 1) {
			optionSelected = 3;
		}
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_D)) {
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
		StagePlay* temp = ((StagePlay*)(Stage::getStage("Play")));
		
		if (optionSelected == 1) {
			
			temp->gameSceneSP = temp->Lvls[0];
			temp->gameSceneSP->restartLvl(temp->enemysMapSP);
			Stage::changeState("Play");
		}
		else if (optionSelected == 2) {
			temp->gameSceneSP = temp->Lvls[1];
			temp->gameSceneSP->restartLvl(temp->enemysMapSP);
			Stage::changeState("Play");
		}
		else if (optionSelected == 3) {
			Stage::changeState("Play");
		}



		//Stage::current_state->init();
	}

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
	select1 = Texture::Get("data/UI/lvlselected/select1.png");
	select2 = Texture::Get("data/UI/lvlselected/select2.png");
	select3 = Texture::Get("data/UI/lvlselected/select3.png");
	uiTexture = select1;

}