#include "Stage.h"



void Stage::render()
{

}


void Stage::init()
{

}


void Stage::update(double seconds_elapsed)
{

}



void Stage::renderUI(int cuadrante, Texture* tex) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	Mesh quad;

	if (cuadrante == 0) {
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));

		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));

	}
	else if (cuadrante == 1) {
		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));

		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(1, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (cuadrante == 2) {
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(-1, 1, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 1, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (cuadrante == 3) {
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(-1, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(-1, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(1, 1));
	}
	else if (cuadrante == 4) {
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(0, -1, 0));
		quad.uvs.push_back(Vector2(0, 0));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(0, 0, 0));
		quad.uvs.push_back(Vector2(0, 1));
		quad.vertices.push_back(Vector3(1, -1, 0));
		quad.uvs.push_back(Vector2(1, 0));
		quad.vertices.push_back(Vector3(1, 0, 0));
		quad.uvs.push_back(Vector2(1, 1));

	}
	Shader* shader = Shader::Get("data/shaders/quad.vs", "data/shaders/texture old.fs");//flat.fs");
	shader->enable();
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_texture", tex, 0);
	shader->setFloat("u_opacity", 0.5f);
	quad.render(GL_TRIANGLES);
	shader->disable();
}