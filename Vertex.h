#ifndef VERTEX_H
#define VERTEX_H


#include "Vectors.h"

#include <GL/glut.h>


class Vertex
{
public:

	Vertex()
	:_position(0.0f, 0.0f, 0.0f)
	,_textureCoords(0.0f, 0.0f, 0.0f)
	,_color(0.5f, 0.5f, 0.5f, 1.0f)
	,_normal(0.0f, 0.0f, 1.0f)
	{
	}

	
	~Vertex()
	{
	}


	void SetPosition(float x, float y, float z)
	{
		this->_position.Set(x, y, z);
	}


	void SetPosition(Vector3f pos)
	{
		this->_position = pos;
	}


	Vector3f GetPosition()
	{
		return this->_position;
	}


	Vector3f& Position()
	{
		return this->_position;
	}


	void SetTextureCoords(float x, float y, float z)
	{
		this->_textureCoords.Set(x, y, z);
	}


	void SetTextureCoords(Vector3f pos)
	{
		this->_textureCoords = pos;
	}


	Vector3f GetTextureCoords()
	{
		return this->_textureCoords;
	}


	Vector3f& TextureCoords()
	{
		return this->_textureCoords;
	}


	void SetColor(float r, float g, float b, float a)
	{
		this->_color.Set(r, g, b, a);
	}


	void SetColor(Vector4f color)
	{
		this->_color = color;
	}


	Vector4f GetColor()
	{
		return this->_color;
	}


	Vector4f& Color()
	{
		return this->_color;
	}


	void SetNormal(float x, float y, float z)
	{
		this->_normal.Set(x, y, z);
	}


	void SetNormal(Vector3f normal)
	{
		this->_normal = normal;
	}


	Vector3f GetNormal()
	{
		return this->_normal;
	}


	Vector3f& Normal()
	{
		return this->_normal;
	}


	void Execute(bool color = true, bool normal = true, bool texCoords = true)
	{
		if( color )
		{
			glColor4fv(this->_color);
		}
		if( normal )
		{
			glNormal3fv(this->_normal);
		}
		if( texCoords )
		{
			glTexCoord3fv(this->_textureCoords);
		}
		glVertex3fv(this->_position);
	}

private:

	Vector3f	_position;
	Vector3f	_textureCoords;
	Vector4f	_color;
	Vector3f	_normal;

};


#endif // VERTEX_H