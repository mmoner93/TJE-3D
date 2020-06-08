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
	Texture* textureGreen;
	Texture* textureOrange;
	Texture* textureRed;
	bool shooted = false;
	float time_Shooted = 3.0;
	EntityTowerArreglo( Texture* t1, Texture* t2, Texture* t3, Shader* s, Mesh* m, Material* mat, std::string nS, float sc = 1.0, float til = 1.0) :EntityGameObject(t3, s, m, mat, nS, sc, til) {
		disparoMeshPegamento = Mesh::Get("data/impactos/impactoPegamento.OBJ");
		disparoPegamentoTexture = Texture::Get("data/impactos/impactogris.png");
		textureGreen = t1;
		textureOrange = t2;
		textureRed = t3;
	}

	 void render(Light* light);
	 void update(float seconds_elapsed);
	 void onReceveidShootPegamento(Vector3 temp, Vector3 norm);
	 void switchLight();
	 void changeTime(float seconds_elapsed);
	 void breakTower();
};


#endif 