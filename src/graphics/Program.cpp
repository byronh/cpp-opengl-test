#include "Program.h"
#include "../core/Exception.h"

namespace astro
{

	Program::Program(const std::vector<astro::Shader> & shaders) :
		handle(0)
	{
		if (shaders.size() <= 0)
		{
			throw Exception("Must provide at least one shader to create a program");
		}

		handle = glCreateProgram();
		if (handle == 0)
		{
			throw Exception("Failed to create program");
		}

		for (unsigned i=0; i<shaders.size(); ++i)
		{
			glAttachShader(handle, shaders[i].getHandle());
		}

		glLinkProgram(handle);

		for (unsigned i=0; i<shaders.size(); ++i)
		{
			glDetachShader(handle, shaders[i].getHandle());
		}

		GLint status;
		glGetProgramiv(handle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Failed to link program: ");

			GLint length;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
			char* log = new char[length + 1];
			glGetProgramInfoLog(handle, length, NULL, log);
			msg += log;
			delete[] log;

			glDeleteProgram(handle);
			handle = 0;
			throw Exception(msg);
		}
	}

	Program::~Program()
	{
		if (handle != 0)
		{
			glDeleteProgram(handle);
		}
	}

	GLuint Program::getHandle() const
	{
		return handle;
	}

}