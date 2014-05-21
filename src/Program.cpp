#include "Program.h"
#include "Exception.h"

namespace astro
{
	Program::Program(const Shader::vector & shaders) : handle(0)
	{
		Shader::vector::size_type size = shaders.size();
		if (size <= 0)
		{
			throw Exception("Must provide at least one shader to create a program");
		}

		handle = glCreateProgram();
		if (handle == 0)
		{
			throw Exception("Failed to create program");
		}

		Shader::vector::const_iterator iter;
		for (iter = shaders.begin(); iter != shaders.end(); ++iter)
		{
			glAttachShader(handle, iter->getHandle());
		}

		glLinkProgram(handle);
		
		for (iter = shaders.begin(); iter != shaders.end(); ++iter)
		{
			glDetachShader(handle, iter->getHandle());
		}

		GLint status;
		glGetProgramiv(handle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Failed to link program:\n");

			GLint length;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
			char* info = new char[length + 1];
			glGetProgramInfoLog(handle, length, NULL, info);
			msg += info;
			delete[] info;

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