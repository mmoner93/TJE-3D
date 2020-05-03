#include "StagePlay.h"
#include "material.h"
#include "light.h"
//some globals
Shader* shaderBasic = NULL;
Shader* shaderFlat = NULL;

//Animation* anim = NULL;
float angle = 0;
Matrix44 plane_model;
Matrix44 torpedo_model;
bool attached_torpedo = true;
Camera* camera;
Game* gameI = NULL;
Material* material = NULL;
Matrix44 viewprojection;
Light* light = NULL;
Vector3 ambientLight(0.2, 0.2, 0.2);
void StagePlay::init() {

	gameI = Game::instance;

	//OpenGL flags
	glEnable(GL_CULL_FACE); //render both sides of every triangle
	glEnable(GL_DEPTH_TEST); //check the occlusions using the Z buffer

	//create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 10.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, gameI->window_width / (float)gameI->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective

	// example of shader loading using the shaders manager
	shaderBasic = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	shaderFlat = Shader::Get("data/shaders/phong.vs", "data/shaders/phong.ps");
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	
	torpedo_model.setTranslation(0, -5, 0); 
	light = new Light();
	light->position.set(0, 50, 0);
	material = new Material();
	//plane_model.scale(50.0f, 50.0f, 50.0f);
	controlInit = true;
	
}



void renderMeshPhong(Matrix44 m, Mesh* mesh, Texture* texture, int submesh = 0)
{
	if (!shaderFlat)
		return;

	Camera* camera = Camera::current;

	//enable shader
	shaderFlat->enable();

	//upload uniforms
	shaderFlat->setMatrix44("model", m); //upload info to the shader
	shaderFlat->setMatrix44("viewprojection", viewprojection); //upload info to the shader

	shaderFlat->setTexture("color_texture", texture); //set texture in slot 0
	//shaderFlat->setTexture("nomal_texture", textureNorrmal, 1); //set texture in slot 1


	shaderFlat->setUniform3("positionCamera", camera->eye);
	shaderFlat->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shaderFlat);
	material->uploadToShader(shaderFlat);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES,0);
	
	//disable shader
	shaderFlat->disable();
}

void renderMesh(Matrix44 m, Mesh* mesh, Texture* texture, int submesh = 0)
{
	if (!shaderBasic)
		return;

	Camera* camera = Camera::current;

	//enable shader
	shaderBasic->enable();

	//upload uniforms
	shaderBasic->setUniform("u_color", Vector4(1, 1, 1, 1));
	shaderBasic->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shaderBasic->setUniform("u_texture", texture);
	shaderBasic->setUniform("u_model", m);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES, 1);

	//disable shader
	shaderBasic->disable();
}


void StagePlay::render()
{

	if (!controlInit) {
		init();
	}


	Vector3 eye = plane_model * Vector3(0, 10, 30);
	Vector3 center = plane_model * Vector3();
	Vector3 up = plane_model.rotateVector(Vector3(0, 1, 0));
	if (!gameI->free_cam)
		camera->lookAt(eye, center, up); //position the camera and point to 0,0,0

	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();

	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//create model matrix for cube
	Matrix44 m;
	viewprojection = camera->viewprojection_matrix;
	//isla
	Texture* texture = Texture::Get("data/island/island_color_luz.tga");
	Mesh* mesh = Mesh::Get("data/island/island.ASE");
	renderMesh(m, mesh, texture);

	//avion
	texture = Texture::Get("data/spitfire/spitfire_color_spec.tga");
	mesh = Mesh::Get("data/spitfire/spitfire.ASE");
	texture = Texture::Get("data/otros/bomber_axis.tga");
	//mesh = Mesh::Get("data/Pirate Kit/Models/OBJ format/boat_large.obj");
	mesh = Mesh::Get("data/otros/bomber_axis.ASE");

	
	renderMesh(plane_model, mesh, texture);

	//torpedo
	texture = Texture::Get("data/trees/trunk.tga");
	
	mesh = Mesh::Get("data/trees/trunk.obj");
	//texture = Texture::Get("data/spitfire/spitfire_color_spec.tga");
	//mesh = Mesh::Get("data/weapons/Models/ammo_uzi.obj");
	//renderMesh(attached_torpedo ? torpedo_model * plane_model : torpedo_model, mesh, texture);

	renderMeshPhong( torpedo_model , mesh, texture);

	//Draw the floor grid
	drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(gameI->window);
}



void StagePlay::update(double seconds_elapsed)
{
	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	float avionSpeed = 30;
	//example
	angle += (float)seconds_elapsed * 10.0f;



	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || gameI->mouse_locked) //is left button pressed?
	{
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	if (gameI->free_cam == false)
	{
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
		if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
	}
	else
	{
		//async input to move the camera around
		if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	}

	if (Input::isKeyPressed(SDL_SCANCODE_F) && attached_torpedo)
	{
		attached_torpedo = false;
		torpedo_model = torpedo_model * plane_model;
		//torpedo_model.
	}

	if (!gameI->free_cam)
	{
		plane_model.translate(0, 0, seconds_elapsed * -avionSpeed);
	}

	if (!attached_torpedo) {
		torpedo_model.translateGlobal(0, seconds_elapsed * -10, 0);
	}
}