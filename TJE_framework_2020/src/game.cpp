#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"
#include "Stage.h"
#include "StagePlay.h"
#include "StageEditor.h"
#include "StageMenu.h"
#include "StageMenuInGame.h"
#include "StageShop.h"
#include "StageLVL.h"
#include "StageSaveLoad.h"
#include "StageEndLVL.h"
#include <cmath>
#include "extra/bass.h"
#include "AudioBass.h"
//some globals
Shader* shader = NULL;

Animation* anim = NULL;
/*float angle = 0;
Matrix44 plane_model;
Matrix44 torpedo_model;
bool attached_torpedo = true;
*/

Game* Game::instance = NULL;
std::map<std::string, Stage*> Stage::s_stages;
Stage* Stage::current_state = NULL;
Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	

	new StageMenu();
	((StageMenu*)Stage::getStage("Menu"))->init();
	new StageShop();
	((StageShop*)Stage::getStage("Shop"))->init();
	new StageSaveLoad();
	((StageSaveLoad*)Stage::getStage("SaveLoad"))->init();
	new StageMenuInGame();
	((StageMenuInGame*)Stage::getStage("MenuInGame"))->init();
	new StageLVL();
	((StageLVL*)Stage::getStage("SelectLVL"))->init();


	new StagePlay();
	new StageEditor();

	//para evitar luego cargas y errores
	((StagePlay*)Stage::getStage("Play"))->init();

	new StageEndLVL();
	((StageEndLVL*)Stage::getStage("EndLVL"))->init();


	/*
	//OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	//create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f,10.f, 10.f),Vector3(0.f,0.f,0.f), Vector3(0.f,1.f,0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f,window_width/(float)window_height,0.1f,100000.f); //set the projection, we want to be perspective
	*/
	// example of shader loading using the shaders manager
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	//torpedo_model.setTranslation(0, -5, 0);
	MyAudioBass::initBass();
	samplesAudio["ambiente"] = MyAudioBass::Get("data/sounds/ambiente.wav",true);
	samplesAudio["deadRobot"] = MyAudioBass::Get("data/sounds/deadRobot.wav",false);
	samplesAudio["repairRobot"] = MyAudioBass::Get("data/sounds/repairRobot.wav", false);
	samplesAudio["weapon"] = MyAudioBass::Get("data/sounds/weapon.wav", false);
	samplesAudio["pegamento"] = MyAudioBass::Get("data/sounds/pegamento.wav", false);
	samplesAudio["granada"] = MyAudioBass::Get("data/sounds/granada.wav", false);
	samplesAudio["rebotePegamento"] = MyAudioBass::Get("data/sounds/rebotePegamento.wav", false);
	samplesAudio["impactoPegamento"] = MyAudioBass::Get("data/sounds/impactoPegamento.wav", false);
	samplesAudio["impactoShoot"] = MyAudioBass::Get("data/sounds/impactoShoot.wav", false);
	samplesAudio["TutorialJefe"] = MyAudioBass::Get("data/sounds/TutorialJefe.wav", false);
	samplesAudio["ambiente"]->PlaySoundAmbient();
	//sample2->PlaySoundAmbient();
	

	//hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}



//what to do when the image has to be draw
void Game::render(void)
{
	Stage::current_state->render();
}

void Game::update(double seconds_elapsed)
{

	Stage::current_state->update(seconds_elapsed);

	//to navigate with the mouse fixed in the middle
	if (mouse_locked)
		Input::centerMouse();
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_TAB: free_cam = !free_cam;

			if (free_cam && Stage::current_state->actual_name._Equal("Play")) {


				((StageEditor*)Stage::getStage("Editor"))->gameScene= ((StagePlay*)Stage::current_state)->gameSceneSP;
				((StageEditor*)Stage::getStage("Editor"))->camera = ((StagePlay*)Stage::current_state)->cameraSP;
				Stage::changeState("Editor");
				Stage::current_state->init();

			}else if(!free_cam && Stage::current_state->actual_name._Equal("Editor")){
				Stage::changeState("Play");
			}


			break;
		case SDLK_F1: Shader::ReloadAll(); break;
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}




}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}
