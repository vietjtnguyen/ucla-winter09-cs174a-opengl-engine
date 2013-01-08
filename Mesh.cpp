#include <iostream>
#include <fstream>

#include "Triangle.h"
#include "Vertex.h"

#include "Mesh.h"


using namespace std;


Mesh::Mesh()
:_vertices()
,_triangles()
{
}


Mesh::Mesh(const char* filename)
:_vertices()
,_triangles()
{
	fstream fileStream;
	fileStream.open(filename, fstream::in | iostream::binary);

	if( fileStream.is_open() )
	{
		unsigned short chunkId;
		unsigned long chunkLength;
		unsigned short chunkQuantity;

		// Get file length
		fileStream.seekg(0, ios::end);
		int fileLength = fileStream.tellg();
		fileStream.seekg(0, ios::beg);

		// Loop through chunk structure
		while( fileStream.tellg() < fileLength )
		{
			fileStream.read((char*)&chunkId, 2);
			fileStream.read((char*)&chunkLength, 4);

			switch( chunkId )
			{
			case 0x4d4d: // Main chunk
				break;

			case 0x3d3d: // 3D editor chunk
				break;

			case 0x4000: // Object block
				{
					char name[20];

					// Read object name
					for( int count = 0; count < 20; ++count )
					{
						fileStream.read(&name[count], 1);
						if( name[count] == '\0' )
						{
							break;
						}
					}
				}
				break;

			case 0x4100: // Triangular mesh
				break;

			case 0x4110: // Vertices list
				fileStream.read((char*)&chunkQuantity, 2);
				for( unsigned short i = 0; i < chunkQuantity; ++i )
				{
					Vertex* vertex = new Vertex();
					if( vertex )
					{
						Vector3f nativePos;
						this->_vertices.push_back(vertex);
						for( int j = 0; j < 3; ++j )
						{
							fileStream.read((char*)(&nativePos[j]), 4);
						}

						// Convert from 3ds coordinates to opengl coordinates.
						vertex->SetPosition(nativePos.x, nativePos.z, -nativePos.y);
					}
				}
				break;

			case 0x4120: // Faces description
				fileStream.read((char*)&chunkQuantity, 2);
				for( unsigned short i = 0; i < chunkQuantity; ++i )
				{
					Triangle* triangle = new Triangle();
					if( triangle )
					{
						this->_triangles.push_back(triangle);
						unsigned short vertIndex;
						for( int j = 0; j < 3; ++j )
						{
							fileStream.read((char*)&vertIndex, 2);
							triangle->SetVertex(j, this->_vertices.at((unsigned int)vertIndex));
						}
						fileStream.read((char*)&vertIndex, 2); // Extra data
					}
				}
				break;

			case 0x4140: // Mapping coordinates list
				fileStream.read((char*)&chunkQuantity, 2);
				for( unsigned short i = 0; i < chunkQuantity; ++i )
				{
					Vertex* vertex = this->_vertices.at((unsigned int)i);
					if( vertex )
					{
						for( int j = 0; j < 2; ++j )
						{
							fileStream.read((char*)(&vertex->TextureCoords()[j]), 4);
						}
					}
				}
				break;

			default: // Skip chunk
				fileStream.seekg(chunkLength-6, ios_base::cur);
			}
		}

		fileStream.close();

		this->CalculateVertexNormals();
		this->Update();
	}
}


Mesh::~Mesh()
{
}


void Mesh::TransformVertices(Matrix44f transform)
{
	for( unsigned int i = 0; i < this->_vertices.size(); ++i )
	{
		Vertex* vertex = this->_vertices.at(i);
		if( vertex )
		{
			vertex->Position() = (Vector3f)(transform*Vector4f(vertex->GetPosition(), 1.0f));
		}
	}
}


void Mesh::CalculateVertexNormals()
{
	// Clear all vertex normals
	for( unsigned int i = 0; i < this->_vertices.size(); ++i )
	{
		Vertex* vertex = this->_vertices.at(i);
		if( vertex )
		{
			vertex->Normal() = 0.0f;
		}
	}

	// Sum all adjacent triangle normals
	for( unsigned int i = 0; i < this->_triangles.size(); ++i )
	{
		Triangle* triangle = this->_triangles.at(i);
		if( triangle )
		{
			if( triangle->IsValid() )
			{
				for( unsigned int j = 0; j < 3; ++j )
				{
					Vertex* vertex = triangle->GetVertex(j);
					vertex->Normal() += triangle->GetNormal();
				}
			}
		}
	}

	// Normalize all vertex normals
	for( unsigned int i = 0; i < this->_vertices.size(); ++i )
	{
		Vertex* vertex = this->_vertices.at(i);
		if( vertex )
		{
			vertex->Normal().Normalize();
		}
	}
}


void Mesh::Update(bool drawNormals)
{
	this->StartRecording();

	glBegin(GL_TRIANGLES);
		for( unsigned int i = 0; i < this->_triangles.size(); ++i )
		{
			Triangle* triangle = this->_triangles.at(i);
			if( triangle )
			{
				triangle->Execute(false, true, true);
			}
		}
	glEnd();

	if( drawNormals )
	{
		glColor4f(1.0f, 0.0f, 1.0f, 0.75f);
		glBegin(GL_LINES);
			for( unsigned int i = 0; i < this->_vertices.size(); ++i )
			{
				Vertex* vertex = this->_vertices.at(i);
				if( vertex )
				{
					glVertex3fv((float*)vertex->GetPosition());
					glVertex3fv((float*)(vertex->GetPosition()+vertex->GetNormal()));
				}
			}
		glEnd();
	}

	this->StopRecording();
}