#include "Game.h"

#include "graphics/Program.h"

namespace astro
{

	void Game::setup()
	{
		Shader::Array shaders;

		Shader vertexShader("basic.vert.glsl", Shader::SHADERTYPE_VERTEX);
		Shader fragmentShader("basic.frag.glsl", Shader::SHADERTYPE_FRAGMENT);

		shaders.push_back(vertexShader);
		shaders.push_back(fragmentShader);

		program = new Program(shaders);


		Vector3f vertices[3];
		vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
		vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
		vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void Game::update(float delta)
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program->getHandle());
		{
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
		}
		glUseProgram(0);
	}
}