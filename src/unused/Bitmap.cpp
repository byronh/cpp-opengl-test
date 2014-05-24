#include "Bitmap.h"
#include "../core/Exception.h"
#include "../utils/stb_image.h"

namespace astro
{

	inline unsigned char AverageRGB(unsigned char rgb[3])
	{
		return (unsigned char)(((double)rgb[0] + (double)rgb[1] + (double)rgb[2]) / 3.0);
	}

	static void Grayscale2GrayscaleAlpha(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = 255;
	}

	static void Grayscale2RGB(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[0];
		dest[2] = src[0];
	}

	static void Grayscale2RGBA(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[0];
		dest[2] = src[0];
		dest[3] = 255;
	}

	static void GrayscaleAlpha2Grayscale(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
	}

	static void GrayscaleAlpha2RGB(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[0];
		dest[2] = src[0];
	}

	static void GrayscaleAlpha2RGBA(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[0];
		dest[2] = src[0];
		dest[3] = src[1];
	}

	static void RGB2Grayscale(unsigned char* src, unsigned char* dest)
	{
		dest[0] = AverageRGB(src);
	}

	static void RGB2GrayscaleAlpha(unsigned char* src, unsigned char* dest)
	{
		dest[0] = AverageRGB(src);
		dest[1] = 255;
	}

	static void RGB2RGBA(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[1];
		dest[2] = src[2];
		dest[3] = 255;
	}

	static void RGBA2Grayscale(unsigned char* src, unsigned char* dest)
	{
		dest[0] = AverageRGB(src);
	}

	static void RGBA2GrayscaleAlpha(unsigned char* src, unsigned char* dest)
	{
		dest[0] = AverageRGB(src);
		dest[1] = src[3];
	}

	static void RGBA2RGB(unsigned char* src, unsigned char* dest)
	{
		dest[0] = src[0];
		dest[1] = src[1];
		dest[2] = src[2];
	}

	typedef void(*FormatConverterFunc)(unsigned char*, unsigned char*);

	static FormatConverterFunc ConverterFuncForFormats(Bitmap::Format srcFormat, Bitmap::Format destFormat)
	{
		if (srcFormat == destFormat)
			throw Exception("Just use memcpy if pixel formats are the same");

		switch (srcFormat)
		{

		case Bitmap::FORMAT_GRAYSCALE:
			switch (destFormat)
			{
			case Bitmap::FORMAT_GRAYSCALE_ALPHA: return Grayscale2GrayscaleAlpha;
			case Bitmap::FORMAT_RGB:            return Grayscale2RGB;
			case Bitmap::FORMAT_RGBA:           return Grayscale2RGBA;
			default:
				throw Exception("Unhandled bitmap format");
			}
			break;

		case Bitmap::FORMAT_GRAYSCALE_ALPHA:
			switch (destFormat)
			{
			case Bitmap::FORMAT_GRAYSCALE: return GrayscaleAlpha2Grayscale;
			case Bitmap::FORMAT_RGB:       return GrayscaleAlpha2RGB;
			case Bitmap::FORMAT_RGBA:      return GrayscaleAlpha2RGBA;
			default:
				throw Exception("Unhandled bitmap format");
			}
			break;

		case Bitmap::FORMAT_RGB:
			switch (destFormat)
			{
			case Bitmap::FORMAT_GRAYSCALE:      return RGB2Grayscale;
			case Bitmap::FORMAT_GRAYSCALE_ALPHA: return RGB2GrayscaleAlpha;
			case Bitmap::FORMAT_RGBA:           return RGB2RGBA;
			default:
				throw Exception("Unhandled bitmap format");
			}
			break;

		case Bitmap::FORMAT_RGBA:
			switch (destFormat)
			{
			case Bitmap::FORMAT_GRAYSCALE:      return RGBA2Grayscale;
			case Bitmap::FORMAT_GRAYSCALE_ALPHA: return RGBA2GrayscaleAlpha;
			case Bitmap::FORMAT_RGB:            return RGBA2RGB;
			default:
				throw Exception("Unhandled bitmap format");
			}
			break;

		default:
			throw Exception("Unhandled bitmap format");
		}
	}

	inline unsigned GetPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Bitmap::Format format)
	{
		return (row*width + col)*format;
	}

	inline bool RectsOverlap(unsigned srcCol, unsigned srcRow, unsigned destCol, unsigned destRow, unsigned width, unsigned height)
	{
		unsigned colDiff = srcCol > destCol ? srcCol - destCol : destCol - srcCol;
		if (colDiff < width)
			return true;

		unsigned rowDiff = srcRow > destRow ? srcRow - destRow : destRow - srcRow;
		if (rowDiff < height)
			return true;

		return false;
	}

	Bitmap::Bitmap(unsigned width,
		unsigned height,
		Format format,
		const unsigned char* pixels) :
		_pixels(NULL)
	{
		_set(width, height, format, pixels);
	}

	Bitmap::~Bitmap()
	{
		if (_pixels) free(_pixels);
	}

	Bitmap Bitmap::bitmapFromFile(std::string relativePath)
	{
		std::string absolutePath = ASSET_DIR + relativePath;

		int width, height, channels;
		unsigned char* pixels = stbi_load(absolutePath.c_str(), &width, &height, &channels, 0);
		if (!pixels) throw Exception(stbi_failure_reason());

		Bitmap bmp(width, height, (Format)channels, pixels);
		stbi_image_free(pixels);
		return bmp;
	}

	Bitmap::Bitmap(const Bitmap& other) :
		_pixels(NULL)
	{
		_set(other._width, other._height, other._format, other._pixels);
	}

	Bitmap& Bitmap::operator = (const Bitmap& other)
	{
		_set(other._width, other._height, other._format, other._pixels);
		return *this;
	}

	unsigned int Bitmap::getWidth() const
	{
		return _width;
	}

	unsigned int Bitmap::getHeight() const
	{
		return _height;
	}

	Bitmap::Format Bitmap::getFormat() const
	{
		return _format;
	}

	unsigned char* Bitmap::pixelBuffer() const
	{
		return _pixels;
	}

	unsigned char* Bitmap::getPixel(unsigned int column, unsigned int row) const
	{
		if (column >= _width || row >= _height)
			throw Exception("Pixel coordinate out of bounds");

		return _pixels + GetPixelOffset(column, row, _width, _height, _format);
	}

	void Bitmap::setPixel(unsigned int column, unsigned int row, const unsigned char* pixel)
	{
		unsigned char* myPixel = getPixel(column, row);
		memcpy(myPixel, pixel, _format);
	}

	void Bitmap::flipVertically()
	{
		unsigned long rowSize = _format*_width;
		unsigned char* rowBuffer = new unsigned char[rowSize];
		unsigned halfRows = _height / 2;

		for (unsigned rowIdx = 0; rowIdx < halfRows; ++rowIdx)
		{
			unsigned char* row = _pixels + GetPixelOffset(0, rowIdx, _width, _height, _format);
			unsigned char* oppositeRow = _pixels + GetPixelOffset(0, _height - rowIdx - 1, _width, _height, _format);

			memcpy(rowBuffer, row, rowSize);
			memcpy(row, oppositeRow, rowSize);
			memcpy(oppositeRow, rowBuffer, rowSize);
		}

		delete rowBuffer;
	}

	void Bitmap::rotate90CounterClockwise()
	{
		unsigned char* newPixels = (unsigned char*)malloc(_format*_width*_height);

		for (unsigned row = 0; row < _height; ++row)
		{
			for (unsigned col = 0; col < _width; ++col)
			{
				unsigned srcOffset = GetPixelOffset(col, row, _width, _height, _format);
				unsigned destOffset = GetPixelOffset(row, _width - col - 1, _height, _width, _format);
				memcpy(newPixels + destOffset, _pixels + srcOffset, _format); //copy one pixel
			}
		}

		free(_pixels);
		_pixels = newPixels;

		unsigned swapTmp = _height;
		_height = _width;
		_width = swapTmp;
	}

	void Bitmap::copyRectFromBitmap(const Bitmap& src,
		unsigned srcCol,
		unsigned srcRow,
		unsigned destCol,
		unsigned destRow,
		unsigned width,
		unsigned height)
	{
		if (srcCol == 0 && srcRow == 0 && width == 0 && height == 0)
		{
			width = src.getWidth();
			height = src.getHeight();
		}

		if (width == 0 || height == 0)
			throw Exception("Can't copy zero height/width rectangle");

		if (srcCol + width >= src.getWidth() || srcRow + height >= src.getHeight())
			throw Exception("Rectangle doesn't fit within source bitmap");

		if (destCol + width >= _width || destRow + height >= _height)
			throw Exception("Rectangle doesn't fit within destination bitmap");

		if (_pixels == src._pixels && RectsOverlap(srcCol, srcRow, destCol, destRow, width, height))
			throw Exception("Source and destination are the same bitmap, and rects overlap. Not allowed!");

		FormatConverterFunc converter = NULL;
		if (_format != src._format)
			converter = ConverterFuncForFormats(_format, src._format);

		for (unsigned row = 0; row < height; ++row)
		{
			for (unsigned col = 0; col < width; ++col)
			{
				unsigned char* srcPixel = src._pixels + GetPixelOffset(srcCol + col, srcRow + row, src._width, src._height, src._format);
				unsigned char* destPixel = _pixels + GetPixelOffset(destCol + col, destRow + row, _width, _height, _format);

				if (converter)
				{
					converter(srcPixel, destPixel);
				}
				else
				{
					memcpy(destPixel, srcPixel, _format);
				}
			}
		}
	}

	void Bitmap::_set(unsigned width,
		unsigned height,
		Format format,
		const unsigned char* pixels)
	{
		if (width == 0) throw Exception("Zero width bitmap");
		if (height == 0) throw Exception("Zero height bitmap");
		if (format <= 0 || format > 4) throw Exception("Invalid bitmap format");

		_width = width;
		_height = height;
		_format = format;

		size_t newSize = _width * _height * _format;
		if (_pixels)
		{
			_pixels = (unsigned char*)realloc(_pixels, newSize);
		}
		else
		{
			_pixels = (unsigned char*)malloc(newSize);
		}

		if (pixels)
			memcpy(_pixels, pixels, newSize);
	}

}