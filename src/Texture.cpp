#include "Texture.h"
#include "Exception.h"

namespace astro
{

	static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
	{
		switch (format)
		{
		case Bitmap::FORMAT_GRAYSCALE:
			return GL_RED;
		case Bitmap::FORMAT_GRAYSCALE_ALPHA:
			return GL_RG;
		case Bitmap::FORMAT_RGB:
			return GL_RGB;
		case Bitmap::FORMAT_RGBA:
			return GL_RGBA;
		default:
			throw Exception("Invalid bitmap format");
		}
	}

	Texture::Texture(const Bitmap& bitmap, GLint minMagFilter, GLint wrapMode) :
		originalWidth((GLfloat)bitmap.getWidth()),
		originalHeight((GLfloat)bitmap.getHeight())
	{
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatForBitmapFormat(bitmap.getFormat()), (GLsizei)bitmap.getWidth(), (GLsizei)bitmap.getHeight(),
			0, TextureFormatForBitmapFormat(bitmap.getFormat()), GL_UNSIGNED_BYTE, bitmap.pixelBuffer());
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &handle);
	}

	GLuint Texture::getHandle() const
	{
		return handle;
	}

	GLfloat Texture::getOriginalWidth() const
	{
		return originalWidth;
	}

	GLfloat Texture::getOriginalHeight() const
	{
		return originalHeight;
	}

}