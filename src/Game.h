#pragma once

namespace astro
{
	class Game
	{

	public:

		Game() {};
		~Game() {};

		void setup();
		void shutdown();
		void update();
		void render();

	private:

		Game(const Game & game);
		Game & operator = (const Game & game);

	};
}