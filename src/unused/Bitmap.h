#pragma once

#include <string>

namespace astro
{

	class Bitmap
	{

	public:

		enum Format
		{
			FORMAT_GRAYSCALE = 1,
			FORMAT_GRAYSCALE_ALPHA = 2,
			FORMAT_RGB = 3,
			FORMAT_RGBA = 4,
		};

		/**
		Creates a new image with the specified width, height and format.

		Width and height are in pixels. Image will contain random garbage if
		pixels = NULL.
		*/
		Bitmap(unsigned width, unsigned height, Format format, const unsigned char* pixels = NULL);
		Bitmap(const Bitmap & other);
		Bitmap & operator = (const Bitmap& other);
		~Bitmap();

		static Bitmap bitmapFromFile(std::string relativePath);
		unsigned getWidth() const;
		unsigned getHeight() const;
		Format getFormat() const;

		/**
		Pointer to the raw pixel data of the bitmap.

		Each channel is 1 byte. The number and meaning of channels per pixel is specified
		by the `Format` of the image. The pointer points to all the columns of
		the top row of the image, followed by each remaining row down to the bottom.
		i.e. c0r0, c1r0, c2r0, ..., c0r1, c1r1, c2r1, etc
		*/
		unsigned char* pixelBuffer() const;

		/**
		Returns a pointer to the start of the pixel at the given coordinates.

		The size of the pixel depends on the `Format` of the image.
		*/
		unsigned char* getPixel(unsigned int column, unsigned int row) const;

		/**
		Sets the raw pixel data at the given coordinates.

		The size of the pixel depends on the `Format` of the bitmap.
		*/
		void setPixel(unsigned int column, unsigned int row, const unsigned char* pixel);

		/**
		Reverses the row order of the pixels, so the bitmap will be upside down.
		*/
		void flipVertically();

		/**
		Rotates the image 90 degrees counter clockwise.
		*/
		void rotate90CounterClockwise();

		/**
		Copies a rectangular area from the given source bitmap into this bitmap.

		If srcCol, srcRow, width, and height are all zero, the entire source
		bitmap will be copied (full width and height).

		If the source bitmap has a different format to the destination bitmap,
		the pixels will be converted to match the destination format.

		Will throw and exception if the source and destination bitmaps are the
		same, and the source and destination rectangles overlap. If you want to
		copy a bitmap onto itself, then make a copy of the bitmap first.
		*/
		void copyRectFromBitmap(const Bitmap& src, unsigned srcCol, unsigned srcRow, unsigned destCol, unsigned destRow, unsigned width, unsigned height);

	private:
		Format _format;
		unsigned _width;
		unsigned _height;
		unsigned char* _pixels;

		void _set(unsigned width, unsigned height, Format format, const unsigned char* pixels);
		static void _getPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Format format);
	};

}