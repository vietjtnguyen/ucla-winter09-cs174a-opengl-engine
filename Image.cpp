#include <iostream>

#include "Image.h"


using namespace std;


// Construct an invalid blank image (no data array initialized)
Image::Image()
:_size(0, 0)
,_pixelFormat(RGB8)
,_pixelDataSize(0)
,_dataSize(0)
,_data(NULL)
{
#ifdef DEBUG
	cout << "Image constructor " << this << endl;
#endif
}


// Construct a blank image
Image::Image(unsigned int width, unsigned int height, PixelFormat pixelFormat)
:_size(width, height)
,_pixelFormat(pixelFormat)
,_pixelDataSize(0)
,_dataSize(0)
,_data(NULL)
{
	if( this->_size.width > 0 && this->_size.height > 0 )
	{
		this->_pixelDataSize = PixelDataSize(this->_pixelFormat);
		this->_dataSize = this->_pixelDataSize*this->_size.width*this->_size.height;

		this->_data = new unsigned char[this->_dataSize];
		if( this->_data )
		{
			memset(this->_data, 0, this->_dataSize);
		}
		else
		{
			this->_size = 0;
			this->_pixelDataSize = 0;
			this->_dataSize = 0;
			this->_data = NULL;
		}
	}
	else
	{
		this->_size = 0;
		this->_pixelDataSize = 0;
		this->_dataSize = 0;
		this->_data = NULL;
	}
	
#ifdef DEBUG
	cout << "Image constructor " << this << endl;
#endif
}


// Construct a blank image, vector variant
Image::Image(Vector2ui size, PixelFormat pixelFormat)
:_size(size)
,_pixelFormat(pixelFormat)
,_pixelDataSize(0)
,_dataSize(0)
,_data(NULL)
{
	if( this->_size.width > 0 && this->_size.height > 0 )
	{
		this->_pixelDataSize = PixelDataSize(this->_pixelFormat);
		this->_dataSize = this->_pixelDataSize*this->_size.width*this->_size.height;

		this->_data = new unsigned char[this->_dataSize];
		if( this->_data )
		{
			memset(this->_data, 0, this->_dataSize);
		}
		else
		{
			this->_size = 0;
			this->_pixelDataSize = 0;
			this->_dataSize = 0;
			this->_data = NULL;
		}
	}
	else
	{
		this->_size = 0;
		this->_pixelDataSize = 0;
		this->_dataSize = 0;
		this->_data = NULL;
	}

#ifdef DEBUG
	cout << "Image constructor " << this << endl;
#endif
}


// Construct the image from another image and copy the raw data
Image::Image(Image& other)
:_size(other._size)
,_pixelFormat(other._pixelFormat)
,_pixelDataSize(other._pixelDataSize)
,_dataSize(other._dataSize)
,_data(NULL)
{
	if( this->_size.width > 0 && this->_size.height > 0 )
	{
		this->_data = new unsigned char[this->_dataSize];
		if( this->_data )
		{
			memcpy(this->_data, other._data, this->_dataSize);
		}
		else
		{
			this->_size = 0;
			this->_pixelDataSize = 0;
			this->_dataSize = 0;
			this->_data = NULL;
		}
	}
	else
	{
		this->_size = 0;
		this->_pixelDataSize = 0;
		this->_dataSize = 0;
		this->_data = NULL;
	}
	
#ifdef DEBUG
	cout << "Image constructor " << this << endl;
#endif
}


// Destruct the image and clear the raw data if it exists
Image::~Image()
{
	if( this->IsValid() )
	{
		delete this->_data;
	}
	
#ifdef DEBUG
	cout << "Image destructor " << this << endl;
#endif
}


// Initialize the image data
void Image::Initialize(unsigned int width, unsigned int height, PixelFormat pixelFormat)
{
	if( !this->IsValid() )
	{
		this->_size.Set(width, height);
		this->_pixelFormat = pixelFormat;
		this->_pixelDataSize = PixelDataSize(this->_pixelFormat);
		this->_dataSize = this->_pixelDataSize*this->_size.width*this->_size.height;

		if( this->_size.width > 0 && this->_size.height > 0 )
		{
			this->_data = new unsigned char[this->_dataSize];
			if( this->_data )
			{
				memset(this->_data, 0, this->_dataSize);
			}
			else
			{
				this->_size = 0;
				this->_pixelDataSize = 0;
				this->_dataSize = 0;
				this->_data = NULL;
			}
		}
		else
		{
			this->_size = 0;
			this->_pixelDataSize = 0;
			this->_dataSize = 0;
			this->_data = NULL;
		}
	}
}


// Return true if the image is valid (has initialized data)
bool Image::IsValid()
{
	return (this->_data != NULL);
}


// Get the image size as a vector
Vector2ui Image::GetSize()
{
	return this->_size;
}


// Get the pixel format enumeration
PixelFormat Image::GetPixelFormat()
{
	return this->_pixelFormat;
}


// Switch red and blue compoents
void Image::SwitchRedBlue()
{
	switch( this->_pixelFormat )
	{
	case RGB8:
	case RGBA8:
		for( unsigned int y = 0; y < this->_size.height; ++y )
		{
			for( unsigned int x = 0; x < this->_size.width; ++x )
			{
				unsigned char* pixelPos =
					this->_data+(x+y*this->_size.width)*this->_pixelDataSize;
				unsigned char red = *(pixelPos+2);
				*(pixelPos+2) = *(pixelPos+0);
				*(pixelPos+0) = red;
			}
		}
		break;
	}
}


// Get the length of the raw data array in bytes
unsigned int Image::GetDataSize()
{
	return this->_dataSize;
}


// Get raw data pointer
unsigned char* Image::GetData()
{
	return this->_data;
}


// Set pixel color as a unsigned char array
void Image::SetPixelColor(unsigned int x, unsigned int y, float* colorArray )
{
	for( unsigned int i = 0; i < this->_pixelDataSize; ++i )
	{
		*(this->_data+(x+y*this->_size.width)*this->_pixelDataSize+i) = (unsigned char)(*(colorArray+i)*255);
	}
}


void Image::SetPixelColor(Vector2ui pos, float* colorArray)
{
	this->SetPixelColor(pos.x, pos.y, colorArray);
}


// Get pixel color as a unsigned char array
unsigned char* Image::GetPixelColor(unsigned int x, unsigned int y)
{
	return this->_data+(x+y*this->_size.width)*this->_pixelDataSize;
}


unsigned char* Image::GetPixelColor(Vector2ui pos)
{
	return this->GetPixelColor(pos.x, pos.y);
}