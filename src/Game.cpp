#include "Game.h"

#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Program.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL.h>

namespace astro
{

	void Game::setup()
	{
		// Build shader program
		program = new Program("basic.vert.glsl", "basic.frag.glsl");
		MVPuniform = program->getUniformLocation("MVP");

		// Setup camera
		camera = new Camera(
			glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f),
			glm::lookAt(Vector3f(4, 3, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0))
		);

		MVP = camera->getProjectionMatrix() * camera->getViewMatrix() * model;

		//std::string sphereFile = ASSET_DIR + std::string("phoenix_ugv.md2");
		//Assimp::Importer importer;
		//const aiScene * scene = importer.ReadFile(sphereFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
		//if (scene)
		//{
		//	std::cout << "Success!" << std::endl;
		//}
		//else
		//{
		//	throw Exception("Failed to load " + sphereFile + ": " + importer.GetErrorString());
		//}

		//unsigned char* image;
		//int width, height;
		std::string imageFile = ASSET_DIR + std::string("hazard.png");
		//image = SOIL_load_image(imageFile.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

		Handle tex = SOIL_load_OGL_texture(imageFile.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		if (tex == 0)
		{
			throw Exception(std::string("Failed to load image! ") + SOIL_last_result());
		}

		// Create mesh
		Vertex vertices[3];
		vertices[0].position = Vector3f(-1.0f, -1.0f, 0.0f);
		vertices[1].position = Vector3f(1.0f, -1.0f, 0.0f);
		vertices[2].position = Vector3f(0.0f, 1.0f, 0.0f);
		vertices[0].texture = Vector2f(0.0f, 0.0f);
		vertices[1].texture = Vector2f(1.0f, 0.0f);
		vertices[2].texture = Vector2f(0.5f, 1.0f);

		unsigned int indices[3] = { 0, 1, 2 };

		VertexBuffer vb(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
		IndexBuffer ib(indices, indices + sizeof(indices) / sizeof(indices[0]));

		mesh = new Mesh(vb, ib);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void Game::update(float delta)
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program->begin();
		{
			glUniformMatrix4fv(MVPuniform, 1, GL_FALSE, &MVP[0][0]);
			mesh->render();
		}
		program->end();
	}

	void Game::shutdown()
	{
		delete camera;
		delete mesh;
		delete program;
	}
}