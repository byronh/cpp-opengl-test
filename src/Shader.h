#pragma once

#include <string>

namespace astro
{

	class Shader
	{

	public:

		enum ShaderType
		{
			VERTEX,
			GEOMETRY,
			FRAGMENT,
		};
		Shader(const std::string & filePath, ShaderType type);

	private:

		void build(const std::string & code, ShaderType type);

		Shader();
		Shader(const Shader & shader);
		Shader & operator = (const Shader & shader);

	};
}