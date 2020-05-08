#ifndef ENUMSTRUCTS_H
#define ENUMSTRUCTS_H

#define NUM_ENTITIES 4

enum eCellType : uint8 {
	EMPTY,TREE_ONE,TREE_TWO,TREE_TRHE,HOUSE_1
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





#endif 