#pragma once

#include "OpenGL.h"

namespace astro
{
	class Program;

	class Game
	{

	public:

		Game() {};
		~Game() {};

		void setup();
		void update();
		void render();
		void shutdown();

	private:

		Program * program;
		GLuint vertexArrayObject;
		GLuint vertexBufferObject;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};
}