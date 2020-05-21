#include "StagePlay.h"
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
GameMap* mapGame = NULL;
vector<Entity*> mapaObjects;//guardo la info de que dibujar segun type
map<string,Entity*> enemysMap;//guardo la info de como dibujarlo
Scene* gameScene=NULL;

std::vector<Vector3> points;


/*Pruebas

Matrix44 plane_model;
Matrix44 torpedo_model;
Matrix44 arbol2_model;

bool attached_torpedo = true;
float angle = 0;
*/

void rellenarEnemys() {
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


void rellenarEntitys() {

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
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"game");
			break;
		case TREE_POPLAR:
			textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp =  new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
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
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"game");
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


void LoadMap() {
	for (int x = 0; x < mapGame->width; ++x)
		for (int y = 0; y < mapGame->height; ++y)
		{
			//get cell info
			sCell& cell = mapGame->getCell(x, y);
			if (cell.type == 0) //skip empty
				continue;

			if (cell.type > 0 && cell.type <= NUM_ENTITIES) {
				EntityMesh* tempmesh = (EntityMesh*)mapaObjects[cell.type];
				EntityGameObject* temp = new EntityGameObject(tempmesh->textura, tempmesh->shader, tempmesh->mesh, material,tempmesh->nameShader, 3.0f);

				temp->model->translate(x*3, 0.0f, y*3);

				//podria hacer una función para indicar estas cosas. Roto las figuras para que cuadren en escenario (esquinas , paredes)
				if (cell.type == 6) {
					temp->model->rotate(PI,Vector3(0,1,0));
				}

				if (cell.type == 7) {
					temp->model->rotate(PI/2, Vector3(0, 1, 0));
				}

				if (cell.type == 8) {
					temp->model->rotate(-PI / 2, Vector3(0, 1, 0));
				}


				if (cell.type == 10) {
					temp->model->rotate(PI/2, Vector3(0, 1, 0));
				}

				if (cell.type == 11) {
					temp->model->rotate(PI, Vector3(0, 1, 0));
				}

				if (cell.type == 13) {
					temp->model->rotate(-PI/2, Vector3(0, 1, 0));
				}


				gameScene->addObject(temp);


			}



		}

}





void inicializarScena() {

	Light* light = new Light();
	light->position.set(100, 50, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	//light
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");

	EntityGameObject* EntityMeshTemp = new EntityGameObject(texture, shaderGame, mesh, material,"game",0.01);

	EntityMeshTemp->model->translateGlobal(light->position.x, light->position.y, light->position.z);
	EntityLight* ltemp = new EntityLight(EntityMeshTemp,light);


	//suelo
	mesh = new Mesh();

	mesh->createPlane(1000);

	Texture* xs = Texture::Get("data/terra_lila2.png");
	EntityGameObject* entitySuelo= new EntityGameObject(xs, shaderGame, mesh, material,"game",1.0f,1000.f);
	


	//cielo

	//mesh = Mesh::Get("data/space_cubemap.ASE"); cielo.ASE

	//xs = Texture::Get("data/hell_cubemap.tga");
	mesh = Mesh::Get("data/cielo.ASE");
	xs = Texture::Get("data/cielo.png");

	EntityGameObject* entityCielo = new EntityGameObject(xs, shaderBasic, mesh, material, "basic", 1.0f,1.0f);


	//player

	Mesh* meshTemp = Mesh::Get("data/personajes/playerRojoMascara.OBJ");
	Texture* texTemp = Texture::Get("data/personajes/playerRojoMascara.png", false, true);
	EntityPlayer* player;
	player = new EntityPlayer(texTemp, shaderGame, meshTemp, material, "game", Vector3(10, 0, 10));

	texTemp = Texture::Get("data/arma/uzi.png", false, true);
	meshTemp = Mesh::Get("data/arma/uzi.obj");

	EntityGameObject* tempWeapon = new EntityGameObject(texTemp, shaderGame, meshTemp, material, "game");

	player->atachWeapon(tempWeapon);


	gameScene = new Scene(ltemp, entitySuelo, entityCielo,player);

}


void loadEnemys() {

	for (int i = 0; i < NUM_ENEMYS; i++) {
		EntityMesh* en;

		switch (i) {
		case 0:
			en = (EntityMesh*)enemysMap["Arachnoid"];

			break;
		case 1:

			en = (EntityMesh*)enemysMap["ReconBot"];
			break;
		case 2:

			en = (EntityMesh*)enemysMap["Companion"];
			break;
		case 3:

			en = (EntityMesh*)enemysMap["MobileStorageBot"];
			break;
		case 4:

			en = (EntityMesh*)enemysMap["MechaTrooper"];
			break;
		case 5:

			en = (EntityMesh*)enemysMap["FieldFighter"];
			break;
		case 6:

			en = (EntityMesh*)enemysMap["QuadrupedTank"];
			break;
		case 7:

			en = (EntityMesh*)enemysMap["MechaGolem"];
			break;
		case 8:

			en = (EntityMesh*)enemysMap["Mecha01"];
			break;
		}


		EntityGameObject* temp = new EntityGameObject(en->textura, en->shader, en->mesh, en->material, "game");

		temp->model->translate(0, 0, i * 10.0f);

		gameScene->addObject(temp);
	}


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
	shaderGame= Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs");
	
	material = new Material();

	
	
	
	
	
	/*plata
	
	material->ambient = Vector3(0.19225f, 0.19225f, 0.19225f);
	material->diffuse = Vector3(0.50754f, 0.50754f, 0.50754f);
	material->specular = Vector3(0.508273f, 0.508273f, 0.508273f);
	material->shininess = 0.4f;
	*/

	//chromo

	material->ambient = Vector3(0.0, 0.0, 0.0);
	material->diffuse = Vector3(0.55, 0.55, 0.55);
	material->specular = Vector3(0.7, 0.70, 0.70);
	material->shininess = 1.0f;
	


	mapGame = new GameMap(256,256);
	mapGame->loadMapWithMap("data/myMaps/mycaca.map");
	controlInit = true;
	//mLigth.setIdentity();

	
	rellenarEntitys();
	rellenarEnemys();
	
	inicializarScena();
	loadEnemys();
	LoadMap();

	
	//pruebas
	
	//plane_model.scale(50.0f, 50.0f, 50.0f);
	//plane_model.scale(20, 20, 20);
	//player.model.scale(0.01f, 0.01f, 0.01f);
	//arbol2_model.translate(10, 0, 0);
	//arbol2_model.translate(60, 60, 60);
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	//plane_model.setTranslation(0, 0, 0);
	//torpedo_model.setTranslation(0, -5, 0); 
}


//de momento lo dejo aqui. Se puede transladar cuando haga mecanica pensada de "pegamento" para reparar.
void renderPoints(Matrix44 m, Mesh* mesh, Texture* texture=NULL, int submesh = 0)
{
	if (!shaderFlat)
		return;

	Camera* camera = Camera::current;

	//enable shader
	shaderFlat->enable();

	//upload uniforms
	shaderFlat->setUniform("u_color", Vector4(1, 1, 1, 1));
	shaderFlat->setUniform("u_viewprojection", camera->viewprojection_matrix);
	
	shaderFlat->setUniform("u_model", m);
	shaderFlat->setFloat("u_tilling", 1.0);
	//shader->setUniform("u_time", time);
	mesh->render(GL_POINTS, -1);

	//disable shader
	shaderFlat->disable();
}



//como antes
void StagePlay :: addPoint() {

	Vector3 pos = camera->center;
	pos.y = 0;
	Vector3 origin = camera->center;
	Vector3 dir = camera->getRayDirection(Input::mouse_position.x,Input::mouse_position.y, gameI->window_width, gameI->window_height);

	//para poner algo en el suelo
	//pos = RayPlaneCollision(Vector3(),Vector3(0,1,0),origin,dir);


	for (int i = 0; i<gameScene->mapaObjects.size(); i++) {
		EntityGameObject* en = gameScene->mapaObjects[i];

		Mesh* mesh = en->mesh;

		if (mesh->testRayCollision(*en->model, origin, dir, pos, Vector3())) {
			points.push_back(pos);
			break;
		}
	
	}

	/*Mesh* mesh = Mesh::Get("data/personajes/ROBOT1.obj");

	if(mesh->testRayCollision(Matrix44(), origin, dir, pos, Vector3()) ){
		points.push_back(pos);
	}*/


}


void StagePlay::render()
{

	if (!controlInit) {
		init();
	}

	//avion
	/*Vector3 eye = plane_model * Vector3(0, 10, 30);
	Vector3 center = plane_model * Vector3();
	Vector3 up = plane_model.rotateVector(Vector3(0, 1, 0));*/

	

	//set the clear color (the background color)
	//glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	camera->enable();
	gameScene->pintarScene();
	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	Mesh points_mesh;
	points_mesh.vertices = points;
	if (points.size()) {
		renderPoints(Matrix44(), &points_mesh, NULL, 0);
	}
	
	
	//Draw the floor grid
	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	//drawText(20, 20, "HEllo World", Vector3(1, 1, 1), 2);

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(gameI->window);
}



void StagePlay::update(double seconds_elapsed)
{
	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	float avionSpeed = 30;
	//avion
	//angle += (float)seconds_elapsed * 10.0f;

	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || gameI->mouse_locked) //is left button pressed?
	{
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	if (gameI->free_cam == false)
	{
		//actualizo para collisiones.
		gameScene->myPlayer->update(seconds_elapsed, gameScene->mapaObjects);
		
		/*Avion
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
		if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
		if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
		*/

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

	//para disparar los puntos de colision
	if (Input::isKeyPressed(SDL_SCANCODE_C)) {
		addPoint();
	}


	/* avion
	if (Input::isKeyPressed(SDL_SCANCODE_F) && attached_torpedo)
	{
		attached_torpedo = false;
		torpedo_model = torpedo_model * plane_model;
		//torpedo_model.
	}

	if (!attached_torpedo) {
		torpedo_model.translateGlobal(0, seconds_elapsed * -10, 0);
		arbol2_model.translateGlobal(0, seconds_elapsed * -10, 0);
	}


	
	if (!gameI->free_cam)
	{
		plane_model.translate(0, 0, seconds_elapsed * -avionSpeed);
	}

	*/
	

	//para que el cielo siga a la camara
	gameScene->cielo->model->setTranslation(camera->center.x, camera->center.y, camera->center.z);

	if (gameI->free_cam == false) {
		Input::centerMouse();
		SDL_ShowCursor(false);
	}
	else {
		SDL_ShowCursor(true);
	}

}