#include <iostream>
#include <cstring>

#include "Texture.h"


using namespace std;


// Blank texture constructor
Texture::Texture()
:_textureName(NULL)
,_frameCounts(1, 1)
,_animFrame(0.0f)
,_image(NULL)
{
#ifdef DEBUG
	cout << "Texture constructor " << this << endl;
#endif
}


// Construct a texture from a pre-existing image
Texture::Texture(Image* image)
:_textureName(NULL)
,_frameCounts(1, 1)
,_animFrame(0.0f)
,_image(NULL)
{
	if( image )
	{
		if( image->IsValid() )
		{
			this->_image = image;

			// Generate texture name
			glGenTextures(1, &this->_textureName);

			// Activate texture
			glBindTexture(GL_TEXTURE_2D, this->_textureName);

			// Set texture
			glTexImage2D(
				GL_TEXTURE_2D,
				0, // Base level
				PixelGlInternal(this->_image->GetPixelFormat()), // Internal format
				this->_image->GetSize().width,
				this->_image->GetSize().height,
				0, // No border
				PixelGlFormat(this->_image->GetPixelFormat()), // Pixel data format
				GL_UNSIGNED_BYTE, // Pixel data type
				(GLvoid*)this->_image->GetData());

			// Set filters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Deactivate texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

#ifdef DEBUG
	cout << "Texture constructor " << this << endl;
#endif
}


// Construct a texture from part of a pre-existing image
Texture::Texture(Image* image, Vector2i offset, Vector2ui size, bool asAlpha)
:_textureName(NULL)
,_frameCounts(1, 1)
,_animFrame(0.0f)
,_image(NULL)
{
	if( image )
	{
		if( image->IsValid() )
		{
			this->_image = image;

			// Generate texture name
			glGenTextures(1, &this->_textureName);

			// Activate texture
			glBindTexture(GL_TEXTURE_2D, this->_textureName);

			// Set texture
			glTexSubImage2D(
				GL_TEXTURE_2D,
				0, // Base level
				offset.x,
				offset.y,
				size.width,
				size.height,
				asAlpha ? GL_LUMINANCE_ALPHA : PixelGlFormat(this->_image->GetPixelFormat()), // Pixel data format
				GL_UNSIGNED_BYTE, // Pixel data type
				(GLvoid*)this->_image->GetData());

			// Set filters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Deactivate texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

#ifdef DEBUG
	cout << "Texture constructor " << this << endl;
#endif
}


// Destructor
Texture::~Texture()
{
	if( this->IsValid() )
	{
		glDeleteTextures(1, &this->_textureName);
	}

#ifdef DEBUG
	cout << "Texture destructor " << this << endl;
#endif
}


// Return true if texture is valid (has a valid image attached)
bool Texture::IsValid()
{
	if( this->_image )
	{
		return this->_image->IsValid();
	}
	else
	{
		return false;
	}
}


// Get internal texture name (OpenGL id)
GLuint Texture::GetTextureName()
{
	return this->_textureName;
}


// Set frame counts
void Texture::SetFrameCounts(unsigned int horizontalFrames, unsigned int verticalFrames)
{
	if( horizontalFrames > 0 && verticalFrames > 0 )
	{
		this->_frameCounts.Set(horizontalFrames, verticalFrames);
	}
}


// Set frame counts via vector
void Texture::SetFrameCounts(Vector2ui frameCounts)
{
	this->SetFrameCounts(frameCounts.x, frameCounts.y);
}


// Get frame counts
Vector2ui Texture::GetFrameCounts()
{
	return this->_frameCounts;
}


// Set animation frame
void Texture::SetAnimationFrame(float frame)
{
	this->_animFrame = frame;
}


// Get animation frame
float Texture::GetAnimationFrame()
{
	return this->_animFrame;
}


// Attach an image to the texture
void Texture::AttachImage(Image* image)
{
	if( image )
	{
		if( image->IsValid() )
		{
			this->_image = image;

			// Generate texture name
			glGenTextures(1, &this->_textureName);

			// Activate texture
			glBindTexture(GL_TEXTURE_2D, this->_textureName);

			// Set texture
			glTexImage2D(
				GL_TEXTURE_2D,
				0, // Base level
				PixelGlInternal(this->_image->GetPixelFormat()), // Internal format
				this->_image->GetSize().width,
				this->_image->GetSize().height,
				0, // No border
				PixelGlFormat(this->_image->GetPixelFormat()), // Pixel data format
				GL_UNSIGNED_BYTE, // Pixel data type
				(GLvoid*)this->_image->GetData());

			// Set filters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Deactivate texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}


// Get attached image
Image* Texture::GetImage()
{
	return this->_image;
}


// Reload texture from attached image
void Texture::ReloadTexture()
{
	if( this->IsValid() )
	{
		glBindTexture(GL_TEXTURE_2D, this->_textureName);

		glTexImage2D(
			GL_TEXTURE_2D,
			0, // Base level
			PixelGlInternal(this->_image->GetPixelFormat()), // Internal format
			this->_image->GetSize().width,
			this->_image->GetSize().height,
			0, // No border
			PixelGlFormat(this->_image->GetPixelFormat()), // Pixel data format
			GL_UNSIGNED_BYTE, // Pixel data type
			(GLvoid*)this->_image->GetData());

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}