#ifndef BITMAP_LOADER_H
#define BITMAP_LOADER_H


#include <fstream>
#include <iostream>


#define BITMAP_BYTE_ALIGNMENT 2


using namespace std;


// TODO (Viet Nguyen): Support non 24-bit bitmaps and possibly 32-bit bitmaps. Support color palettes as well. Convert everything to 32-bit bitmaps regardless?
class Bitmap
{
public:

	Bitmap(const char* filename)
	:_bitmapFileHeader()
	,_bitmapInfoHeader()
	,_rawData(NULL)
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

			// Read color data
			int pixelDataSize = 3;
			int dataOffset = 0;
			int dataLength = this->GetWidth()*pixelDataSize;
			int dataRowPad = BITMAP_BYTE_ALIGNMENT-dataLength%BITMAP_BYTE_ALIGNMENT;
			int dataArraySize = dataLength*this->GetHeight();

			this->_rawData = new char[dataArraySize];

			for( int y = 0; y < (int)this->GetHeight(); ++y )
			{
				fileStream.read(this->_rawData+dataOffset, dataLength);
				dataOffset += dataLength;
				if( dataRowPad )
				{
					fileStream.read(buffer, dataRowPad);
					dataOffset += 0;
				}
			}

			fileStream.close();
		}
		else
		{
			delete this;
			return;
		}
	}

	~Bitmap()
	{
		if( this->_rawData )
		{
			delete _rawData;
		}
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

	inline unsigned long GetWidth()
	{
		return this->_bitmapInfoHeader.width;
	}

	inline unsigned long GetHeight()
	{
		return this->_bitmapInfoHeader.height;
	}

	inline char* GetRawData()
	{
		return _rawData;
	}

private:

	BitmapFileHeader _bitmapFileHeader;
	BitmapInfoHeader _bitmapInfoHeader;
	char* _rawData;
};


#endif // BITMAP_LOADER_H