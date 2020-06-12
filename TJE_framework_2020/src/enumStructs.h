#ifndef ENUMSTRUCTS_H
#define ENUMSTRUCTS_H

#define NUM_ENTITIES 39
#define NUM_ENEMYS 14
#define MAX_IMPACTO_DISPAROS 35
#define MAX_IMPACTO_DISPAROS_PEGAMENTO 35
#define MAX_IMPACTO_DISPAROS_MOVIMIENTO 35

enum enumEstadosTower {GREEN,ORANGE,RED};
enum enumTipoDisparo {T_NONE,T_PEGAMENTO,T_NORMAL};
enum levels { LVL1, LVL2, LVL3 };

enum enumWeapons {
	PEGAMENTO,WEAPON1, WEAPON2, WEAPON3, WEAPON4, WEAPON5, WEAPON6, WEAPON7, WEAPON8
};

enum enumEnemyMove {
	STOP,LEFT,RIGHT,UP,DOWN
};

enum weapons { ARMA1, ARMA2, ARMA3, ARMA4, ARMA5, ARMA6, ARMA7, ARMA8, ARMA9 };
enum estadosRobot { STOP_R, ANDAR_TONTO, ANDAR_LISTO,DESTRUIR_TORRE,E_REPAIR };
enum eCellType : uint8 {
	EMPTY, TREE_OLIVE, TREE_POPLAR, TREE_POPLAR_AUTUM, HOUSE_CUTRE, ESTACION_1,
	CORNER_IZQUIERDA_SUP, CORNER_IZQUIERDA_INF, CORNER_DERECHA_SUP, CORNER_DERECHA_INF,
	WALL_SUP, WALL_DER, WALL_IZ, WALL_INF, MINA, PORTAL, TORRETAS_DEFENS, HANGAR_1, HANGAR_2,
	HANGAR_3, HANGAR_4, HANGAR_5, TOWER_COMMU, CURVA_TRAIN, FOREST_1, FOREST_2, MINA_1, MINA_2,
	MINA_3, MINA_4, REFIN_TUBES, ALMACEN, BARRILES,FABRICA,NAVE_1,TRANSFORMADORES,ROOM_1,
	ROOM_2, ROOM_3,PUERTO=39
};

enum eItemType : uint8 {
	NOTHING,
	SWORD,
	POTION
};

struct sCell {
	eCellType type;
	eItemType item;
};

struct sMapHeader {
	int w; //width of map
	int h; //height of map
	unsigned char bytes; //num bytes per cell
	unsigned char extra[7]; //filling bytes, not used
};


//no se usa
struct sParticle {
	Vector3 pos=Vector3(10,0,10);
	Vector3 vel_x;
	Vector3 vel_y;
	float vel_ang;
	float angle;
	float radius;
	sParticle(){ angle = vel_ang = 0.0f; }
};


#endif
