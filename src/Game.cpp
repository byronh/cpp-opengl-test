#include "Game.h"
#include "Shader.h"
#include "Program.h"

namespace astro
{
	void Game::setup()
	{
		// Load shaders
		Shader vert("basic.vert.glsl", Shader::VERTEX);
		Shader frag("basic.frag.glsl", Shader::FRAGMENT);

		Shader::vector shaders;
		shaders.push_back(vert);
		shaders.push_back(frag);

		program = new Program(shaders);

		// Create triangle
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

		GLfloat vertexData[] = {
			0.0f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(program->getAttribute("vert"));
		glVertexAttribPointer(program->getAttribute("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Game::update()
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program->getHandle());
		{
			glBindVertexArray(vertexArrayObject);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}
		glUseProgram(0);
	}

	void Game::shutdown()
	{

	}
}