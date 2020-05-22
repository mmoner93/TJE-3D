#include "GameMap.h"
using namespace std;


bool GameMap::loadMapWithMap(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL) //file not found
		return NULL;

	sMapHeader header; //read header and store it in the struct
	fread(&header, sizeof(sMapHeader), 1, file);

	assert(header.bytes == 1); //always control bad cases!!
	//allocate memory for the cells data and read it
	unsigned char* cells = new unsigned char[header.w * header.h];
	fread(cells, header.bytes, header.w * header.h, file);
	fclose(file); //always close open files
	//create the map where we will store it
	//GameMap* map = new GameMap(header.w, header.h);
	width = header.w;
	height = header.h;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			getCell(x, y).type = (eCellType)cells[x + y * width];

	delete[] cells; //always free any memory allocated!

	return true;
}

int* GameMap::loadMapWithCsv(const char* filesrc, int size) { //archivo y tamaño de area
	int pos = 0;
	int* mapborder = new int[size];
	ifstream file;
	file.open(filesrc, fstream::in);
	if (!file.is_open()) {
		fprintf(stderr, "Error locating the file map");
	}
	while (file.good()) {
		string line;
		while (getline(file, line)) {   // get a whole line
			std::stringstream ss(line);
			while (getline(ss, line, ',')) {
				int aux;
				istringstream(line) >> aux;
				mapborder[pos++] = aux;
			}
		}
	}
	return mapborder;
}




bool validarType(sCell& temp) {
	if (temp.type >= 144  && temp.type<=151 || temp.type==128 || temp.type == 129 || temp.type == 130 || temp.type == 241
		|| temp.type == 67 || temp.type == 2 || temp.type == 225 || temp.type == 226 || temp.type == 227 || temp.type == 34 || temp.type == 35
		|| temp.type == 242 || temp.type == 224 || temp.type == 17 || temp.type == 20 || temp.type == 38 || temp.type == 195 || temp.type == 193) {
		return false;
	}

	return true;
}

bool GameMap::movimiento_valido(Vector2 Movement,int tipo) {
	int cs = 8;


	sCell& cellLeftUp = getCell(floor((Movement.x) /cs), floor(Movement.y /cs));
	sCell& cellRightUp = getCell(floor((Movement.x+ cs) / cs), floor(Movement.y / cs));
	sCell& cellLeftDown = getCell(floor((Movement.x) / cs), floor((Movement.y+ cs) / cs));
	sCell& cellRightDown = getCell(floor((Movement.x + cs) / cs), floor((Movement.y + cs) / cs));

	if (validarType(cellLeftUp) && validarType(cellRightUp) && validarType(cellLeftDown) && validarType(cellRightDown)) {
		return true;
	}
	else {
		return false;
	}

	
}



