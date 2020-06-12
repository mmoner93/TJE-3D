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


//Animation* anim = NULL;

/*Pruebas

Matrix44 plane_model;
Matrix44 torpedo_model;
Matrix44 arbol2_model;

bool attached_torpedo = true;
float angle = 0;
*/

void StagePlay::rellenarEnemys() {
	Entity* temp;
	Texture* textureTemp;
	Mesh* MeshTemp;
	Shader* shaderTemp;

	for (int i = 0; i < NUM_ENEMYS; i++) {
		switch (i) {
		
		case 0:
			textureTemp = Texture::Get("data/personajes/Arachnoid.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/personajes/Arachnoid.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			
			enemysMapSP["Arachnoid"] = temp;
			break;
		case 1:
			textureTemp = Texture::Get("data/personajes/ReconBot.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/personajes/ReconBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			enemysMapSP["ReconBot"] = temp;
			break;
			
		case 2:
			textureTemp = Texture::Get("data/personajes/Companion-bot.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/companion/companion.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["Companion"] = temp;
			break;
			
		case 3:
			textureTemp = Texture::Get("data/personajes/MobileStorageBot.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/personajes/MobileStorageBot.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			enemysMapSP["MobileStorageBot"] = temp;
			break;
			
		case 4:
			textureTemp = Texture::Get("data/personajes/MechaTrooper.png", false, false);
			shaderTemp = shaderGameSP;
			//MeshTemp = Mesh::Get("data/personajes/MechaTrooper.obj");
			MeshTemp = Mesh::Get("data/animations/mechatrooper/MechaTrooper.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["MechaTrooper"] = temp;
			break;
		case 5:
			textureTemp = Texture::Get("data/personajes/FieldFighter.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/fieldfighter/fieldfighter.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["FieldFighter"] = temp;
			break;
			
		case 6:
			textureTemp = Texture::Get("data/personajes/QuadrupedTank.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/personajes/QuadrupedTank.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			enemysMapSP["QuadrupedTank"] = temp;
			break;
			
		case 7:
			textureTemp = Texture::Get("data/personajes/MechaGolem.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/mechagolem/mechagolem.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["MechaGolem"] = temp;
			break;
		case 8:
			textureTemp = Texture::Get("data/personajes/Mecha01.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/mecha01/mecha01.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["Mecha01"] = temp;
			break;
		case 9:
			textureTemp = Texture::Get("data/personajes/Companion-bot.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/companion/companion big.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["CompanionBig"] = temp;
			break;
		case 10:
			textureTemp = Texture::Get("data/personajes/MechaTrooper.png", false, false);
			shaderTemp = shaderGameSP;
			//MeshTemp = Mesh::Get("data/personajes/MechaTrooper.obj");
			MeshTemp = Mesh::Get("data/animations/mechatrooper/mechatrooper big.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["MechaTrooperBig"] = temp;
			break;
		case 11:
			textureTemp = Texture::Get("data/personajes/FieldFighter.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/fieldfighter/fielfighter_big.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["FieldFighterBig"] = temp;
			break;
		case 12:
			textureTemp = Texture::Get("data/personajes/MechaGolem.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/mechagolem/mechagolem big.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["MechaGolemBig"] = temp;
			break;
		case 13:
			textureTemp = Texture::Get("data/personajes/Mecha01.png", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/animations/mecha01/mecha01 big.mesh");
			temp = new EntityMesh(textureTemp, shaderAnimSP, MeshTemp, materialSP, "game");
			enemysMapSP["Mecha01Big"] = temp;
			break;
		}



	}

}


void StagePlay::rellenarEntitys() {

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
			//textureTemp = Texture::Get("data/trees/leaves_olive.tga", false, false);
			shaderTemp = shaderGameSP;
			//MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP,"game");
			break;
		case TREE_POPLAR:
			//textureTemp = Texture::Get("data/trees/leaves_poplar.tga", false, false);
			shaderTemp = shaderGameSP;
			//MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp =  new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case TREE_POPLAR_AUTUM:
			//textureTemp = Texture::Get("data/trees/leaves_poplar_autumn.tga", false, false);
			shaderTemp = shaderGameSP;
			//MeshTemp = Mesh::Get("data/trees/leaves.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HOUSE_CUTRE:
			textureTemp = Texture::Get("data/white.tga", false, false);
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/export_12.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case ESTACION_1:
			textureTemp = Texture::Get("data/escena/estacion1.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/estacion1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case CORNER_IZQUIERDA_SUP:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP,"game");
			break;
		case CORNER_IZQUIERDA_INF:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case CORNER_DERECHA_SUP:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case CORNER_DERECHA_INF:
			textureTemp = Texture::Get("data/escena/corner.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/corner.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case WALL_SUP:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case WALL_DER:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case WALL_IZ:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case WALL_INF:
			textureTemp = Texture::Get("data/escena/wall.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/wall.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case MINA:
			textureTemp = Texture::Get("data/escena/mineral.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/mineral.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case PORTAL:
			textureTemp = Texture::Get("data/escena/portal.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/portal.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case TORRETAS_DEFENS:
			textureTemp = Texture::Get("data/escena/defend zone2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/defend zone2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HANGAR_1:
			textureTemp = Texture::Get("data/escena/angar nave 1.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/angar nave 1.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HANGAR_2:
			textureTemp = Texture::Get("data/escena/angar nave 2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/angar nave 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HANGAR_3:
			textureTemp = Texture::Get("data/escena/angar.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/angar.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HANGAR_4:
			textureTemp = Texture::Get("data/escena/angar2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/angar2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case HANGAR_5:
			textureTemp = Texture::Get("data/escena/angar3.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/angar3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case TOWER_COMMU:
			textureTemp = Texture::Get("data/escena/comunications.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/comunications.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case CURVA_TRAIN:
			textureTemp = Texture::Get("data/escena/curve train ok.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/curve train ok.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case FOREST_1:
			textureTemp = Texture::Get("data/escena/forest.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/forest.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case FOREST_2:
			textureTemp = Texture::Get("data/escena/forest2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/forest2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case MINA_1:
			textureTemp = Texture::Get("data/escena/mining.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/mining.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case MINA_2:
			textureTemp = Texture::Get("data/escena/mining2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/mining2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case MINA_3:
			textureTemp = Texture::Get("data/escena/mining3.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/mining3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case MINA_4:
			textureTemp = Texture::Get("data/escena/mining4.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/mining4.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case REFIN_TUBES:
			textureTemp = Texture::Get("data/escena/refin tubes.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/refin tubes.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
			
		case ALMACEN:
			textureTemp = Texture::Get("data/escena/almacen.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/almacen.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case BARRILES:
			textureTemp = Texture::Get("data/escena/barriles.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/barriles.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case FABRICA:
			textureTemp = Texture::Get("data/escena/fabrica.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/fabrica.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case NAVE_1:
			textureTemp = Texture::Get("data/escena/nave.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/nave.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case TRANSFORMADORES:
			textureTemp = Texture::Get("data/escena/transformadores.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/transformadores.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case ROOM_1:
			textureTemp = Texture::Get("data/escena/habitacion control.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/habitacion control.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case ROOM_2:
			textureTemp = Texture::Get("data/escena/habitacion control 2.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/habitacion control 2.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case ROOM_3:
			textureTemp = Texture::Get("data/escena/habitacion control 3.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/habitacion control 3.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		case PUERTO:
			textureTemp = Texture::Get("data/escena/puerto.png");
			shaderTemp = shaderGameSP;
			MeshTemp = Mesh::Get("data/escena/puerto.obj");
			temp = new EntityMesh(textureTemp, shaderTemp, MeshTemp, materialSP, "game");
			break;
		}
		
		listEntitysSP.push_back(temp);
	
	}
}







void StagePlay::inicializarScena() {

	Light* light = new Light();
	light->position.set(100, 50, 60);
	light->specular_color.set(1.0f, 1.0f, 1.0f);
	light->diffuse_color.set(1.0f, 1.0f, 1.0f);


	//light
	Texture* texture = Texture::Get("data/white.tga", false, false);

	Mesh* mesh = Mesh::Get("data/sphere.ASE");


	EntityLight* ltemp = new EntityLight(light, texture, shaderGameSP, mesh, materialSP, "game", 0.01);

	//suelo
	mesh = new Mesh();

	mesh->createPlane(1000);

	Texture* xs = Texture::Get("data/terra_lila2.png");
	EntityGameObject* entitySuelo= new EntityGameObject(xs, shaderGameSP, mesh, materialSP,"game",1.0f,1000.f);
	


	//cielo

	//mesh = Mesh::Get("data/space_cubemap.ASE"); cielo.ASE

	//xs = Texture::Get("data/hell_cubemap.tga");
	mesh = Mesh::Get("data/cielo.ASE");
	xs = Texture::Get("data/cielo.png");

	EntityGameObject* entityCielo = new EntityGameObject(xs, shaderBasicSP, mesh, materialSP, "basic", 1.0f,1.0f);


	//player

	//Mesh* meshTemp = Mesh::Get("data/personajes/playerRojoMascara.OBJ");
	//Texture* texTemp = Texture::Get("data/personajes/playerRojoMascara.png", false, true);
	Mesh* meshTemp = Mesh::Get("data/animations/character final.mesh");
	Texture* texTemp = Texture::Get("data/animations/new_caracther.png");
	EntityPlayer* player;
	player = new EntityPlayer(texTemp, shaderAnimSP, meshTemp, materialSP, "game", Vector3(10.f, 0.f, 10.f));
	player->loalAnim();


	texTemp = Texture::Get("data/arma/weaponPegamento.png", false, true);
	meshTemp = Mesh::Get("data/arma/weaponPegamento.obj");


	EntityGameObject* tempWeapon = new EntityGameObject(texTemp, shaderGameSP, meshTemp, materialSP, "game");

	player->atachWeapon(PEGAMENTO, tempWeapon);

	texTemp = Texture::Get("data/arma/uzi.png", false, true);
	meshTemp = Mesh::Get("data/arma/uzi.obj");
	tempWeapon = new EntityGameObject(texTemp, shaderGameSP, meshTemp, materialSP, "game");

	player->atachWeapon(WEAPON1, tempWeapon);

	uiTexture = Texture::Get("data/UI/items.png");
	damage = Texture::Get("data/UI/vida.png");

	
	Lvls[0]= new Scene(0, ltemp, entitySuelo, entityCielo, player);

	Lvls[0]->LoadMap(listEntitysSP);
	Lvls[0]->loadEnemys(enemysMapSP);
	Lvls[0]->initListDisparos();
	Lvls[0]->spawnTower();

	Lvls[1] = new Scene(1, ltemp, entitySuelo, entityCielo, player);

	Lvls[1]->LoadMap(listEntitysSP);
	Lvls[1]->loadEnemys(enemysMapSP);
	Lvls[1]->initListDisparos();
	Lvls[1]->spawnTower();

	//gameSceneSP = Lvls[0];


}




void StagePlay::init() {

	gameISP = Game::instance;
	
	//OpenGL flags
	glEnable(GL_CULL_FACE); //render both sides of every triangle
	glEnable(GL_DEPTH_TEST); //check the occlusions using the Z buffer

	//create our camera
	cameraSP = new Camera();
	cameraSP->lookAt(Vector3(0.f, 10.f, 10.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	cameraSP->setPerspective(70.f, gameISP->window_width / (float)gameISP->window_height, 0.1f, 100000.f); //set the projection, we want to be perspective

	// example of shader loading using the shaders manager
	shaderBasicSP = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	shaderPhongSP = Shader::Get("data/shaders/phong.vs", "data/shaders/phong.fs");
	shaderFlatSP= Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	shaderGameSP= Shader::Get("data/shaders/basic.vs", "data/shaders/Game.fs");
	shaderAnimSP = Shader::Get("data/shaders/skinningnew.vs", "data/shaders/Game.fs");
	
	materialSP = new Material();

	
	
	
	
	
	/*plata
	
	material->ambient = Vector3(0.19225f, 0.19225f, 0.19225f);
	material->diffuse = Vector3(0.50754f, 0.50754f, 0.50754f);
	material->specular = Vector3(0.508273f, 0.508273f, 0.508273f);
	material->shininess = 0.4f;
	*/

	//chromo

	materialSP->ambient = Vector3(0.0, 0.0, 0.0);
	materialSP->diffuse = Vector3(0.55, 0.55, 0.55);
	materialSP->specular = Vector3(0.7, 0.70, 0.70);
	materialSP->shininess = 1.0f;
	


	
	//mLigth.setIdentity();

	
	rellenarEntitys();
	rellenarEnemys();
	
	inicializarScena();
	
	

	
	//pruebas
	
	//plane_model.scale(50.0f, 50.0f, 50.0f);
	//plane_model.scale(20, 20, 20);
	//player.model.scale(0.01f, 0.01f, 0.01f);
	//arbol2_model.translate(10, 0, 0);
	//arbol2_model.translate(60, 60, 60);
	//phongShader = Shader::Get("phong.vs", "phong.ps");
	//plane_model.setTranslation(0, 0, 0);
	//torpedo_model.setTranslation(0, -5, 0); 


	controlInit = true;

}


//de momento lo dejo aqui. Se puede transladar cuando haga mecanica pensada de "pegamento" para reparar.
void StagePlay::renderPoints(Matrix44 m, Mesh* mesh, int submesh )
{
	if (!shaderFlatSP)
		return;

	Camera* camera = Camera::current;

	//enable shader
	shaderFlatSP->enable();

	//upload uniforms
	shaderFlatSP->setUniform("u_color", Vector4(1, 1, 1, 1));
	shaderFlatSP->setUniform("u_viewprojection", camera->viewprojection_matrix);
	
	shaderFlatSP->setUniform("u_model", m);
	shaderFlatSP->setFloat("u_tilling", 1.0);
	//shader->setUniform("u_time", time);
	mesh->render(GL_POINTS, -1);

	//disable shader
	shaderFlatSP->disable();
}



//como antes
void StagePlay :: addPoint() {

	Vector3 pos = cameraSP->center;
	pos.y = 0;
	Vector3 origin = cameraSP->center;
	Vector3 dir = cameraSP->getRayDirection(Input::mouse_position.x,Input::mouse_position.y, gameISP->window_width, gameISP->window_height);

	//para poner algo en el suelo
	//pos = RayPlaneCollision(Vector3(),Vector3(0,1,0),origin,dir);


	for (int i = 0; i<gameSceneSP->mapaObjects.size(); i++) {
		EntityGameObject* en = gameSceneSP->mapaObjects[i];

		Mesh* mesh = en->mesh;

		if (mesh->testRayCollision(*en->model, origin, dir, pos, Vector3())) {
			pointsSP.push_back(pos);
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
	cameraSP->enable();
	gameSceneSP->pintarScene();
	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	Mesh points_mesh;
	points_mesh.vertices = pointsSP;
	if (pointsSP.size()) {
		renderPoints(Matrix44(), &points_mesh, 0);
	}
	
	
	//Draw the floor grid
	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	drawText(400, 295, "X", Vector3(1, 1, 1), 2);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	

	renderUI(0, uiTexture, 0.8f);
	gameSceneSP->myPlayer->radar();
	//drawText(725, 525, "A", Vector3(1, 1, 1), 2);
	//drawText(725, 570, "G", Vector3(1, 1, 1), 2);

//	NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
		
	float opacity = 1.0 - gameSceneSP->myPlayer->health * 0.1;
	//float opacity = (((gameSceneSP->myPlayer->health - 0.0f) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin;
	renderUI(0, damage, opacity);

	
	SDL_GL_SwapWindow(gameISP->window);
}



void StagePlay::update(double seconds_elapsed)
{
	float speed = (float)seconds_elapsed * (float)10; //the speed is defined by the seconds_elapsed so it goes constant
	float avionSpeed = 30;
	//avion
	//angle += (float)seconds_elapsed * 10.0f;

	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || gameISP->mouse_locked) //is left button pressed?
	{
		cameraSP->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		cameraSP->rotate(Input::mouse_delta.y * 0.005f, cameraSP->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}


	//actualizo para collisiones.
	gameSceneSP->myPlayer->update(seconds_elapsed, gameSceneSP->mapaObjects);
		
	/*Avion
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(1, 0, 0));
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) plane_model.rotate(-90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) plane_model.rotate(90 * seconds_elapsed * DEG2RAD, Vector3(0, 1, 0));
	if (Input::isKeyPressed(SDL_SCANCODE_Q)) plane_model.rotate(40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
	if (Input::isKeyPressed(SDL_SCANCODE_E)) plane_model.rotate(-40 * seconds_elapsed * DEG2RAD, Vector3(0, 0, -1));
	*/


	//para disparar los puntos de colision
	/*if (Input::isKeyPressed(SDL_SCANCODE_C)) {
		addPoint();
	}
	*/

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
	gameSceneSP->cielo->model->setTranslation(cameraSP->center.x, cameraSP->center.y, cameraSP->center.z);
	gameSceneSP->updateScene(seconds_elapsed);
	
	Input::centerMouse();
	SDL_ShowCursor(false);
	if (Input::wasKeyPressed(SDL_SCANCODE_M))
	{
		Stage::changeState("MenuInGame");
	}

	if (gameSceneSP->checkEndLvl()) {
		Stage::changeState("EndLVL");
	}

}