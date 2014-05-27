#pragma once

#include "core/Core.h"

namespace astro
{

	class Program;

	class Game
	{

	public:

		Game() {};
		~Game() {};

		void setup();
		void update(float delta);
		void render();
		void shutdown() {};

	private:

		float scale;
		Handle worldUniform;

		Handle vertexArrayObject;
		Handle vertexBufferObject;
		Handle indexBufferObject;
		
		Program * program;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}