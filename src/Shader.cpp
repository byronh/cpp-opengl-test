#include "Shader.h"
#include "Exception.h"
#include "Logger.h"

#include <assert.h>
#include <fstream>
#include <sstream>

namespace astro
{
	Shader::Shader(const std::string & relativePath, ShaderType type) :
		handle(0),
		refCount(NULL)
	{
		std::string absolutePath = EXECUTABLE_DIRECTORY + relativePath;

		std::ifstream stream;
		stream.open(absolutePath.c_str(), std::ios::in | std::ios::binary);
		if (!stream.is_open())
		{
			throw astro::Exception(std::string("Failed to open shader file: ") + absolutePath);
		}

		std::stringstream buffer;
		buffer << stream.rdbuf();

		build(buffer.str(), type);

		refCount = new unsigned;
		*refCount = 1;
	}

	Shader::Shader(const Shader & other) :
		handle(other.handle),
		refCount(other.refCount)
	{
		retain();
	}

	Shader & Shader::operator = (const Shader & other)
	{
		release();
		handle = other.handle;
		refCount = other.refCount;
		retain();
		return *this;
	}

	Shader::~Shader()
	{
		if (refCount)
		{
			release();
		}
	}

	GLuint Shader::getHandle() const
	{
		return handle;
	}

	void Shader::build(const std::string & code, ShaderType type)
	{
		GLenum shaderType;

		switch (type)
		{
		case Shader::VERTEX:
			shaderType = GL_VERTEX_SHADER;
			break;
		case Shader::GEOMETRY:
			shaderType = GL_GEOMETRY_SHADER;
			break;
		case Shader::FRAGMENT:
			shaderType = GL_FRAGMENT_SHADER;
			break;
		default:
			throw Exception("Invalid shader type specified");
			break;
		}

		handle = glCreateShader(shaderType);
		if (handle == 0)
		{
			throw Exception("Failed to create shader");
		}

		const char* shaderCode = code.c_str();
		glShaderSource(handle, 1, (const GLchar **)& shaderCode, NULL);
		glCompileShader(handle);

		GLint status;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Failed to compile shader:\n");

			GLint length;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
			char* info = new char[length + 1];
			glGetShaderInfoLog(handle, length, NULL, info);
			msg += info;
			delete[] info;

			glDeleteShader(handle);
			handle = 0;
			throw Exception(msg);
		}
	}

	void Shader::retain()
	{
		assert(refCount);
		*refCount += 1;
	}

	void Shader::release()
	{
		assert(refCount && *refCount > 0);
		*refCount -= 1;
		if (*refCount == 0)
		{
			Logger::debug("Shader deleted");
			glDeleteShader(handle);
			handle = 0;
			delete refCount;
			refCount = NULL;
		}
	}
}