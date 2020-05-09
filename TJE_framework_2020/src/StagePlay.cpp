#include "StagePlay.h"
#include "material.h"
#include "light.h"
#include "GameMap.h"
#include "Entity.h"
#include "EntityGameObject.h"
#include "EntityMesh.h"
#include "Scene.h"
#include "EntityLight.h"
using namespace std;

//some globals
Shader* shaderBasic = NULL;
Shader* shaderFlat = NULL;
Shader* shaderPhong = NULL;
//Animation* anim = NULL;
float angle = 0;
Matrix44 plane_model;
Matrix44 torpedo_model;
Matrix44 arbol2_model;

bool attached_torpedo = true;
Camera* camera;
Game* gameI = NULL;
Material* material = NULL;
Matrix44 viewprojection;
Light* light = NULL;

Matrix44 mLigth;
GameMap* mapGame = NULL;
vector<Entity*> mapaObjects;
Vector3 ambientLight(0.0, 0.0, 0.0);
Scene* gameScene=NULL;

void rellenarEntitys() {

	Entity* temp;
	Texture* textureTemp;
	Mesh* MeshTemp;
	Shader* shaderTemp;
	for (int i = 0; i < NUM_ENTITIES; i++) {
		switch (i) {
		case 0:
			textureTemp = Texture::Get("data/trees/leaves_olive.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material);
			break;
		case 1:
			textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp =  new EntityMesh(textureTemp, shaderTemp, MeshTemp, material);
			break;
		case 2:
			textureTemp = Texture::Get("data/trees/leaves_poplar_autumn.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material);
			break;
		case 3:
			textureTemp = Texture::Get("data/white.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/export (1).obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material);
			break;

		}
		
		mapaObjects.push_back(temp);
	
	}
}


void LoadMap() {

	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");
	//texture = Texture::Get("data/spitfire/spitfire_color_spec.tga");
	//mesh = Mesh::Get("data/weapons/Models/ammo_uzi.obj");
	//renderMesh(attached_torpedo ? torpedo_model * plane_model : torpedo_model, mesh, texture);

	if (!shaderFlat)
		return;

	Camera* camera = Camera::current;




	for (int x = 0; x < mapGame->width; ++x)
		for (int y = 0; y < mapGame->height; ++y)
		{
			//get cell info
			sCell& cell = mapGame->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;

			if (cell.type > 0 && cell.type <= 4) {
				EntityMesh* tempmesh = (EntityMesh*)mapaObjects[cell.type - 1];
				EntityGameObject* temp = new EntityGameObject(tempmesh->textura, tempmesh->shader, tempmesh->mesh, material, 3.0f);
				//temp->renderConPhong(x,y,light);
				temp->model->translate(x, 0.0f, y);
				gameScene->addObject(temp);


			}



		}



	//disable shader
	shaderFlat->disable();
}



void inicializarScena() {

	light = new Light();
	light->position.set(100, 2, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");

	EntityMesh* EntityMeshTemp = new EntityMesh(texture, shaderPhong, mesh, material);


	EntityLight* ltemp = new EntityLight(EntityMeshTemp,light);


	mesh = new Mesh();

	mesh->createPlane(1000);
	Texture* xs = Texture::Get("data/suelo2.tga");
	EntityGameObject* entityGame= new EntityGameObject(xs, shaderBasic, mesh, material,1.0f,100.0f);
	

	mesh = Mesh::Get("data/space_cubemap.ASE"); 

	xs = Texture::Get("data/hell_cubemap.tga");
	EntityGameObject* entityGame2 = new EntityGameObject(xs, shaderBasic, mesh, material, 1.0f, 1.0f);


	gameScene = new Scene(ltemp,entityGame, entityGame2);

}


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
	shaderPhong = Shader::Get("data/shaders/phong.vs", "data/shaders/phong.fs");
	shaderFlat= Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	plane_model.setTranslation(0, 0, 0);
	torpedo_model.setTranslation(0, -5, 0); 
	
	arbol2_model.translate(10, 0, 0);
	//arbol2_model.translate(60, 60, 60);
	
	material = new Material();
	//plane_model.scale(50.0f, 50.0f, 50.0f);

	mapGame = new GameMap(128,128);
	mapGame->loadMapWithMap("data/myMaps/mymap.map");
	controlInit = true;
	//mLigth.setIdentity();
	mLigth.scale(0.01, 0.01, 0.01);
	mLigth.translateGlobal(100, 2, 60);
	//plane_model.scale(20, 20, 20);
	rellenarEntitys();
	inicializarScena();
	LoadMap();
	

}



void renderMeshPhong(Matrix44 m, Mesh* mesh, Texture* texture, int submesh = 0)
{
	if (!shaderPhong)
		return;

	Camera* camera = Camera::current;
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//enable shader
	shaderPhong->enable();

	//upload uniforms
	shaderPhong->setMatrix44("model", m); //upload info to the shader
	shaderPhong->setMatrix44("viewprojection", camera->viewprojection_matrix); //upload info to the shader

	shaderPhong->setTexture("color_texture", texture); //set texture in slot 0
	//shaderFlat->setTexture("nomal_texture", textureNorrmal, 1); //set texture in slot 1


	shaderPhong->setUniform3("positionCamera", camera->eye);
	shaderPhong->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shaderPhong);
	material->uploadToShader(shaderPhong);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES,0);
	
	//disable shader
	shaderPhong->disable();
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
	mesh->render(GL_TRIANGLES, 0);

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
	

	//avion
	texture = Texture::Get("data/spitfire/spitfire_color_spec.tga");
	mesh = Mesh::Get("data/spitfire/spitfire.ASE");
	texture = Texture::Get("data/otros/bomber_axis.tga",false,true);
	//mesh = Mesh::Get("data/Pirate Kit/Models/OBJ format/boat_large.obj");
	mesh = Mesh::Get("data/otros/bomber_axis.ASE");

	
	renderMeshPhong(plane_model, mesh, texture);

	
	texture = Texture::Get("data/white.tga", false, false);

	mesh = Mesh::Get("data/sphere.ASE");

	
	renderMeshPhong(mLigth, mesh, texture);


	texture = Texture::Get("data/white.tga", false, false);

	mesh = Mesh::Get("data/export (1).obj");


	renderMesh(m, mesh, texture);



	gameScene->pintarScene();
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
		arbol2_model.translateGlobal(0, seconds_elapsed * -10, 0);
	}

	

	gameScene->cielo->model->setTranslation(camera->center.x, camera->center.y, camera->center.z);

}