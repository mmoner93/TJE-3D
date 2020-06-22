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

	if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
		optionSelectedFila -= 1;
		if (optionSelectedFila < 1) {
			optionSelectedFila = 3;
		}
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		optionSelectedFila += 1;
		if (optionSelectedFila > 3) {
			optionSelectedFila = 1;
		}
	}


	if (optionSelected == 1) {
		if (optionSelectedFila == 1) {
			uiTexture = select1;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select21;
		}
		else {
			uiTexture = select31;
		}
		
	}
	else if (optionSelected == 2) {
		if (optionSelectedFila == 1) {
			uiTexture = select2;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select22;
		}
		else {
			uiTexture = select32;
		}
	}
	else if (optionSelected == 3) {
		if (optionSelectedFila == 1) {
			uiTexture = select3;
		}
		else if (optionSelectedFila == 2) {
			uiTexture = select23;
		}
		else {
			uiTexture = select33;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
		StagePlay* temp = ((StagePlay*)(Stage::getStage("Play")));
		

		if (optionSelected == 1) {
			if (optionSelectedFila == 1) {
				temp->gameSceneSP = temp->Lvls[0];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else if (optionSelectedFila == 2) {
				temp->gameSceneSP = temp->Lvls[3];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else {
				temp->gameSceneSP = temp->Lvls[6];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}

		}
		else if (optionSelected == 2) {
			if (optionSelectedFila == 1) {
				temp->gameSceneSP = temp->Lvls[1];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else if (optionSelectedFila == 2) {
				temp->gameSceneSP = temp->Lvls[4];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else {
				temp->gameSceneSP = temp->Lvls[7];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
		}
		else if (optionSelected == 3) {
			if (optionSelectedFila == 1) {
				temp->gameSceneSP = temp->Lvls[2];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else if (optionSelectedFila == 2) {
				temp->gameSceneSP = temp->Lvls[5];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
			else {
				temp->gameSceneSP = temp->Lvls[8];
				temp->gameSceneSP->restartLvl(temp->enemysMapSP);
				Stage::changeState("Play");
			}
		}







		//Stage::current_state->init();
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
		Stage::changeState("Menu");
		//Stage::current_state->init();
	}
	

}
void StageLVL::init() {
	select1 = Texture::Get("data/UI/lvlselected/select1.png");
	select2 = Texture::Get("data/UI/lvlselected/select2.png");
	select3 = Texture::Get("data/UI/lvlselected/select3.png");
	select21 = Texture::Get("data/UI/lvlselected/select21.png");
	select22 = Texture::Get("data/UI/lvlselected/select22.png");
	select23 = Texture::Get("data/UI/lvlselected/select23.png");
	select31 = Texture::Get("data/UI/lvlselected/select31.png");
	select32 = Texture::Get("data/UI/lvlselected/select32.png");
	select33 = Texture::Get("data/UI/lvlselected/select33.png");
	uiTexture = select1;

}