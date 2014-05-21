#include "Game.h"
#include "Exception.h"
#include "Logger.h"

#include "OpenGL.h"
#include <GLFW/glfw3.h>

#include <iostream>

void run()
{
	
	// Initialize GLFW
	GLFWwindow* window;
	if (!glfwInit())
	{
		throw astro::Exception("Failed to initialize GLFW!");
	}

	// Use OpenGL version 3.3 - forward compatibility needed for Mac OS X
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create GLFW window as OpenGL context
	window = glfwCreateWindow(1280, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw astro::Exception("Failed to create window! Your hardware must support OpenGL 3.3 or higher.");
	}
	glfwMakeContextCurrent(window);

	// Enable vertical sync
	glfwSwapInterval(1);

	// Load OpenGL extensions via glLoadGen
	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		throw astro::Exception("Failed to load extensions for OpenGL 3.3!");
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	astro::Game game;
	game.setup();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		game.update();
		game.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Shut down
	game.shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(void)
{
	try
	{
		run();
	}
	catch (astro::Exception & e)
	{
		astro::Logger::error(e.what());
		astro::Logger::error("Press [ENTER] to continue...");
		std::cin.get();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}