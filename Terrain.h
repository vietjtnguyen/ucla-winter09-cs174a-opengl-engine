#ifndef TERRAIN_H
#define TERRAIN_H


#include "Object.h"
#include "Vectors.h"


class Image;
class Vertex;


class Terrain : public Object
{
public:

	Terrain(int width, int height);
	Terrain(Vector2i size);
	Terrain(Image* image);
	
	virtual ~Terrain();

	bool IsValid();

	void LoadHeightMap(Image* image);

	void SetSize(int width, int height);
	void SetSize(Vector2i size);
	Vector2i GetSize();

	void SetOffset(int x, int y);
	void SetOffset(Vector2i offset);
	Vector2i GetOffset();

	void SetHeight(int x, int y, float height);
	void SetHeight(Vector2i pos, float height);
	float GetHeight(int x, int y);
	float GetHeight(Vector2i pos);
	float GetHeight(float x, float y, float z);
	float GetHeight(Vector3f pos);
	float GetScaledHeight(int x, int y);
	float GetScaledHeight(Vector2i pos);
	float GetScaledHeight(float x, float y, float z);
	float GetScaledHeight(Vector3f pos);

	void SetColor(int x, int y, float r, float g, float b, float a);
	void SetColor(Vector2i pos, Vector4f rgba);
	Vector4f GetColor(int x, int y);
	Vector4f GetColor(Vector2i pos);

	void Update();

private:

	void UpdateVertices();

	// Don't allow modification of the terrain call list.
	virtual void StartRecording() {}
	virtual void StopRecording() {}
	virtual void Clear() {}

	Vector2i		_size;
	Vector2i		_offset;

	unsigned int	_dataSize;
	Vertex*			_heightMatrix;
};


#endif // TERRAIN_H