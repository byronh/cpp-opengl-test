#pragma once

#include "../core/Core.h"

#include "Shader.h"

#include <string>

namespace astro
{

	class Program
	{

	public:

		Program(const std::string & vertexShaderFile, const std::string & fragmentShaderFile);
		~Program();

		void begin();
		void end();

		const Handle getHandle() const;
		const Handle getUniformLocation(const std::string & name) const;

	private:

		bool active;
		Handle handle;

		void init(const Shader::Array & shaders);
		
		Program();
		Program(const Program & other);
		const Program & operator = (const Program & other);

	};

}