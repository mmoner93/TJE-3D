#ifndef ENTITYIMPACTODISPARO_H
#define ENTITYIMPACTODISPARO_H

#include "EntityGameObject.h"

class EntityImpactoDisparo :public EntityGameObject
{
public:

	int id;
	bool in_use;
	Vector3 position;
	Vector3 normPosition;

	EntityImpactoDisparo(int i, Texture* t, Shader* s, Mesh* m, Material* mat, std::string nS, float sc = 1.0, float til = 1.0) :EntityGameObject(t, s, m, mat, nS, sc, til) {
		id = i;
		in_use = false;
	}




};


#endif 