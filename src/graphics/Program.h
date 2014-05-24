#pragma once

#include "../core/Core.h"

#include "Shader.h"

namespace astro
{

	class Program
	{

	public:

		Program(const Shader::Array & shaders);
		~Program();

		Handle getHandle() const;

	private:

		Handle handle;
		
		Program();
		Program(const Program & other);
		const Program & operator = (const Program & other);

	};

}