#ifndef IMAGE_H
#define IMAGE_H


#include <cstring>

#include "Trash.h"
#include "Vectors.h"


enum PixelFormat
{
	G8, // Note (Viet Nguyen): Grayscale
	RGB8,
	RGBA8,
	RGB10A2 // Note (Viet Nguyen): Used for HDR
};


// Map the pixel format enumeration to its pixel data size in bytes
inline unsigned int PixelDataSize(PixelFormat pixelFormat)
{
	switch( pixelFormat )
	{
	case G8:
		return 1;
	case RGB8:
		return 3;
	case RGBA8:
	case RGB10A2:
		return 4;
	default:
		return 0;
	}
}


// This class is a generalization of a 2D image of varying pixel format. This class directly holds the pixel data in a byte array. The image can be constructed directly or initialized post-construction. The post-construction initialization of the data array is for image loading derived classes of Image. Note that this class is marked (derived from) as Trash to be picked up when the world is destructed.
class Image : public Trash
{
public:

	Image();
	Image(unsigned int width, unsigned int height, PixelFormat pixelFormat);
	Image(Vector2ui size, PixelFormat pixelFormat);
	Image(Image& other);

	virtual ~Image();

	void Initialize(unsigned int width, unsigned int height, PixelFormat pixelFormat);
	
	bool IsValid();

	Vector2ui GetSize();

	PixelFormat GetPixelFormat();

	void SwitchRedBlue();

	unsigned int GetDataSize();

	unsigned char* GetData();

	void SetPixelColor(unsigned int x, unsigned int y, float* colorArray);
	void SetPixelColor(Vector2ui pos, float* colorArray);

	unsigned char* GetPixelColor(unsigned int x, unsigned int y);
	unsigned char* GetPixelColor(Vector2ui pos);

protected:

	Vector2ui		_size;

	PixelFormat		_pixelFormat;
	unsigned int	_pixelDataSize;
	unsigned int	_dataSize;

	unsigned char*	_data;
};


#endif // IMAGE_H