#include "Program.h"

namespace astro
{

	Program::Program(const Shader::Array & shaders) :
		handle(0),
		active(false)
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

		glValidateProgram(handle);
		glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Failed to validate program: ");

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
			if (active) {
				throw Exception("Attempted to delete an active program");
			}
			glDeleteProgram(handle);
		}
	}

	void Program::begin()
	{
		if (active)
		{
			throw Exception("Program already started");
		}
		glUseProgram(handle);
		active = true;
	}

	void Program::end()
	{
		if (!active)
		{
			throw Exception("Must call begin() before end()");
		}
		glUseProgram(0);
		active = false;
	}

	Handle Program::getHandle() const
	{
		return handle;
	}

	Handle Program::getUniformLocation(const std::string & name) const
	{
		Handle location = glGetUniformLocation(handle, name.c_str());
		if (location == -1)
		{
			throw Exception("Invalid uniform location - doesn't exist or may have been removed by optimization");
		}
		return location;
	}

}