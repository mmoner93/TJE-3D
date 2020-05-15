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
Shader* shaderGame = NULL;
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
Matrix44 modelA;
Matrix44 mLigth;
GameMap* mapGame = NULL;
vector<Entity*> mapaObjects;
map<string,Entity*> enemysMap;
Vector3 ambientLight(0.0, 0.0, 0.0);
Scene* gameScene=NULL;

std::vector<Vector3> points;


struct sPlayer {
	Vector3 position;
	float yaw;
	float pitch;
	Matrix44 model;
	sPlayer() { yaw=pitch = 0.0; }
};

sPlayer player;

void rellenarEnemys() {
	Entity* temp;
	Texture* textureTemp;
	Mesh* MeshTemp;
	Shader* shaderTemp;

	for (int i = 0; i < NUM_ENEMYS; i++) {
		switch (i) {
		case 0:
			textureTemp = Texture::Get("data/personajes/Arachnoid.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/Arachnoid.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			
			enemysMap["Arachnoid"] = temp;
			break;
		case 1:
			textureTemp = Texture::Get("data/personajes/ReconBot.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/ReconBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["ReconBot"] = temp;
			break;
		case 2:
			textureTemp = Texture::Get("data/personajes/Companion-bot.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/Companion-bot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["Companion"] = temp;
			break;
		case 3:
			textureTemp = Texture::Get("data/personajes/MobileStorageBot.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/MobileStorageBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["MobileStorageBot"] = temp;
			break;
		case 4:
			textureTemp = Texture::Get("data/personajes/MechaTrooper.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/MechaTrooper.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["MechaTrooper"] = temp;
			break;
		case 5:
			textureTemp = Texture::Get("data/personajes/FieldFighter.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/FieldFighter.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["FieldFighter"] = temp;
			break;
		case 6:
			textureTemp = Texture::Get("data/personajes/QuadrupedTank.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/QuadrupedTank.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["QuadrupedTank"] = temp;
			break;
		case 7:
			textureTemp = Texture::Get("data/personajes/MechaGolem.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/MechaGolem.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			enemysMap["MechaGolem"] = temp;
			break;
		case 8:
			textureTemp = Texture::Get("data/personajes/Mecha01.png", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/personajes/Mecha01.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
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
	for (int i = 0; i < NUM_ENTITIES; i++) {
		switch (i) {
		case 0:
			textureTemp = Texture::Get("data/trees/leaves_olive.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"game");
			break;
		case 1:
			textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp =  new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 2:
			textureTemp = Texture::Get("data/trees/leaves_poplar_autumn.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 3:
			textureTemp = Texture::Get("data/white.tga", false, false);
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/export_12.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 4:
			textureTemp = Texture::Get("data/escena/estacion1.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/estacion1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 5:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"game");
			break;
		case 6:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 7:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 8:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 9:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 10:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 11:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 12:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 13:
			textureTemp = Texture::Get("data/escena/mineral.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mineral.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 14:
			textureTemp = Texture::Get("data/escena/portal.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/portal.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 15:
			textureTemp = Texture::Get("data/escena/defend zone.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/defend zone.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 16:
			textureTemp = Texture::Get("data/escena/angar nave 1.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar nave 1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 17:
			textureTemp = Texture::Get("data/escena/angar nave 2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar nave 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 18:
			textureTemp = Texture::Get("data/escena/angar.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 19:
			textureTemp = Texture::Get("data/escena/angar2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 20:
			textureTemp = Texture::Get("data/escena/angar3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/angar3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 21:
			textureTemp = Texture::Get("data/escena/comunications.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/comunications.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 22:
			textureTemp = Texture::Get("data/escena/curve train ok.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/curve train ok.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 23:
			textureTemp = Texture::Get("data/escena/forest.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/forest.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 24:
			textureTemp = Texture::Get("data/escena/forest2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/forest2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 25:
			textureTemp = Texture::Get("data/escena/mining.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 26:
			textureTemp = Texture::Get("data/escena/mining2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 27:
			textureTemp = Texture::Get("data/escena/mining3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 28:
			textureTemp = Texture::Get("data/escena/mining4.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/mining4.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 29:
			textureTemp = Texture::Get("data/escena/refin tubes.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/refin tubes.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
			
		case 30:	
			textureTemp = Texture::Get("data/escena/almacen.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/almacen.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 31:
			textureTemp = Texture::Get("data/escena/barriles.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/barriles.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 32:
			textureTemp = Texture::Get("data/escena/fabrica.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/fabrica.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 33:
			textureTemp = Texture::Get("data/escena/nave.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/nave.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 34:
			textureTemp = Texture::Get("data/escena/transformadores.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/transformadores.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 35:
			textureTemp = Texture::Get("data/escena/habitacion control.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 36:
			textureTemp = Texture::Get("data/escena/habitacion control 2.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
			break;
		case 37:
			textureTemp = Texture::Get("data/escena/habitacion control 3.png");
			shaderTemp = shaderGame;
			MeshTemp = Mesh::Get("data/escena/habitacion control 3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "game");
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

			if (cell.type > 0 && cell.type <= NUM_ENTITIES) {
				EntityMesh* tempmesh = (EntityMesh*)mapaObjects[cell.type - 1];
				EntityGameObject* temp = new EntityGameObject(tempmesh->textura, tempmesh->shader, tempmesh->mesh, material,tempmesh->nameShader, 3.0f);
				//temp->renderConPhong(x,y,light);
				temp->model->translate(x*3, 0.0f, y*3);

				//podria hacer una función para indicar estas cosas.
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



	//disable shader
	shaderFlat->disable();
}





void inicializarScena() {

	light = new Light();
	light->position.set(100, 50, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");

	EntityMesh* EntityMeshTemp = new EntityMesh(texture, shaderPhong, mesh, material,"phong");


	EntityLight* ltemp = new EntityLight(EntityMeshTemp,light);


	mesh = new Mesh();

	mesh->createPlane(1000);
	Texture* xs = Texture::Get("data/escena/bgv9.png");
	//en el de cuadros 5000
	EntityGameObject* entityGame= new EntityGameObject(xs, shaderGame, mesh, material,"game",1.0f,1000.0f);
	

	mesh = Mesh::Get("data/space_cubemap.ASE"); 

	xs = Texture::Get("data/hell_cubemap.tga");
	EntityGameObject* entityGame2 = new EntityGameObject(xs, shaderBasic, mesh, material, "basic", 1.0f, 1.0f);


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
	shaderGame= Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs");
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	plane_model.setTranslation(0, 0, 0);
	torpedo_model.setTranslation(0, -5, 0); 
	
	arbol2_model.translate(10, 0, 0);
	//arbol2_model.translate(60, 60, 60);
	
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
	




	//plane_model.scale(50.0f, 50.0f, 50.0f);

	mapGame = new GameMap(256,256);
	mapGame->loadMapWithMap("data/myMaps/mymap3.map");
	controlInit = true;
	//mLigth.setIdentity();
	mLigth.scale(0.01, 0.01, 0.01);
	mLigth.translateGlobal(100, 50, 60);
	//plane_model.scale(20, 20, 20);
	rellenarEntitys();
	rellenarEnemys();
	inicializarScena();
	LoadMap();
	
	modelA.scale(1.0f, 1.0f, 1.0f);


	player.position=Vector3(10,0,10);
	//player.model.scale(0.01f, 0.01f, 0.01f);
	

}



void renderMeshPhong(Matrix44 m, Mesh* mesh, Texture* texture, int submesh = -1)
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

	shaderPhong->setFloat("u_tilling", 1.0);
	shaderPhong->setUniform3("positionCamera", camera->eye);
	shaderPhong->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shaderPhong);
	material->uploadToShader(shaderPhong);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES, submesh);
	
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
	shaderBasic->setFloat("u_tilling", 1.0);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES, -1);

	//disable shader
	shaderBasic->disable();
}

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


		EntityGameObject* temp  = new EntityGameObject(en->textura, en->shader, en->mesh, en->material, "phong");
		
		temp->model->translate(0, 0, i * 10.0f);
		
		renderMeshPhong(*temp->model, temp->mesh, temp->textura);

	}


}


void paintEnemys() {


	for (int i = 0; i < NUM_ENEMYS; i++) {
		EntityGameObject* en;

		switch (i) {
		case 0:
			en = (EntityGameObject*)enemysMap["Arachnoid"];
			
			break;
		case 1:

			en = (EntityGameObject*)enemysMap["ReconBot"];
			break;
		case 2:

			en = (EntityGameObject*)enemysMap["Companion"];
			break;
		case 3:

			en = (EntityGameObject*)enemysMap["MobileStorageBot"];
			break;
		case 4:

			en = (EntityGameObject*)enemysMap["MechaTrooper"];
			break;
		case 5:

			en = (EntityGameObject*)enemysMap["FieldFighter"];
			break;
		case 6:

			en = (EntityGameObject*)enemysMap["QuadrupedTank"];
			break;
		case 7:

			en = (EntityGameObject*)enemysMap["MechaGolem"];
			break;
		case 8:

			en = (EntityGameObject*)enemysMap["Mecha01"];
			break;
		}



		renderMeshPhong(*en->model, en->mesh, en->textura);

	}



}


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

	//player

	
    Vector3 eye = player.model * Vector3(0, 0.6, -0.2);
	Vector3 front(0, 0, -1);
	Matrix44 PITCH;
	PITCH.setRotation(player.pitch * DEG2RAD, Vector3(1, 0, 0));
	front = PITCH.rotateVector(front);
	Matrix44 YAW;
	YAW.setRotation(player.yaw * DEG2RAD, Vector3(0, 1, 0));
	front = YAW.rotateVector(front);
	Vector3 center = eye + front;
	Vector3 up = Vector3(0, 1, 0);

	if (!gameI->free_cam)
		camera->lookAt(eye, center, up); //position the camera and point to 0,0,0

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

	//create model matrix for cube
	Matrix44 m;
	viewprojection = camera->viewprojection_matrix;
	//isla
	Texture* texture = Texture::Get("data/island/island_color_luz.tga");
	Mesh* mesh = Mesh::Get("data/island/island.ASE");
	

	//avion
	//texture = Texture::Get("data/spitfire/spitfire_color_spec.tga");
	//mesh = Mesh::Get("data/spitfire/spitfire.ASE");
	texture = Texture::Get("data/personajes/playerRojoMascara.png",false,true);
	//mesh = Mesh::Get("data/Pirate Kit/Models/OBJ format/boat_large.obj");
	mesh = Mesh::Get("data/personajes/playerRojoMascara.OBJ");

	Matrix44* ter = new Matrix44(player.model);

	//ter->scale(0.5, 0.5, 0.5);
	ter->translate(0.2, 0, -0.5);
	ter->rotate(-180 * DEG2RAD, Vector3(0, 1, 0));

	renderMeshPhong(player.model, mesh, texture);

	texture= Texture::Get("data/arma/uzi.png", false, true);
	mesh = Mesh::Get("data/arma/uzi.obj");
	

	renderMeshPhong(*ter, mesh, texture,-1);

	texture = Texture::Get("data/white.tga", false, false);

	mesh = Mesh::Get("data/sphere.ASE");

	
	renderMeshPhong(mLigth, mesh, texture);


	//texture = Texture::Get("data/personajes/ROBOT1.png");

	//mesh = Mesh::Get("data/personajes/ROBOT1.obj");

	


	//renderMeshPhong(m ,mesh, texture);

	//paintEnemys();
	loadEnemys();

	Mesh points_mesh;
	points_mesh.vertices = points;
	if (points.size()) {
		renderPoints(Matrix44(), &points_mesh, NULL, 0);
	}
	
	
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
		Matrix44 R;

		R.setRotation(player.yaw * DEG2RAD, Vector3(0, 1, 0));
		Vector3 front = R.rotateVector(Vector3(0, 0, -1));
		Vector3 right = R.rotateVector(Vector3(1, 0, 0));
		Vector3 target_pos = player.position;

		if(Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) target_pos = player.position + front * 10*speed * seconds_elapsed;
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) target_pos = player.position - front * 10 * speed * seconds_elapsed;
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))  target_pos = player.position - right * 10 * speed * seconds_elapsed;
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) target_pos = player.position + right * 10 * speed * seconds_elapsed;
		//if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
		//if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));

		player.yaw -= Input::mouse_delta.x * 0.1;
		player.pitch -= Input::mouse_delta.y * 0.1;

		//calculamos el centro de la esfera de colisión del player elevandola hasta la cintura
		Vector3 character_center = target_pos + Vector3(0, 1.0,0);
		bool has_collision = false;
		
		for (int i = 0; i < gameScene->mapaObjects.size(); i++)
		{

			EntityGameObject* en = gameScene->mapaObjects[i];

			Mesh* mesh = en->mesh;

			//para cada objecto de la escena...
			Vector3 coll;
			Vector3 collnorm;

			//comprobamos si colisiona el objeto con la esfera (radio 3)
			if (mesh->testSphereCollision(*(en->model), character_center,0.1, coll, collnorm) == false) {
				continue; //si no colisiona, pasamos al siguiente objeto
			}
			/*if(mesh->testRayCollision(*(en->model), character_center, Vector3(0,0, 1), coll, collnorm,15.0f,true) == false)
				continue;*/
			has_collision = true;
			Vector3 push_away = normalize(coll - character_center) * seconds_elapsed;
			target_pos = player.position - push_away;
			target_pos.y = 0;	
			break;

			//si la esfera está colisionando muevela a su posicion anterior alejandola del objeto
			//Vector3 push_away = normalize(coll - character_center) * dt;
			//position = previous_pos - push_away; //move to previous pos but a little bit further

			//cuidado con la Y, si nuestro juego es 2D la ponemos a 0
			//position.y = 0;

			//reflejamos el vector velocidad para que de la sensacion de que rebota en la pared
			//velocity = reflect(velocity, collnorm) * 0.95;

		}


		//TRS

		//if (!has_collision) 
		player.position = target_pos;

		//player.model.setIdentity();
	
		player.model.setTranslation(player.position.x, player.position.y, player.position.z);
		
		player.model.rotate(player.yaw * DEG2RAD, Vector3(0, 1, 0));
	

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

	if (Input::isKeyPressed(SDL_SCANCODE_C)) {
		addPoint();
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

	if (gameI->free_cam == false) {
		Input::centerMouse();
		SDL_ShowCursor(false);
	}
	else {
		SDL_ShowCursor(true);
	}

}