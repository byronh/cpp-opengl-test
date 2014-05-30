#pragma once

#include "core/Core.h"

namespace astro
{

	class Camera;
	class Mesh;
	class Program;
	class Texture;

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
		Mesh * mesh;
		Program * program;
		Texture * texture;

		Matrix4f model;
		Matrix4f modelViewProjection;

		Handle uModelViewProjection;
		Handle uTexture;
		
		Game(const Game & game);
		Game & operator = (const Game & game);

	};

}