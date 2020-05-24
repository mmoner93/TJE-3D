#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "EntityGameObject.h" 
#include "includes.h"
#include "input.h"
#include "game.h"
#include "enumStructs.h"
class Inventario
{
public:
	int velociti = 1;
	int armaour = 1;
	int stuntTime = 1;
	int grenades = 1;
	int selectedWeapon = 1;
	int weapons[8];
};


#endif 