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

		Handle vertexArrayObject;
		Handle vertexBufferObject;
		
		Program * program;
		float scale;
		Uniform scaleUniform;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}