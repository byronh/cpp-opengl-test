#include "Game.h"

#include "graphics/Program.h"

#include <iostream>

#include "SOIL.h"

namespace astro
{

	void Game::setup()
	{
		// Build shader program
		Shader::Array shaders;

		Shader vertexShader("basic.vert.glsl", Shader::SHADERTYPE_VERTEX);
		Shader fragmentShader("basic.frag.glsl", Shader::SHADERTYPE_FRAGMENT);

		shaders.push_back(vertexShader);
		shaders.push_back(fragmentShader);

		program = new Program(shaders);

		// Get uniform
		scale = 0.0f;
		worldUniform = program->getUniformLocation("gWorld");

		// Draw triangle
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
		scale += 1.0f * delta;
	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4f World;

		World[0][0] = 1.0f; World[0][1] = 0.0f; World[0][2] = 0.0f; World[0][3] = glm::sin(scale);
		World[1][0] = 0.0f; World[1][1] = 1.0f; World[1][2] = 0.0f; World[1][3] = 0.0f;
		World[2][0] = 0.0f; World[2][1] = 0.0f; World[2][2] = 1.0f; World[2][3] = 0.0f;
		World[3][0] = 0.0f; World[3][1] = 0.0f; World[3][2] = 0.0f; World[3][3] = 1.0f;

		program->begin();
		{
			glUniformMatrix4fv(worldUniform, 1, GL_TRUE, &World[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
		}
		program->end();
	}
}