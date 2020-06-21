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
	std::map<enumTipoDisparo, int> ammoSaved;
	enumTipoDisparo actualAmmo;
	std::map<std::string, int> weaponsSaved;
	std::string actualWeapon;
	std::map<std::string, int> granadeSaved;
	std::string actualGranade;

	int maxPegamento=5;
	int maxGranade = 2;
	float maxHealth = 10.0f;

	float velociti = 0;
	int armaour = 0;
	int stuntTime = 0;
	int selectedWeapon = 1;
	int weapons[8];   // set de armas para comprar/equipar
};


#endif 