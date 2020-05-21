#ifndef STAGEPLAY_H
#define STAGEPLAY_H

#include "includes.h"
#include "Stage.h"
#include "camera.h"
#include "game.h"
#include "Entity.h"
#include "material.h"
#include "Scene.h"

class StagePlay :public Stage
{
public:
	Shader* shaderBasicSP;
	Shader* shaderFlatSP;
	Shader* shaderPhongSP;
	Shader* shaderGameSP;

	Camera* cameraSP;
	Game* gameISP;
	Material* materialSP;

	//guardo la info de que dibujar segun type
	//guardo la info de como dibujarlo
	std::vector<Entity*> listEntitysSP;
	std::map<std::string, Entity*> enemysMapSP;
	Scene* gameSceneSP;
	std::vector<Vector3> pointsSP;


	StagePlay() :Stage("Play") {
		iniciado = true;
	};

	void render();
	void update(double dt);
	void init();
	void addPoint();
	void rellenarEnemys();
	void rellenarEntitys();
	void inicializarScena();


	//son de pruebas que usaremos más adelante.
	void renderPoints(Matrix44 m, Mesh* mesh,int submesh = 0);

};


#endif