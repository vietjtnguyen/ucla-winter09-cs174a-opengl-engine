#ifndef TEXTURE_H
#define TEXTURE_H


#include "Image.h"
#include "Vectors.h"

#include <GL/glut.h>


// Map the pixel format enumeration to its equivalent OpenGL enumeration
inline GLuint PixelGlInternal(PixelFormat pixelFormat)
{
	switch( pixelFormat )
	{
	case G8:
		return GL_INTENSITY8;
	case RGB8:
		return GL_RGB8;
	case RGBA8:
		return GL_RGBA8;
	case RGB10A2:
		return GL_RGB10_A2;
	default:
		return 0;
	}
}


// Map the pixel format enumeration to its equivalent OpenGL enumeration
inline GLuint PixelGlFormat(PixelFormat pixelFormat)
{
	switch( pixelFormat )
	{
	case G8:
		return GL_INTENSITY8;
	case RGB8:
		return GL_RGB;
	case RGBA8:
		return GL_RGBA;
	case RGB10A2:
		return GL_RGBA;
	default:
		return 0;
	}
}


class Texture
{
public:

	Texture();
	Texture(Image* image);
	Texture(Image* image, Vector2i offset, Vector2ui size, bool asAlpha = false);
	~Texture();

	bool IsValid();

	GLuint GetTextureName();

	void SetFrameCounts(unsigned int horizontalFrames, unsigned int verticalFrames);
	void SetFrameCounts(Vector2ui frameCounts);
	Vector2ui GetFrameCounts();

	void SetAnimationFrame(float frame);
	float GetAnimationFrame();

	void AttachImage(Image* image);
	Image* GetImage();

	void ReloadTexture();

protected:

	GLuint		_textureName;

	Vector2ui	_frameCounts;
	float		_animFrame;

	Image*		_image;
};


void BlurTextureSlow(Texture* texture, unsigned int pixelRange);


#endif // TEXTURE_H