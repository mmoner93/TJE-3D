#ifndef ENTITYENEMY_H
#define ENTITYENEMY_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
#include "animation.h"
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
	Mesh* disparoMeshPegamento;
	Texture* disparoPegamentoTexture;

	Animation* idle;
	Animation* run;
	Animation* walk;
	Animation dying;
	Animation* mele1;
	Animation* mele2;
	Skeleton* blendWalkRun;
	bool animated = false;
	int attacking_which = 0;
	float attacking_time = 0.0f;


	estadosRobot actualState;
	enumEnemyMove actualDirection= STOP;

	float health = 4.0;
	bool aLive = true;
	float time_dead = 0.0;


	float shield = 4.0;
	Mesh* shieldMesh;
	Texture* shieldTexture;
	float time_shield_rotate;



	std::vector<Vector3> pointsSP;
	std::vector<Vector3> pointsSPegamento;
	std::vector<Vector3> normPointsSP;
	Shader* shaderPuntos;
	Matrix44 puntos;


	int contadorMovimientos = 0;
	int contadorCollisions = 0;
	std::list<Vector3> movs;
	std::list<Vector3>movs_tower;

	//time ----------------
	float timeTopNextMove = 0.05;
	float timeNextMove = 1.0;
	float initTimeNextCalcCaminoIa = 4.0;
	float timeNextCalcCaminoIa = 0.0;

	float timeNextAttack = 0.0;
	float timeNextAttackMax = 5.0;
	float timeNextShield = 4.0f;
	float timeNextShieldMax = 4.0f;
	float timeStuned = 0.0;
	float timeStunedMax = 3.0;

	bool calculando;


	bool is_node=true;
	int num_pegamento_in=0;


	int id_principal=-1;
	int id_padre=-1;

	Vector3 nextMovelist;

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
		disparoMeshPegamento = Mesh::Get("data/impactos/impactoPegamento.OBJ");
		disparoPegamentoTexture = Texture::Get("data/impactos/impactogris.png");
		shieldMesh = Mesh::Get("data/itemsUse/shield_ene.obj");
		shieldTexture = Texture::Get("data/itemsUse/shield_ene.png");
	}


	void render(Light* light,Vector3 fog);
	void update(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool testCollision(Vector3 target_pos, float seconds_elapsed, std::vector<EntityGameObject*> objects);
	Vector3 moveEnemy(float seconds_elapsed, std::vector<EntityGameObject*> objects);
	bool checkTime(float seconds_elapsed);
	void onReceveidShoot(Vector3 temp, Vector3 norm);
	void onReceveidShootPegamento(Vector3 temp, Vector3 norm);
	void renderPoints(Mesh* meshT);
	void atacar();
	bool mirarSiPlayerCerca();
	void contadorMovUp();
	void contadorCollUp();
	void raroIA();
	
	void moveWithIaList();
	void moveWithIaListTower();

	void loalAnim(int enemy);
	void renderAnimated(Light* light, Vector3 fog);

	void calcularCaminoIA();
	void queHacer(float seconds_elapsed, std::vector<EntityGameObject*> objects);

	void goDestroyTower();

	bool estoyEnUsoIACalc();
	void mirarSiPisoPegamento();
	void sonidoKefe();

};


#endif 