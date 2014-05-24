#pragma once

#include "utils/OpenGL.h"
#include "glm/glm.hpp"

namespace astro
{

	class Program;

	typedef glm::vec3 Vector3f;

	class Game
	{

	public:

		Game() {};
		~Game() {};

		void setup();
		void update() {};
		void render();
		void shutdown() {};

	private:

		GLuint vertexArrayObject;
		GLuint vertexBufferObject;
		
		Program * program;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}