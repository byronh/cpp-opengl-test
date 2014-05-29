#include "Game.h"

#include "graphics/Camera.h"
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

		MVPuniform = program->getUniformLocation("MVP");

		// Setup camera
		camera = new Camera(
			glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f),
			glm::lookAt(Vector3f(3, 4, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0))
		);

		MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * model;

		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		Vector3f vertices[3];
		vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
		vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
		vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

		unsigned int indices[] = {0, 1, 2};

		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &indexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
			glUniformMatrix4fv(MVPuniform, 1, GL_TRUE, &MVP[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

			glDisableVertexAttribArray(0);
		}
		program->end();
	}

	void Game::shutdown()
	{
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteBuffers(1, &vertexArrayObject);
		glDeleteBuffers(1, &indexBufferObject);

		delete camera;
		delete program;
	}
}