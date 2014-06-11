#pragma once

#include "core/Core.h"

#include <Artemis/Artemis.h>

namespace astro
{

	class RenderSystem;

	class Game
	{

	public:

		Game() {};
		~Game() {};

		void setup();
		void update(float delta);
		void render();
		void shutdown();

	private:

		artemis::World world;
		RenderSystem * renderSystem;

		artemis::Entity * player;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}