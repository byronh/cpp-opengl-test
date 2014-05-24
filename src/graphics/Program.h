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

		void begin();
		void end();

		Handle getHandle() const;
		Uniform getUniform(const std::string & name) const;

		//void setUniform1f()

	private:

		Handle handle;
		
		Program();
		Program(const Program & other);
		const Program & operator = (const Program & other);

		bool active;

	};

}