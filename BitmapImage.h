#ifndef BITMAP_IMAGE_H
#define BITMAP_IMAGE_H


#include <fstream>
#include <iostream>

#include "Image.h"


#define BITMAP_BYTE_ALIGNMENT 4


using namespace std;


class BitmapImage : public Image
{
public:

	BitmapImage(const char* filename)
	:Image()
	,_bitmapFileHeader()
	,_bitmapInfoHeader()
	{
		fstream fileStream;
		fileStream.open(filename, fstream::in | iostream::binary);

		if( fileStream.is_open() )
		{
			// Read bitmap file header
			fileStream.read((char*)&(this->_bitmapFileHeader.type), 2);
			fileStream.read((char*)&(this->_bitmapFileHeader.fileSize), 4);
			fileStream.read((char*)&(this->_bitmapFileHeader.reserved1), 2);
			fileStream.read((char*)&(this->_bitmapFileHeader.reserved2), 2);
			fileStream.read((char*)&(this->_bitmapFileHeader.offsetBits), 4);

			// Read bitmap info header
			fileStream.read((char*)&(this->_bitmapInfoHeader.headerSize), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.width), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.height), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.planes), 2);
			fileStream.read((char*)&(this->_bitmapInfoHeader.bitCount), 2);
			fileStream.read((char*)&(this->_bitmapInfoHeader.compression), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.imageSize), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.horizontalPixelsPerMeter), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.verticalPixelsPerMeter), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.usedColors), 4);
			fileStream.read((char*)&(this->_bitmapInfoHeader.importantColors), 4);

			// TODO (Viet Nguyen): Read the color palette.

			// Get file length
			fileStream.seekg(0, ios::end);
			unsigned int length = fileStream.tellg();
			fileStream.seekg(0, ios::beg);

			// Move read position forward
			unsigned int offset = this->_bitmapFileHeader.offsetBits;
			char *buffer = new char[offset];
			fileStream.read(buffer, offset);

			// Create image
			PixelFormat pixelFormat;
			switch( this->_bitmapInfoHeader.bitCount )
			{
			case 8:
				pixelFormat = G8;
				break;
			case 32:
				pixelFormat = RGBA8;
				break;
			case 24:
			default:
				pixelFormat = RGB8;
				break;
			}

			this->Initialize(
				this->_bitmapInfoHeader.width,
				this->_bitmapInfoHeader.height,
				pixelFormat);
			
			int dataOffset = 0;
			int rowLength = this->_size.width*this->_pixelDataSize;
			int rowPad = (BITMAP_BYTE_ALIGNMENT-rowLength%BITMAP_BYTE_ALIGNMENT)%BITMAP_BYTE_ALIGNMENT;

			// Load bitmap data into image
			if( this->IsValid() )
			{
				for( unsigned int y = 0; y < this->_size.height; ++y )
				{
					fileStream.read((char*)this->_data+dataOffset, rowLength);
					dataOffset += rowLength;
					if( rowPad )
					{
						fileStream.read(buffer, rowPad);
						dataOffset += 0;
					}
				}
			}

			// Switch red/blues on 32-bit bitmaps
			if( this->_bitmapInfoHeader.bitCount == 24 ||
				this->_bitmapInfoHeader.bitCount == 32 )
			{
				this->SwitchRedBlue();
			}

			fileStream.close();
		}
	}


	~BitmapImage()
	{
	}


	struct BitmapFileHeader
	{
		unsigned short	type;
		unsigned long	fileSize;
		unsigned short	reserved1;
		unsigned short	reserved2;
		unsigned long	offsetBits;
	};


	struct BitmapInfoHeader
	{
		unsigned long	headerSize;
		unsigned long	width;
		unsigned long	height;
		unsigned short	planes;
		unsigned short	bitCount;
		unsigned long	compression;
		unsigned long	imageSize;
		unsigned long	horizontalPixelsPerMeter;
		unsigned long	verticalPixelsPerMeter;
		unsigned long	usedColors;
		unsigned long	importantColors;
	};

	
	// TODO (Viet Nguyen): Implement a data structure to handle the color palette.


	inline BitmapFileHeader* GetFileHeader()
	{
		return &this->_bitmapFileHeader;
	}


	inline BitmapInfoHeader* GetInfoHeader()
	{
		return &this->_bitmapInfoHeader;
	}

private:

	BitmapFileHeader _bitmapFileHeader;
	BitmapInfoHeader _bitmapInfoHeader;

};


inline void SaveImageAsBitmap(const char* filename, Image* image)
{
	if( image )
	{
		if( image->GetPixelFormat() == RGB8 || image->GetPixelFormat() == RGBA8 )
		{
			fstream fileStream;
			fileStream.open(filename, fstream::out | iostream::binary);

			if( fileStream.is_open() )
			{
				char writeBuffer[4];

				// Calculate file size
				unsigned int pixelDataSize = PixelDataSize(image->GetPixelFormat());

				long rowLength = (long)(image->GetDataSize()/image->GetSize().height);
				long rowPad = (BITMAP_BYTE_ALIGNMENT-rowLength%BITMAP_BYTE_ALIGNMENT)%BITMAP_BYTE_ALIGNMENT;

				long imageSize = (rowLength+rowPad)*image->GetSize().height;

				long headerSize = 54;
				long fileSize = headerSize+imageSize;

				// Write bitmap file header
				fileStream.write( (char*)( &( *((short*)writeBuffer) = 19778 ) ), 2); // type
				fileStream.write( (char*)( &( *((long*)writeBuffer) = fileSize ) ), 4); // file size
				fileStream.write( (char*)( &( *((short*)writeBuffer) = 0 ) ), 2); // reserved 1
				fileStream.write( (char*)( &( *((short*)writeBuffer) = 0 ) ), 2); // reserved 2
				fileStream.write( (char*)( &( *((long*)writeBuffer) = headerSize ) ), 4); // offset bytes

				// Write info header
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 40 ) ), 4); // header size
				fileStream.write( (char*)( &( *((long*)writeBuffer) = (long)image->GetSize().width ) ), 4); // width
				fileStream.write( (char*)( &( *((long*)writeBuffer) = (long)image->GetSize().height ) ), 4); // height
				fileStream.write( (char*)( &( *((short*)writeBuffer) = 1 ) ), 2); // planes
				fileStream.write( (char*)( &( *((short*)writeBuffer) = (short)pixelDataSize*8 ) ), 2); // bit count
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), 4); // compression
				fileStream.write( (char*)( &( *((long*)writeBuffer) = imageSize ) ), 4); // image size
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), 4); // horizontal pixels per meter
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), 4); // vertical pixels per meter
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), 4); // used colors
				fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), 4); // important colors
				
				// Switch red/blues
				image->SwitchRedBlue();

				// Write image data
				for( unsigned int y = 0; y < image->GetSize().height; ++y )
				{
					// Actual data
					fileStream.write( (char*)( image->GetData()+image->GetSize().width*pixelDataSize*y ), image->GetSize().width*pixelDataSize);

					// Pad
					fileStream.write( (char*)( &( *((long*)writeBuffer) = 0 ) ), rowPad);
				}

				// Switch red/blues back
				image->SwitchRedBlue();

				fileStream.close();
			}
		}
	}
}


#endif // BITMAP_IMAGE_H