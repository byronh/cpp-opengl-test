#pragma once

#include "Shader.h"
#include "OpenGL.h"

namespace astro
{
	class Program
	{

	public:

		Program(const Shader::vector & shaders);
		~Program();

		GLuint getHandle() const;
		GLint getAttribute(const GLchar* attributeName) const;
		GLint getUniform(const GLchar* uniformName) const;

	private:

		// TODO hide implementation
		GLuint handle;

		Program();
		Program(const Program & program);
		Program & operator = (const Program & program);

	};
}