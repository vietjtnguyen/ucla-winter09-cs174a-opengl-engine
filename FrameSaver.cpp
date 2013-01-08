#ifdef _WIN32
	#include <windows.h>
#endif
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "FrameSaver.h"


using namespace std;


FrameSaver::FrameSaver()
:_frameCount(0)
,_recordWidth(0)
,_recordHeight(0)
,_pixels(NULL)
,_pixelsWidth(0)
{
}


FrameSaver::~FrameSaver()
{
	if( this->_pixels )
	{
		delete this->_pixels;
	}
}


void FrameSaver::SaveFrame(const char* fileName, unsigned int width, unsigned int height, GLuint buffer)
{
	fstream fileStream;
	fileStream.open(fileName, ios_base::out | ios_base::binary);

	// Check for proper opening
	if( !fileStream.is_open() )
	{
		cout << "File '" << fileName << "' could not be opened for writing! Exiting frame dump." << endl;
		return;
	}

	// Write PPM header
	fileStream << "P6 " << width << " " << height << " 255" << endl;

	// Set buffer
	glGetError(); // Clear the error "buffer"
   	glReadBuffer(buffer);
	GLenum glError = glGetError();
	if( glError != GL_NO_ERROR )
	{
		cout << "Error '" << glError << "' encountered on glReadBuffer(buffer)! Continuing frame dump." << endl;
	}

	// Create pixel buffer if necessary
	if( this->_pixels )
	{
		if( this->_pixelsWidth != width*3 )
		{
			delete this->_pixels;
			this->_pixels = new unsigned char[width*3];
			this->_pixelsWidth = width*3;
		}
	}
	else
	{
		this->_pixels = new unsigned char[width*3];
		this->_pixelsWidth = width*3;
	}

	// Dump pixels
	for( register int y = height-1; y >= 0; --y ) 
	{
		glReadPixels(0, y, width, 1, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)this->_pixels);
		fileStream.write((const char*)this->_pixels, width*3);
	}

	fileStream.close();
}


void FrameSaver::ResetFrameCount()
{
	this->_frameCount = 0;
}


void FrameSaver::SetFrameCount(unsigned int frameCount)
{
	this->_frameCount = frameCount;
}


unsigned int FrameSaver::GetFrameCount()
{
	return this->_frameCount;
}


void FrameSaver::Record(unsigned int width, unsigned int height, GLuint buffer)
{
	this->_recordWidth = width;
	this->_recordHeight = height;

	char fileNameBuffer[32];
	sprintf(fileNameBuffer, "frame%04u.ppm", this->_frameCount);
	this->_frameCount++;

	this->SaveFrame(fileNameBuffer, width, height, buffer);
}


void FrameSaver::ConvertToMpeg(const char* paramFileName)
{
	fstream fileStream;
	fileStream.open(paramFileName, ios_base::out);

	// Check for proper opening
	if( !fileStream.is_open() )
	{
		cout << "File '" << paramFileName << "' could not be opened for writing!" << endl;
		return;
	}

	// Create file
	char fileContent[512];
	int bufsize = sprintf(fileContent, "BASE_FILE_FORMAT PPM\nINPUT_CONVERT *\nINPUT_DIR .\n\nINPUT\nframe*.ppm [0000-%04u]\nEND_INPUT\n\nOUTPUT output.mpg\n\nSIZE %ux%u\n\nPIXEL HALF\nRANGE 10\nGOP_SIZE 30\nSLICES_PER_FRAME 1\n\n#PATTERN IBBPBBPBBPBBPBB\nPATTERN IBBPBBI\nREFERENCE_FRAME ORIGINAL\nPSEARCH_ALG LOGARITHMIC\nBSEARCH_ALG CROSS2\nIQSCALE 8\nPQSCALE 10\nBQSCALE 25\0", this->_frameCount, this->_recordWidth, this->_recordHeight);
	fileStream.write(fileContent, bufsize);

	fileStream.close();

	// Call mpeg_encode.exe
	char command[256];
	sprintf(command,"mpeg_encode.exe %s", paramFileName);
	system(command);
}