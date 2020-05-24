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
	int armaour = 1;
	int stuntTime = 1;
	int grenades = 1;
	int selectedWeapon = 1;
	int weapons[8];
};


#endif 