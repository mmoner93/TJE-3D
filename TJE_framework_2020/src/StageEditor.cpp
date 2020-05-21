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


//some globals
Shader* shaderBasic = NULL;
Shader* shaderFlat = NULL;
Shader* shaderPhong = NULL;
Shader* shaderGame = NULL;
//Animation* anim = NULL;

Camera* camera;
Game* gameI = NULL;
Material* material = NULL;

vector<Entity*> mapaObjects;//guardo la info de que dibujar segun type
map<string, Entity*> enemysMap;//guardo la info de como dibujarlo
Scene* gameScene = NULL;




void StageEditor::rellenarEnemys() {
	Entity* temp;
	Texture* textureTemp;
	Mesh* MeshTemp;
	Shader* shaderTemp;

	for (int i = 0; i < NUM_ENEMYS; i++) {
		switch (i) {
		case 0:
			textureTemp = Texture::Get("data/personajes/Arachnoid.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/Arachnoid.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");

			enemysMap["Arachnoid"] = temp;
			break;
		case 1:
			textureTemp = Texture::Get("data/personajes/ReconBot.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/ReconBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["ReconBot"] = temp;
			break;
		case 2:
			textureTemp = Texture::Get("data/personajes/Companion-bot.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/Companion-bot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["Companion"] = temp;
			break;
		case 3:
			textureTemp = Texture::Get("data/personajes/MobileStorageBot.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/MobileStorageBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["MobileStorageBot"] = temp;
			break;
		case 4:
			textureTemp = Texture::Get("data/personajes/MechaTrooper.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/MechaTrooper.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["MechaTrooper"] = temp;
			break;
		case 5:
			textureTemp = Texture::Get("data/personajes/FieldFighter.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/FieldFighter.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["FieldFighter"] = temp;
			break;
		case 6:
			textureTemp = Texture::Get("data/personajes/QuadrupedTank.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/QuadrupedTank.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["QuadrupedTank"] = temp;
			break;
		case 7:
			textureTemp = Texture::Get("data/personajes/MechaGolem.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/MechaGolem.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["MechaGolem"] = temp;
			break;
		case 8:
			textureTemp = Texture::Get("data/personajes/Mecha01.png", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/personajes/Mecha01.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			enemysMap["Mecha01"] = temp;
			break;
		}



	}

}


void StageEditor::rellenarEntitys() {

	//es posible que más adelante nos venga bien guardarle a cada objeto su type.

	Entity* temp;
	Texture* textureTemp;
	Mesh* MeshTemp;
	Shader* shaderTemp;
	for (int i = 0; i <= NUM_ENTITIES; i++) {
		switch (i) {
		case 0://no aplica
			textureTemp = NULL;
			shaderTemp = NULL;
			MeshTemp = NULL;
			temp = NULL;
		case TREE_OLIVE:
			textureTemp = Texture::Get("data/trees/leaves_olive.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case TREE_POPLAR:
			textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case TREE_POPLAR_AUTUM:
			textureTemp = Texture::Get("data/trees/leaves_poplar_autumn.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HOUSE_CUTRE:
			textureTemp = Texture::Get("data/white.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/export_12.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case ESTACION_1:
			textureTemp = Texture::Get("data/escena/estacion1.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/estacion1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case CORNER_IZQUIERDA_SUP:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case CORNER_IZQUIERDA_INF:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case CORNER_DERECHA_SUP:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case CORNER_DERECHA_INF:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case WALL_SUP:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case WALL_DER:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case WALL_IZ:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case WALL_INF:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case MINA:
			textureTemp = Texture::Get("data/escena/mineral.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mineral.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case PORTAL:
			textureTemp = Texture::Get("data/escena/portal.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/portal.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case TORRETAS_DEFENS:
			textureTemp = Texture::Get("data/escena/defend zone.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/defend zone.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HANGAR_1:
			textureTemp = Texture::Get("data/escena/angar nave 1.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar nave 1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HANGAR_2:
			textureTemp = Texture::Get("data/escena/angar nave 2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar nave 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HANGAR_3:
			textureTemp = Texture::Get("data/escena/angar.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HANGAR_4:
			textureTemp = Texture::Get("data/escena/angar2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case HANGAR_5:
			textureTemp = Texture::Get("data/escena/angar3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case TOWER_COMMU:
			textureTemp = Texture::Get("data/escena/comunications.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/comunications.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case CURVA_TRAIN:
			textureTemp = Texture::Get("data/escena/curve train ok.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/curve train ok.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case FOREST_1:
			textureTemp = Texture::Get("data/escena/forest.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/forest.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case FOREST_2:
			textureTemp = Texture::Get("data/escena/forest2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/forest2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case MINA_1:
			textureTemp = Texture::Get("data/escena/mining.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case MINA_2:
			textureTemp = Texture::Get("data/escena/mining2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case MINA_3:
			textureTemp = Texture::Get("data/escena/mining3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case MINA_4:
			textureTemp = Texture::Get("data/escena/mining4.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining4.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case REFIN_TUBES:
			textureTemp = Texture::Get("data/escena/refin tubes.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/refin tubes.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;

		case ALMACEN:
			textureTemp = Texture::Get("data/escena/almacen.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/almacen.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case BARRILES:
			textureTemp = Texture::Get("data/escena/barriles.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/barriles.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case FABRICA:
			textureTemp = Texture::Get("data/escena/fabrica.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/fabrica.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case NAVE_1:
			textureTemp = Texture::Get("data/escena/nave.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/nave.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case TRANSFORMADORES:
			textureTemp = Texture::Get("data/escena/transformadores.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/transformadores.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case ROOM_1:
			textureTemp = Texture::Get("data/escena/habitacion control.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case ROOM_2:
			textureTemp = Texture::Get("data/escena/habitacion control 2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case ROOM_3:
			textureTemp = Texture::Get("data/escena/habitacion control 3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control 3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case PUERTO:
			textureTemp = Texture::Get("data/escena/puerto.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/puerto.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		}

		mapaObjects.push_back(temp);

	}
}







void StageEditor::inicializarScena() {

	Light* light = new Light();
	light->position.set(100, 50, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	//light
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");


	EntityLight* ltemp = new EntityLight(light, texture, shaderGame, mesh, material, "game", 0.01);

	//suelo
	mesh = new Mesh();

	mesh->createPlane(1000);

	Texture* xs = Texture::Get("data/terra_lila2.png");
	EntityGameObject* entitySuelo = new EntityGameObject(xs, shaderGame, mesh, material, "game", 1.0f, 1000.f);



	//cielo

	//mesh = Mesh::Get("data/space_cubemap.ASE"); cielo.ASE

	//xs = Texture::Get("data/hell_cubemap.tga");
	mesh = Mesh::Get("data/cielo.ASE");
	xs = Texture::Get("data/cielo.png");

	EntityGameObject* entityCielo = new EntityGameObject(xs, shaderBasic, mesh, material, "basic", 1.0f, 1.0f);


	//player

	Mesh* meshTemp = Mesh::Get("data/personajes/playerRojoMascara.OBJ");
	Texture* texTemp = Texture::Get("data/personajes/playerRojoMascara.png", false, true);
	EntityPlayer* player;
	player = new EntityPlayer(texTemp, shaderGame, meshTemp, material, "game", Vector3(10, 0, 10));

	texTemp = Texture::Get("data/arma/uzi.png", false, true);
	meshTemp = Mesh::Get("data/arma/uzi.obj");

	EntityGameObject* tempWeapon = new EntityGameObject(texTemp, shaderGame, meshTemp, material, "game");

	player->atachWeapon(tempWeapon);


	gameScene = new Scene(ltemp, entitySuelo, entityCielo, player);
	gameScene->LoadMap(mapaObjects);
	gameScene->loadEnemys(enemysMap);
}




void StageEditor::init() {

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
	shaderFlat = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	shaderGame = Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs");

	material = new Material();



	material->ambient = Vector3(0.0, 0.0, 0.0);
	material->diffuse = Vector3(0.55, 0.55, 0.55);
	material->specular = Vector3(0.7, 0.70, 0.70);
	material->shininess = 1.0f;



	controlInit = true;



	rellenarEntitys();
	rellenarEnemys();

	inicializarScena();

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

	
    SDL_ShowCursor(true);
	

}