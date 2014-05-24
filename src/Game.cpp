#include "Game.h"

#include "glm/vec3.hpp"

#include <iostream>

namespace astro
{
	void Game::setup()
	{
		glm::vec3 vertices[3];
		vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
		vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
		vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void Game::update()
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
	}

	void Game::shutdown()
	{

	}
}