#pragma once

#include "../utils/OpenGL.h"
#include "Bitmap.h"

namespace astro
{

	class Texture
	{

	public:

		/**
		Creates a texture from a bitmap.

		The texture will be loaded upside down because tdogl::Bitmap pixel data
		is ordered from the top row down, but OpenGL expects the data to
		be from the bottom row up.

		@param bitmap  The bitmap to load the texture from
		@param minMagFiler  GL_NEAREST or GL_LINEAR
		@param wrapMode GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER
		*/
		Texture(const Bitmap & bitmap, GLint minMagFilter = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);
		~Texture();

		GLuint getHandle() const;
		GLfloat getOriginalWidth() const;
		GLfloat getOriginalHeight() const;

	private:

		GLuint handle;
		GLfloat originalWidth;
		GLfloat originalHeight;

		Texture(const Texture & other);
		const Texture & operator=(const Texture & other);
	};

}