#include <iostream>

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>

#include <cstdio>

int main(void)
{

	std::cout << "Hello World!" << std::endl;
	glm::vec3 vec(0.5f, 0.5f, 0.5f);
	std::cout << "Testing glm: " << glm::to_string(vec) << std::endl;
	std::cout << "Press [Enter] to open a GLFW window..." << std::endl;
	std::cin.get();

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(256, 128, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create GLFW window!" << std::endl;
		std::cin.get();
		return -1;
	}

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	if (ogl_LoadFunctions() == ogl_LOAD_SUCCEEDED)
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;

	} else {
		std::cout << "Failed to load ogl functions!" << std::endl;
		std::cin.get();

		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

}