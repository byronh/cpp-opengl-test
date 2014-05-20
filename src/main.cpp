#include <iostream>

#include "gl_core_3_3.h"
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>


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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (ogl_LoadFunctions() == ogl_LOAD_SUCCEEDED)
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.0f, 0.5f, 0.25f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}