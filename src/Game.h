#pragma once

#include "OpenGL.h"

namespace tdogl
{
	class Program;
}

namespace astro
{

	class Texture;

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

		tdogl::Program * program;
		Texture * texture;

		GLuint vertexArrayObject;
		GLuint vertexBufferObject;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}