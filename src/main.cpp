#include <iostream>
#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>

#include "Exception.h"


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
	window = glfwCreateWindow(256, 128, "Hello World", NULL, NULL);
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

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Shut down
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
		std::cerr << e.what() << std::endl;
		std::cerr << "Press any key to continue... ";
		std::cin.get();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}