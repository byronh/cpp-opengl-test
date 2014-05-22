#include "Game.h"
#include "Shader.h"
#include "Program.h"
#include "Texture.h"

namespace astro
{
	void Game::setup()
	{
		// Load shaders
		Shader vert("basic.vert.glsl", Shader::SHADERTYPE_VERTEX);
		Shader frag("basic.frag.glsl", Shader::SHADERTYPE_FRAGMENT);

		Shader::vector shaders;
		shaders.push_back(vert);
		shaders.push_back(frag);

		program = new tdogl::Program(shaders);

		// Load texture
		Bitmap bmp = Bitmap::bitmapFromFile("hazard.png");
		bmp.flipVertically();
		texture = new Texture(bmp);

		// Create triangle
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

		// Put the three triangle vertices (XYZ) and texture coordinates (UV) into the VBO
		GLfloat vertexData[] = {
			//  X     Y     Z       U     V
			0.0f, 0.8f, 0.0f, 0.5f, 1.0f,
			-0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
			0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// connect the xyz to the "vert" attribute of the vertex shader
		glEnableVertexAttribArray(program->attrib("vert"));
		glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

		// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
		glEnableVertexAttribArray(program->attrib("vertTexCoord"));
		glVertexAttribPointer(program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		// unbind the VAO
		glBindVertexArray(0);
	}

	void Game::update()
	{

	}

	void Game::render()
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program->use();
		{
			// bind the texture and set the "tex" uniform in the fragment shader
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getHandle());
			program->setUniform("tex", 0); //set to 0 because the texture is bound to GL_TEXTURE0

			// bind the VAO (the triangle)
			glBindVertexArray(vertexArrayObject);

			// draw the VAO
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// unbind the VAO, the program and the texture
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		program->stopUsing();
	}

	void Game::shutdown()
	{

	}
}