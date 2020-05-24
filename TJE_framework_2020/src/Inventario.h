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
	float velociti = 0;
	int armaour = 0;
	int stuntTime = 0;
	int ammo = 0;
	int grenades = 0;
	int selectedWeapon = 1;
	int weapons[8];   // set de armas para comprar/equipar
};


#endif 