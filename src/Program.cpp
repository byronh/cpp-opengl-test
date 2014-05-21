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

	GLint Program::getAttribute(const GLchar* attributeName) const
	{
		if (!attributeName)
		{
			throw Exception("Attribute name must not be null");
		}

		GLint attrib = glGetAttribLocation(handle, attributeName);

		if (attrib == -1)
		{
			throw Exception(std::string("Program attribute not found: ") + attributeName);
		}

		return attrib;
	}

	GLint Program::getUniform(const GLchar* uniformName) const
	{
		if (!uniformName)
		{
			throw Exception("Uniform name must not be null");
		}

		GLint uniform = glGetUniformLocation(handle, uniformName);

		if (uniform == -1)
		{
			throw Exception(std::string("Program uniform not found: ") + uniformName);
		}

		return uniform;
	}
}