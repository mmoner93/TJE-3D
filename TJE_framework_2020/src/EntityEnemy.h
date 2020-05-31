#ifndef ENTITYENEMY_H
#define ENTITYENEMY_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
#include <list>
class EntityEnemy :public EntityGameObject
{
public:
	Vector3 position;
	float yaw;
	float pitch;
	//EntityGameObject* weapon;
	Vector3 vel_x;
	Vector3 vel_y;
	float vel_ang;
	float angle;
	
	Mesh* disparoMesh;
	Texture* disparoTexture;

	estadosRobot actualState;
	enumEnemyMove actualDirection= STOP;

	float health = 1.0;
	bool aLive = true;
	std::vector<Vector3> pointsSP;
	std::vector<Vector3> normPointsSP;
	Shader* shaderPuntos;
	Matrix44 puntos;


	int contadorMovimientos = 0;
	int contadorCollisions = 0;
	std::list<Vector3> movs;

	//time ----------------
	float timeTopNextMove = 0.05;
	float timeNextMove = 1.0;
	float initTimeNextCalcCaminoIa = 4.0;
	float timeNextCalcCaminoIa = 0.0;


	bool calculando;

	EntityEnemy(Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, Vector3 pos, Shader* shaderP, float sc = 1.0, float til = 1.0, float ya = 0.0, float pi = 0.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {

		yaw = ya;
		pitch = pi;
		//weapon = NULL;
		angle = 0.0;
		vel_ang = 0.0;
		position = pos;
		shaderPuntos = shaderP;
		actualState = STOP_R;
		calculando = false;
		disparoMesh = Mesh::Get("data/impactos/impacto.OBJ");
		disparoTexture = Texture::Get("data/impactos/impacto.png");

	}


	void render(Light* light);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 moveEnemy(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool checkTime(float seconds_elapsed);
	void onReceveidShoot(Vector3 temp, Vector3 norm);
	void renderPoints(Mesh* meshT);
	void atacar();
	bool mirarSiPlayerCerca();
	void contadorMovUp();
	void contadorCollUp();
	void raroIA();
	


	void calcularCaminoIA();
	void queHacer(float seconds_elapsed, std::vector<EntityGameObject*> objects);


	bool estoyEnUsoIACalc();

};


#endif 