#pragma once

#include "../utils/OpenGL.h"

#include <memory>
#include <string>
#include <vector>

namespace astro
{

	class Shader
	{

	public:

		typedef std::vector<Shader> vector;
		enum ShaderType
		{
			SHADERTYPE_VERTEX,
			SHADERTYPE_GEOMETRY,
			SHADERTYPE_FRAGMENT,
		};
		Shader(const std::string & filePath, ShaderType type);
		Shader(const Shader & other);
		Shader & operator = (const Shader & other);
		~Shader();

		GLuint getHandle() const;

	private:

		// TODO hide implementation
		GLuint handle;
		unsigned * refCount;

		void build(const std::string & code, ShaderType type);

		Shader();
		void retain();
		void release();

	};

}