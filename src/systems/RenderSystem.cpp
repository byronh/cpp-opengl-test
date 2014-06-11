#include "RenderSystem.h"

#include "../graphics/Camera.h"
#include "../graphics/Model.h"
#include "../graphics/Program.h"

#include <iostream>

namespace astro
{

	RenderSystem::RenderSystem()
	{
		this->addComponentType<RenderComponent>();
	}

	RenderSystem::~RenderSystem()
	{
		delete _camera;
		delete _model;
		delete _program;
	}
	
	void RenderSystem::initialize()
	{
		_renderMapper.init(*world);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		_camera = new Camera(
			glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f),
			glm::lookAt(Vector3f(175, 125, -175), Vector3f(0, 0, 0), Vector3f(0, 1, 0))
		);

		_program = new Program("basic.vert.glsl", "basic.frag.glsl");

		_model = new Model("phoenix_ugv.md2");

		for (int i = 0; i < NUM_INSTANCES; ++i)
		{
			worldMatrices[i] = glm::translate(worldMatrices[i], Vector3f((i - NUM_INSTANCES / 2) * 100, 0, 0));
			modelViewProjectionMatrices[i] = _camera->getCombinedMatrix() * worldMatrices[i];
		}
	}

	void RenderSystem::begin()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_program->begin();
	}

	void RenderSystem::processEntity(artemis::Entity & e)
	{
		_model->renderMeshes(NUM_INSTANCES, modelViewProjectionMatrices, worldMatrices);
	}

	void RenderSystem::end()
	{
		_program->end();
	}

}