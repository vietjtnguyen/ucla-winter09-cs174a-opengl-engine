#include <iostream>
#include <cstring>

#include "Image.h"
#include "Matrices.h"
#include "Vertex.h"

#include "Terrain.h"

#include <GL/glut.h>


using namespace std;


Terrain::Terrain(int width, int height)
:_size(width, height)
,_offset(0, 0)
,_dataSize(0)
,_heightMatrix(NULL)
{
	if( this->_size.width >= 0 && this->_size.height >= 0 )
	{
		this->_dataSize = (unsigned int)((this->_size.width+1)*(this->_size.height+1));
		this->_heightMatrix = new Vertex[this->_dataSize];

		this->UpdateVertices();
	}

#ifdef DEBUG
	cout << "Terrain constructor " << this << endl;
#endif
}


Terrain::Terrain(Vector2i size)
:_size(size)
,_offset(0, 0)
,_dataSize(0)
,_heightMatrix(NULL)
{
	if( this->_size.width >= 0 && this->_size.height >= 0 )
	{
		this->_dataSize = (unsigned int)((this->_size.width+1)*(this->_size.height+1));
		this->_heightMatrix = new Vertex[this->_dataSize];

		this->UpdateVertices();
	}

#ifdef DEBUG
	cout << "Terrain constructor " << this << endl;
#endif
}


Terrain::Terrain(Image* image)
:_size(0, 0)
,_offset(0, 0)
,_dataSize(0)
,_heightMatrix(NULL)
{
	if( image )
	{
		this->_size.width = (int)image->GetSize().width-1;
		this->_size.height = (int)image->GetSize().height-1;

		if( this->_size.width >= 0 && this->_size.height >= 0 )
		{
			this->_dataSize = (unsigned int)((this->_size.width+1)*(this->_size.height+1));
			this->_heightMatrix = new Vertex[this->_dataSize];

			this->UpdateVertices();

			for( int y = 0; y <= this->_size.height; ++y )
			{
				for( int x = 0; x <= this->_size.width; ++x )
				{
					unsigned char pixelValue = 255-*image->GetPixelColor(x, y);
					this->SetHeight(x, y, (float)pixelValue/255.0f);
				}
			}
		}
	}

#ifdef DEBUG
	cout << "Terrain constructor " << this << endl;
#endif
}


Terrain::~Terrain()
{
	if( this->_heightMatrix )
	{
		// TODO (Viet Nguyen): Figure out what this fails.
		//delete this->_heightMatrix;
	}

#ifdef DEBUG
	cout << "Terrain destructor " << this << endl;
#endif
}


bool Terrain::IsValid()
{
	return (this->_heightMatrix != NULL);
}


void Terrain::LoadHeightMap(Image* image)
{
}


// TODO (Viet Nguyen): Preserve the previous height information.
void Terrain::SetSize(int width, int height)
{
	if( width >= 0 && height >= 0 )
	{
		this->_size.Set(width, height);

		if( this->IsValid() )
		{
			delete this->_heightMatrix;
			this->_heightMatrix = NULL;
		}

		this->_dataSize = (unsigned int)((this->_size.width+1)*(this->_size.height+1));
		this->_heightMatrix = new Vertex[this->_dataSize];

		this->UpdateVertices();
	}
}


void Terrain::SetSize(Vector2i size)
{
	this->SetSize(size.width, size.height);
}


Vector2i Terrain::GetSize()
{
	return this->_size;
}


void Terrain::SetOffset(int x, int y)
{
	this->_offset.Set(x, y);
	this->UpdateVertices();
}


void Terrain::SetOffset(Vector2i offset)
{
	this->SetOffset(offset.x, offset.y);
}


Vector2i Terrain::GetOffset()
{
	return this->_offset;
}


void Terrain::SetHeight(int x, int y, float height)
{
	if( this->IsValid() )
	{
		if( x >= 0 && x <= this->_size.width &&
			y >= 0 && y <= this->_size.height )
		{
			this->_heightMatrix[x+y*(this->_size.width+1)].Position().y = height;
		}
	}
}


void Terrain::SetHeight(Vector2i pos, float height)
{
	this->SetHeight(pos.x, pos.y, height);
}


float Terrain::GetHeight(int x, int y)
{
	if( this->IsValid() )
	{
		if( x >= 0 && x <= this->_size.width &&
			y >= 0 && y <= this->_size.height )
		{
			return this->_heightMatrix[x+y*(this->_size.width+1)].Position().y;
		}
	}
	return 0.0f;
}


float Terrain::GetHeight(Vector2i pos)
{
	return this->GetHeight(pos.x, pos.y);
}


float Terrain::GetHeight(float x, float y, float z)
{
	Vector4f worldPos(x, y, z, 1.0f);
	Matrix44f worldToObject;
	worldToObject = // WARNING (Viet Nguyen): The matrix multiply order is currently implemented INCORRECTLY. It should be scale, rotate, translate left to right.
		Matrix44f::Translate(
			-this->_position.x,
			-this->_position.y,
			-this->_position.z)*
		Matrix44f::EulerRotate(
			-this->_eulerRotation.x,
			-this->_eulerRotation.y,
			-this->_eulerRotation.z)*
		Matrix44f::Scale(
			1.0f/this->_scale.x,
			1.0f/this->_scale.y,
			1.0f/this->_scale.z);

	Vector4f localPos = worldToObject*worldPos;
	localPos.x = localPos.x-(float)this->_offset.x;
	localPos.z = -localPos.z-(float)this->_offset.y;

	if( localPos.x < 0 || localPos.x > this->_size.x ||
		localPos.z < 0 || localPos.z > this->_size.y )
	{
		return 0.0f;
	}
	else
	{
		Vector2i lowPos((int)floor(localPos.x), (int)floor(localPos.z));
		Vector2f posMod(localPos.x-floor(localPos.x), localPos.z-floor(localPos.z));

		float leftHeight =
			this->GetHeight(lowPos.x, lowPos.y)*(1.0f-posMod.y)+
			this->GetHeight(lowPos.x, lowPos.y+1)*(posMod.y);
		float rightHeight =
			this->GetHeight(lowPos.x+1, lowPos.y)*(1.0f-posMod.y)+
			this->GetHeight(lowPos.x+1, lowPos.y+1)*(posMod.y);
		float height = leftHeight*(1.0f-posMod.x)+rightHeight*(posMod.x);

		return height;
	}
}


float Terrain::GetHeight(Vector3f pos)
{
	return this->GetHeight(pos.x, pos.y, pos.z);
}


float Terrain::GetScaledHeight(int x, int y)
{
	return this->GetHeight(x, y)*this->_scale.y;
}


float Terrain::GetScaledHeight(Vector2i pos)
{
	return this->GetHeight(pos)*this->_scale.y;
}


float Terrain::GetScaledHeight(float x, float y, float z)
{
	return this->GetHeight(x, y, z)*this->_scale.y;
}


float Terrain::GetScaledHeight(Vector3f pos)
{
	return this->GetHeight(pos)*this->_scale.y;
}


void Terrain::Update()
{
	if( this->IsValid() )
	{
		this->Object::StartRecording();
		glBegin(GL_QUADS);

		for( int y = 0; y < this->_size.height; ++y )
		{
			for( int x = 0; x < this->_size.width; ++x )
			{
				this->_heightMatrix[(x+0)+(y+0)*(this->_size.width+1)].Execute();
				this->_heightMatrix[(x+1)+(y+0)*(this->_size.width+1)].Execute();
				this->_heightMatrix[(x+1)+(y+1)*(this->_size.width+1)].Execute();
				this->_heightMatrix[(x+0)+(y+1)*(this->_size.width+1)].Execute();
			}
		}

		glEnd();
		this->Object::StopRecording();
	}
}


void Terrain::UpdateVertices()
{
	if( this->IsValid() )
	{
		for( int y = 0; y <= this->_size.height; ++y )
		{
			for( int x = 0; x <= this->_size.width; ++x )
			{

				Vertex* vertex = this->_heightMatrix+x+y*(this->_size.width+1);
				
				vertex->Position().x = (float)x + (float)this->_offset.x;
				vertex->Position().z = -(float)y - (float)this->_offset.y;

				vertex->TextureCoords().u = (float)x / (float)this->_size.width;
				vertex->TextureCoords().v = (float)y / (float)this->_size.height;

				vertex->Normal().x = 0.0f;
				vertex->Normal().y = 1.0f;
				vertex->Normal().z = 0.0f;
			}
		}
	}
}