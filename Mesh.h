#ifndef MESH_H
#define MESH_H


#include <vector>

#include "Matrices.h"
#include "Object.h"


using namespace std;


class Vertex;
class Triangle;


class Mesh : public Object
{
public:

	Mesh();
	Mesh(const char* fileName);

	virtual ~Mesh();

	void TransformVertices(Matrix44f transform);

	void CalculateVertexNormals();

	void Update(bool drawNormals = false);

private:

	vector<Vertex*>		_vertices;
	vector<Triangle*>	_triangles;

};


#endif // MESH_H