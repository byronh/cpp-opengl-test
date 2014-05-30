#pragma once

#include "core/Core.h"

#define NUM_INSTANCES 6

namespace astro
{

	class Camera;
	class Model;
	class Program;

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

		Camera * camera;
		Model * model;
		Program * program;

		Matrix4f world[NUM_INSTANCES];
		Matrix4f modelViewProjection[NUM_INSTANCES];

		Handle uTexture;
		
		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}