#include "Game.h"
#include "OpenGL.h"
#include "Shader.h"

namespace astro
{
	void Game::setup()
	{
		Shader* shader = new Shader("/shaders/basic.vert.glsl", Shader::VERTEX);
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