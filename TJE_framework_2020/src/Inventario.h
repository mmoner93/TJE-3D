#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
class Inventario
{
public:
	//std::map<enumTipoDisparo, int> ammoSaved;
	enumTipoDisparo actualAmmo;
	//std::map<std::string, int> weaponsSaved;
	std::string actualWeapon;
	//std::map<std::string, int> granadeSaved;
	std::string actualGranade;

	int estoyGuardadoEn = 0;

	int ammoPegamento;
	int ammoDisparo;
	int ammoGranada;


	int mejora_Mapa = 0;
	int coins = 0;
	bool arma2Comprada=false;

	int bestPuntuacion0 = 0;
	int bestPuntuacion1 = 0;
	int bestPuntuacion2 = 0;
	int bestPuntuacion3 = 0;
	int bestPuntuacion4 = 0;
	int bestPuntuacion5 = 0;
	int bestPuntuacion6 = 0;
	int bestPuntuacion7 = 0;
	int bestPuntuacion8 = 0;
	

	int maxPegamento=5;
	int maxGranade = 10;
	float maxHealth = 10.0f;

	float velociti = 0;
	int armaour = 0;
	int stuntTime = 0;
	int selectedWeapon = 1;
	int weapons[8];   // set de armas para comprar/equipar
};


#endif 