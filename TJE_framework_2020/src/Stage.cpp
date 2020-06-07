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



void Stage::renderUI(int type, Texture* tex, float opacity,Vector3 positionPoint) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	Mesh quad;

	if (type == 0) {
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
	else if (type == 1) {
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
	else if (type == 2) {
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
	else if (type == 3) {
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
	else if (type == 4) {
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
	else if (type == 5) {
		quad.vertices.push_back(positionPoint);
		quad.uvs.push_back(Vector2(1, 1));

	}

	Shader* shader;
	if (type != 5) {
		shader = Shader::Get("data/shaders/quad.vs", "data/shaders/texture old.fs");//flat.fs");
	}
	else {
		shader = Shader::Get("data/shaders/quad.vs", "data/shaders/flat.fs");//flat.fs");
	}
	
	shader->enable();
	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_texture", tex, 0);
	shader->setFloat("u_opacity", opacity);
	if (type != 5) {
		quad.render(GL_TRIANGLES);
	}
	else {
		quad.render(GL_POINT);
	}
	
	shader->disable();
}