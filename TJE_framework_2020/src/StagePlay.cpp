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
Matrix44 modelA;
Matrix44 mLigth;
GameMap* mapGame = NULL;
vector<Entity*> mapaObjects;
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
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"phong");
			break;
		case 1:
			textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp =  new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			break;
		case 2:
			textureTemp = Texture::Get("data/trees/leaves_poplar_autumn.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			break;
		case 3:
			textureTemp = Texture::Get("data/white.tga", false, false);
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/escena/export_12.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			break;
		case 4:
			textureTemp = Texture::Get("data/escena/estacion1.png");
			shaderTemp = shaderPhong;
			MeshTemp = Mesh::Get("data/escena/estacion1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "phong");
			break;
		case 5:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material,"basic");
			break;
		case 6:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 7:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 8:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 9:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 10:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 11:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 12:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 13:
			textureTemp = Texture::Get("data/escena/mineral.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/mineral.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 14:
			textureTemp = Texture::Get("data/escena/portal.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/portal.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 15:
			textureTemp = Texture::Get("data/escena/defend zone.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/defend zone.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 16:
			textureTemp = Texture::Get("data/escena/angar nave 1.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/angar nave 1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 17:
			textureTemp = Texture::Get("data/escena/angar nave 2.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/angar nave 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 18:
			textureTemp = Texture::Get("data/escena/angar.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/angar.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 19:
			textureTemp = Texture::Get("data/escena/angar2.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/angar2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 20:
			textureTemp = Texture::Get("data/escena/angar3.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/angar3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 21:
			textureTemp = Texture::Get("data/escena/comunications.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/comunications.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 22:
			textureTemp = Texture::Get("data/escena/curve train ok.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/curve train ok.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 23:
			textureTemp = Texture::Get("data/escena/forest.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/forest.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 24:
			textureTemp = Texture::Get("data/escena/forest2.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/forest2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 25:
			textureTemp = Texture::Get("data/escena/mining.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/mining.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 26:
			textureTemp = Texture::Get("data/escena/mining2.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/mining2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 27:
			textureTemp = Texture::Get("data/escena/mining3.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/mining3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 28:
			textureTemp = Texture::Get("data/escena/mining4.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/mining4.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 29:
			textureTemp = Texture::Get("data/escena/recta tren.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/recta tren.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
			break;
		case 30:
			textureTemp = Texture::Get("data/escena/refin tubes.png");
			shaderTemp = shaderBasic;
			MeshTemp = Mesh::Get("data/escena/refin tubes.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, material, "basic");
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
	light->position.set(100, 2, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");

	EntityMesh* EntityMeshTemp = new EntityMesh(texture, shaderPhong, mesh, material,"phong");


	EntityLight* ltemp = new EntityLight(EntityMeshTemp,light);


	mesh = new Mesh();

	mesh->createPlane(1000);
	Texture* xs = Texture::Get("data/escena/suelo3.tga");
	EntityGameObject* entityGame= new EntityGameObject(xs, shaderBasic, mesh, material,"basic",1.0f,1000.0f);
	

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
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	plane_model.setTranslation(0, 0, 0);
	torpedo_model.setTranslation(0, -5, 0); 
	
	arbol2_model.translate(10, 0, 0);
	//arbol2_model.translate(60, 60, 60);
	
	material = new Material();
	//plane_model.scale(50.0f, 50.0f, 50.0f);

	mapGame = new GameMap(256,256);
	mapGame->loadMapWithMap("data/myMaps/mymap2.map");
	controlInit = true;
	//mLigth.setIdentity();
	mLigth.scale(0.01, 0.01, 0.01);
	mLigth.translateGlobal(100, 2, 60);
	//plane_model.scale(20, 20, 20);
	rellenarEntitys();
	inicializarScena();
	LoadMap();
	
	modelA.scale(1.0f, 1.0f, 1.0f);


	player.position=Vector3(10,0,10);
	//player.model.scale(0.01f, 0.01f, 0.01f);
	

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

	shaderPhong->setFloat("u_tilling", 1.0);
	shaderPhong->setUniform3("positionCamera", camera->eye);
	shaderPhong->setUniform3("lightAmbient", ambientLight);
	light->uploadToShader(shaderPhong);
	material->uploadToShader(shaderPhong);
	//shader->setUniform("u_time", time);
	mesh->render(GL_TRIANGLES, -1);
	
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

	
	renderMeshPhong(player.model, mesh, texture);

	
	texture = Texture::Get("data/white.tga", false, false);

	mesh = Mesh::Get("data/sphere.ASE");

	
	renderMeshPhong(mLigth, mesh, texture);


	texture = Texture::Get("data/personajes/ROBOT1.png");

	mesh = Mesh::Get("data/personajes/ROBOT1.obj");

	


	renderMeshPhong(m ,mesh, texture);

	
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
		Vector3 character_center = target_pos + Vector3(0, 0.5,0);
		bool has_collision = false;
		
		for (int i = 0; i < gameScene->mapaObjects.size(); i++)
		{

			EntityGameObject* en = gameScene->mapaObjects[i];

			Mesh* mesh = en->mesh;

			//para cada objecto de la escena...
			Vector3 coll;
			Vector3 collnorm;

			//comprobamos si colisiona el objeto con la esfera (radio 3)
			if (mesh->testSphereCollision(*(en->model), character_center,0.3, coll, collnorm) == false) {
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