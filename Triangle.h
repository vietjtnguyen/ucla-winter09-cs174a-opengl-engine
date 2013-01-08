#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Vertex.h"


class Triangle
{
public:

	Triangle()
	:_vertex1(NULL)
	,_vertex2(NULL)
	,_vertex3(NULL)
	,_normal()
	{
	}


	Triangle(Vertex* vert1, Vertex* vert2, Vertex* vert3)
	:_vertex1(vert1)
	,_vertex2(vert2)
	,_vertex3(vert3)
	,_normal()
	{
		this->CalculateNormal();
	}


	~Triangle()
	{
	}


	bool IsValid()
	{
		return ( this->_vertex1 != NULL && this->_vertex2 != NULL && this->_vertex3 != NULL );
	}


	void SetVertex(int index, Vertex* vertex)
	{
		if( index >= 0 && index <= 2 )
		{
			*(&this->_vertex1+index) = vertex;
			this->CalculateNormal();
		}
	}


	Vertex* GetVertex(int index)
	{
		if( index >= 0 && index <= 2 )
		{
			return *(&this->_vertex1+index);
		}
		return NULL;
	}


	Vertex* Vertex1()
	{
		return this->_vertex1;
	}


	Vertex* Vertex2()
	{
		return this->_vertex2;
	}


	Vertex* Vertex3()
	{
		return this->_vertex3;
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


	void CalculateNormal()
	{
		if( this->IsValid() )
		{
			Vector3f vec12 = this->_vertex2->Position() - this->_vertex1->Position();
			Vector3f vec13 = this->_vertex3->Position() - this->_vertex1->Position();
			this->_normal = vec12.Cross(vec13);
			this->_normal.Normalize();
		}
	}


	void Execute(bool color = true, bool normal = true, bool texCoords = true)
	{
		if( this->IsValid() )
		{
			this->_vertex1->Execute(color, normal, texCoords);
			this->_vertex2->Execute(color, normal, texCoords);
			this->_vertex3->Execute(color, normal, texCoords);
		}
	}

private:
	
	Vertex*		_vertex1;
	Vertex*		_vertex2;
	Vertex*		_vertex3;

	Vector3f	_normal;

};


#endif // TRIANGLE_H