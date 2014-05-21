#pragma once

namespace astro
{
	class Program;

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

		Program * program;

		Game(const Game & game);
		Game & operator = (const Game & game);

	};
}