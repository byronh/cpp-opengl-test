#pragma once

#include "../core/Core.h"

#include "Shader.h"

#include <map>

namespace astro
{

	class Program
	{

	public:

		Program(const Shader::Array & shaders);
		~Program();

		void begin();
		void end();

		Handle getHandle() const;
		Handle getUniformLocation(const std::string & name) const;

	private:

		bool active;
		Handle handle;
		
		Program();
		Program(const Program & other);
		const Program & operator = (const Program & other);

	};

}