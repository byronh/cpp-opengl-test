#pragma once

#include <string>

namespace astro
{

	enum ShaderType
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT,
	};

	class Shader
	{

	public:

		Shader(const std::string & filePath, ShaderType type);

	private:

		void build(const std::string & code, ShaderType type);

		Shader();
		Shader(const Shader & shader);
		Shader & operator = (const Shader & shader);

	};
}