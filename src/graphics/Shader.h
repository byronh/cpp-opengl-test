#pragma once

#include "../core/Core.h"

#include <string>
#include <vector>

namespace astro
{

	class Shader
	{

	public:

		typedef std::vector<Shader> Array;

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

		Handle getHandle() const;

	private:

		Handle handle;
		unsigned * refCount;

		void build(const std::string & code, ShaderType type);

		Shader();
		void retain();
		void release();

	};

}