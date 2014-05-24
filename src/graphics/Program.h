#pragma once

#include "Shader.h"
#include <vector>

namespace astro
{

	class Program
	{

	public:

		Program(const std::vector<Shader> & shaders);
		~Program();

		GLuint getHandle() const;

	private:

		GLuint handle;
		
		Program();
		Program(const Program & other);
		const Program & operator = (const Program & other);

	};

}