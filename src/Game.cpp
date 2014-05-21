#include "Game.h"
#include "OpenGL.h"
#include "Shader.h"
#include "Program.h"

namespace astro
{
	void Game::setup()
	{
		Shader vert("/shaders/basic.vert.glsl", Shader::VERTEX);
		Shader frag("/shaders/basic.frag.glsl", Shader::FRAGMENT);

		Shader::vector shaders;
		shaders.push_back(vert);
		shaders.push_back(frag);

		program = new Program(shaders);
	}

	void Game::shutdown()
	{

	}

	void Game::update()
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}