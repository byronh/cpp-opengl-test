#include "Game.h"

#include "graphics/Camera.h"
#include "graphics/Model.h"
#include "graphics/Program.h"

#include <iostream>

namespace astro
{

	void Game::setup()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Build shader program
		program = new Program("basic.vert.glsl", "basic.frag.glsl");
		//uTexture = program->getUniformLocation("u_texture");

		// Setup camera
		camera = new Camera(
			glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f),
			glm::lookAt(Vector3f(175, 125, -175), Vector3f(0, 0, 0), Vector3f(0, 1, 0))
		);

		// Build objects
		model = new Model("phoenix_ugv.md2");

		for (int i = 0; i < NUM_INSTANCES; ++i)
		{
			world[i] = glm::translate(world[i], Vector3f((i-NUM_INSTANCES/2) * 100, 0, 0));
			modelViewProjection[i] = camera->getProjectionMatrix() * camera->getViewMatrix() * world[i];
		}
		
	}

	void Game::update(float delta)
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program->begin();
		{
			model->renderMeshes(NUM_INSTANCES, modelViewProjection, world);
		}
		program->end();
	}

	void Game::shutdown()
	{
		delete camera;
		delete model;
		delete program;
	}
}