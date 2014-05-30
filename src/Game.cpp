#include "Game.h"

#include "graphics/Camera.h"
#include "graphics/Model.h"
#include "graphics/Program.h"
#include "graphics/Texture.h"

#include <iostream>

#define NUM_INSTANCES 1

namespace astro
{

	void Game::setup()
	{
		// Build shader program
		program = new Program("basic.vert.glsl", "basic.frag.glsl");
		uModelViewProjection = program->getUniformLocation("u_modelViewProjection");
		uTexture = program->getUniformLocation("u_texture");

		// Setup camera
		camera = new Camera(
			glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f),
			glm::lookAt(Vector3f(150, 100, -150), Vector3f(0, 0, 0), Vector3f(0, 1, 0))
		);

		// Build objects
		mesh = new Model("phoenix_ugv.md2");

		modelViewProjection = camera->getProjectionMatrix() * camera->getViewMatrix() * model;

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
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
			glUniformMatrix4fv(uModelViewProjection, 1, GL_FALSE, &modelViewProjection[0][0]);
			glUniform1i(uTexture, 0);

			Matrix4f WVPMatrices[NUM_INSTANCES];
			Matrix4f WorldMatrices[NUM_INSTANCES];

			for (unsigned int i = 0; i < NUM_INSTANCES; ++i)
			{
				WVPMatrices[i] = glm::transpose(modelViewProjection);
				WorldMatrices[i] = glm::transpose(model);
			}

			mesh->renderMeshes(NUM_INSTANCES, WVPMatrices, WorldMatrices);
		}
		program->end();
	}

	void Game::shutdown()
	{
		delete camera;
		delete mesh;
		delete program;
	}
}