#pragma once

#include "utils/OpenGL.h"

namespace astro
{

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

		GLuint vertexArrayObject;
		GLuint vertexBufferObject;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}