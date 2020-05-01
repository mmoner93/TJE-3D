#ifndef STAGE_H
#define STAGE_H


#include "includes.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"

class Stage
{
public:

	static std::map<std::string, Stage*> s_stages;
	static Stage* current_state;
	bool iniciado;
	bool controlInit;

	static void changeState(const char* name) {
		current_state = s_stages[name];
	}

	Stage(std::string name) {
		iniciado = false;
		controlInit = false;
		s_stages[name] = this;
		if (current_state == NULL) {
			current_state = this;
		}
	}


	Stage* getStage(const char* filename)
	{
		//search image in cache
		auto it = s_stages.find(filename);

		//if found, return it
		if (it != s_stages.end())
			return it->second;

		return NULL;
	}

	virtual void render();
	virtual void update(double dt);
	virtual void init();
	
};


#endif