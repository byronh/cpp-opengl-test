#pragma once

#include "../core/Core.h"

#include <string>

namespace astro
{

	class Texture
	{

	public:

		enum TextureType
		{
			TEXTURETYPE_2D
		};

		Texture(const std::string & relativePath, TextureType type);
		~Texture();

		Handle getHandle();
		void bind(unsigned int unit);
		void unbind();

	private:

		Handle handle;
		GLenum target;

	};

}