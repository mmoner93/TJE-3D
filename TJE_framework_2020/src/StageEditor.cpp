#include "StageEditor.h"


#include "material.h"
#include "light.h"
#include "GameMap.h"
#include "Entity.h"
#include "EntityGameObject.h"
#include "EntityMesh.h"
#include "Scene.h"
#include "EntityLight.h"
#include "EntityPlayer.h"
using namespace std;



void StageEditor::init() {

	gameI = Game::instance;

	//OpenGL flags
	glEnable(GL_CULL_FACE); //render both sides of every triangle
	glEnable(GL_DEPTH_TEST); //check the occlusions using the Z buffer

	//create our camera
	//camera = new Camera();
	//camera->lookAt(Vector3(0.f, 10.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	//camera->setPerspective(70.f, gameI->window_width / (float)gameI->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective




	// example of shader loading using the shaders manager
	shaderBasic = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	shaderPhong = Shader::Get("data/shaders/phong.vs", "data/shaders/phong.fs");
	shaderFlat = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	shaderGame = Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs");

	material = new Material();



	material->ambient = Vector3(0.0, 0.0, 0.0);
	material->diffuse = Vector3(0.55, 0.55, 0.55);
	material->specular = Vector3(0.7, 0.70, 0.70);
	material->shininess = 1.0f;



	controlInit = true;



	/*rellenarEntitys();
	rellenarEnemys();

	inicializarScena();*/

}



void StageEditor::render()
{

	if (!controlInit) {
		init();
	}



	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();
	gameScene->pintarScene();
	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	


	//Draw the floor grid
	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	//drawText(20, 20, "HEllo World", Vector3(1, 1, 1), 2);

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(gameI->window);
}



void StageEditor::update(double seconds_elapsed)
{
	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	
	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || gameI->mouse_locked) //is left button pressed?
	{
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	
		//async input to move the camera around
		if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	

	//para que el cielo siga a la camara
	gameScene->cielo->model->setTranslation(camera->center.x, camera->center.y, camera->center.z);
	gameScene->updateScene(seconds_elapsed);
	
    SDL_ShowCursor(true);
	

}