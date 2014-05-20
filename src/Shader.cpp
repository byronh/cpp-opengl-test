#include "Shader.h"
#include "Exception.h"
#include "OpenGL.h"

#include <fstream>
#include <sstream>

namespace astro
{
	Shader::Shader(const std::string & relativePath, ShaderType type)
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
			throw Exception("Invalid ShaderType specified");
			break;
		}

		GLuint shader = glCreateShader(shaderType);
		if (shader == 0)
		{
			throw Exception("Failed to create shader");
		}

		const char* shaderCode = code.c_str();
		glShaderSource(shader, 1, (const GLchar **)& shaderCode, NULL);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("Failed to compile shader:\n");

			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* info = new char[length + 1];
			glGetShaderInfoLog(shader, length, NULL, info);
			msg += info;
			delete[] info;

			glDeleteShader(shader);
			shader = 0;
			throw Exception(msg);
		}
	}
}