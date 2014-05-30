#include "Texture.h"

#include <iostream>
#include <SOIL.h>

namespace astro
{

	// TODO manage textures
	Texture::Texture(const std::string & relativePath, TextureType type) :
		handle(0)
	{
		switch (type)
		{
		case Texture::TEXTURETYPE_2D:
			target = GL_TEXTURE_2D;
			break;
		default:
			throw Exception("Invalid texture type specified");
		}

		std::string absolutePath = ASSET_DIR + relativePath;

		handle = SOIL_load_OGL_texture(absolutePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		if (handle == 0)
		{
			std::string message("Failed to load image ");
			message += absolutePath + ":\n" + SOIL_last_result();
			throw Exception(message);
		}

		std::cout << "Successfully loaded texture " << relativePath << std::endl;
		unbind();
	}

	Texture::~Texture()
	{
		unbind();
		glDeleteTextures(1, &handle);
	}

	Handle Texture::getHandle()
	{
		return handle;
	}

	void Texture::bind(unsigned int unit)
	{
		if (unit < 0 && unit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
		{
			throw Exception("Attempted to set an invalid texture unit");
		}
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, handle);
	}

	void Texture::unbind()
	{
		glBindTexture(target, 0);
	}

}