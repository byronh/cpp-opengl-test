#pragma once

#include "core/Core.h"

namespace astro
{

	class Program;
	class Camera;

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

		Program * program;
		Camera * camera;

		Matrix4f model;
		Matrix4f MVP;

		Handle MVPuniform;

		Handle vertexArrayObject;
		Handle vertexBufferObject;
		Handle indexBufferObject;
		
		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}