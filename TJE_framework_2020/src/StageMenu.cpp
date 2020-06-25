#include "StageMenu.h"
#include "StagePlay.h"


void StageMenu::render() {

	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*drawText(20, 20, "Press P to Select LVL", Vector3(1, 1, 1), 2);
	drawText(20, 40, "Press S to Shop", Vector3(1, 1, 1), 2);
	drawText(20, 60, "Press L to Load/Save", Vector3(1, 1, 1), 2);*/
	if (((StagePlay*)Stage::getStage("Play"))->Lvls[0] != NULL) {
		((StagePlay*)Stage::getStage("Play"))->init();
		((StagePlay*)Stage::getStage("Play"))->Lvls[1]->pintarScene();
	}
		
	if (cual==0){
		renderUI(0, introTexture, 1);
	}
	else {
		renderUI(0, uiTexture, 1);
	}
	SDL_GL_SwapWindow(Game::instance->window);
}
void StageMenu::update(double dt) {
	//
	float r = 100;
	float x = r * cos(Game::instance->elapsed_time);
	float y = r * sin(Game::instance->elapsed_time);
	//trasladar
	//apuntar al centro
	Camera* aux = Camera::current;
	//aux->center = Vector3(x, 10.0f, y);
	//Vector3
	if (cual == 1) {
		if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
			optionSelected -= 1;
			if (optionSelected < 1) {
				optionSelected = 5;
			}
		}
		else if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
			optionSelected += 1;
			if (optionSelected > 5) {
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
		else if (optionSelected == 4) {
			uiTexture = select4;
		}
		else if (optionSelected == 5) {
			uiTexture = select5;
		}



		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			if (optionSelected == 1) {
				Stage::changeState("SaveLoad");
			}
			else if (optionSelected == 2) {
				Stage::changeState("Shop");
			}
			else if (optionSelected == 3) {
				Stage::changeState("SelectLVL");
			}
			else if (optionSelected == 5) {
				uiTexture = tutorial1;
				cual = 2;
			}
			else if (optionSelected == 4) {
				uiTexture = controles;
				cual = 5;
			}



			//Stage::current_state->init();
		}
	}
	else if(cual==0)
	{
		if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
			uiTexture = introTexture;
			cual = 1;
		}
	}
	else if (cual == 2) {
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			uiTexture = tutorial2;
			cual = 3;
		}
	}
	else if (cual == 3) {
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			uiTexture = tutorial3;
			cual = 4;
		}
	}
	else if (cual == 4) {
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			optionSelected = 1;
			uiTexture = select1;
			cual = 1;
		}
	}
	else if (cual == 5) {
		if (Input::wasKeyPressed(SDL_SCANCODE_E)) {
			optionSelected = 1;
			uiTexture = select1;
			cual = 1;
		}
	}
	


}
void StageMenu::init() {
	select1 = Texture::Get("data/UI/menu/selected1.png");
	select2 = Texture::Get("data/UI/menu/selected2.png");
	select3 = Texture::Get("data/UI/menu/selected3.png");
	select4 = Texture::Get("data/UI/menu/selected4.png");
	select5 = Texture::Get("data/UI/menu/selected5.png");
	tutorial1 = Texture::Get("data/UI/tutorial/tutorial1.png");
	tutorial2 = Texture::Get("data/UI/tutorial/tutorial2.png");
	tutorial3 = Texture::Get("data/UI/tutorial/tutorial3.png");
	controles = Texture::Get("data/UI/controls.png");
	introTexture = Texture::Get("data/UI/intro.png");
	uiTexture = select1;

}