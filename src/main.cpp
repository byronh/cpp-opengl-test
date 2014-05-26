#include "core/Core.h"

#include "Game.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

void run()
{
	
	// Initialize GLFW
	GLFWwindow* window;
	if (!glfwInit())
	{
		throw astro::Exception("Failed to initialize GLFW!");
	}

	// Use OpenGL version 3.3 - forward compatibility needed for Mac OS X
#ifdef APPLE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

	// Create GLFW window as OpenGL context
	window = glfwCreateWindow(1280, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw astro::Exception("Failed to create window! Your hardware must support OpenGL 3.3 or higher.");
	}
	glfwMakeContextCurrent(window);
	//(window, 2300, 200);

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
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	astro::Game game;
	game.setup();

	double lastTime = glfwGetTime();
	double currentTime = 0;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		if (deltaTime > 0)
		{
			game.update(deltaTime);
		}
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