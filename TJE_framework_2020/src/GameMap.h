#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "includes.h"
#include "stdint.h"
#include "framework.h"
#include "utils.h"
//#include "image.h"
//#include "enumsStruct.h"
#include "assert.h"
#include <iostream>
#include <fstream>
#include "enumStructs.h"

class GameMap {
public:

	

	int width;
	int height;
	sCell* data;


	GameMap()
	{
		width = height = 0;
		data = NULL;
	}

	GameMap(int w, int h)
	{
		width = w;
		height = h;
		data = new sCell[w * h];
	}

	sCell& getCell(int x, int y)
	{
		return data[x + y * width];
	};

	sCell* getCellPointers(int x, int y)
	{
		return &data[x + y * width];
	};
	
	bool loadMapWithMap(const char* filename);
	int* loadMapWithCsv(const char* filesrc, int size);


	//void paintMap(Image* fb,Image& tileset, float time);

	bool movimiento_valido(Vector2 Movement, int tipo);

	//void changeSomething(PowerType what, Vector2 target);
};

#endif