#ifndef ENTITYTOWERARREGLO_H
#define ENTITYTOWERARREGLO_H

#include "light.h"
#include "EntityGameObject.h"
#include "enumStructs.h"
class EntityTowerArreglo :public EntityGameObject
{
public:
	enumEstadosTower estado = RED;
	std::vector<Vector3> pointsSPegamento;
	Mesh* disparoMeshPegamento;
	Texture* disparoPegamentoTexture;
	Mesh* meshGreen;
	Mesh* meshOrange;
	Mesh* meshRed;
	Texture* textureGreen;
	Texture* textureOrange;
	Texture* textureRed;

	EntityTowerArreglo( Texture* t1, Texture* t2, Texture* t3, Shader* s, Mesh* m1, Mesh* m2, Mesh* m3, Material* mat, std::string nS, float sc = 1.0, float til = 1.0) :EntityGameObject(t3, s, m3, mat, nS, sc, til) {
		disparoMeshPegamento = Mesh::Get("data/impactos/impactoPegamento.OBJ");
		disparoPegamentoTexture = Texture::Get("data/impactos/impactogris.png");
		meshGreen=m1;
		meshOrange = m2;
		meshRed = m3;
		textureGreen = t1;
		textureOrange = t2;
		textureRed = t3;
	}

	 void render(Light* light);
	 void update(float seconds_elapsed);
	 void onReceveidShootPegamento(Vector3 temp, Vector3 norm);
	 void switchLight();

};


#endif 