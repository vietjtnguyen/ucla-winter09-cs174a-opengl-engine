#ifndef FRAME_SAVER_H 
#define FRAME_SAVER_H


#include <GL/glut.h>


class FrameSaver
{
public:

	FrameSaver();
	~FrameSaver();

	void SaveFrame(const char* fileName, unsigned int width, unsigned int height, GLuint buffer = GL_BACK);

	void ResetFrameCount();
	void SetFrameCount(unsigned int frameCount);
	unsigned int GetFrameCount();

	void Record(unsigned int width, unsigned int height, GLuint buffer = GL_BACK);
	void ConvertToMpeg(const char* paramFileName = "default.param");

private:

	unsigned int	_frameCount;

	unsigned int	_recordWidth;
	unsigned int	_recordHeight;
		
	unsigned char*	_pixels;
	unsigned int	_pixelsWidth;
};


#endif // FRAME_SAVER_H