#ifndef OBJECT_H
#define OBJECT_H


#include <vector>

#include "Entity.h"
#include "Generic.h"
#include "GlobalList.h"
#include "Texture.h"
#include "Vectors.h"
#include "World.h"

#include <GL/glut.h>


class Object : public Entity, public GlobalList<Object>
{
public:

	Object(bool active = true);

	virtual ~Object();

	virtual void StartRecording();
	virtual void StopRecording();
	virtual void Clear();

	void CreatePlane(float width, float length);
	void CreateCube(float size);
	void CreateCone(float radius, float height, unsigned int slices, unsigned int stacks);
	void CreateCylinder();
	void CreateSphere(float radius, unsigned int slices, unsigned int stacks);

	enum MaterialType
	{
		Ambient = 0,
		Diffuse = 1,
		Specular = 2,
		Emission = 3
	};
	void SetColor(MaterialType type, Vector4f rgba);
	Vector4f GetColor(MaterialType type);
	Vector4f& Color(MaterialType type);
	
	void SetShininess(float shininess);
	float GetShininess();
	float& Shininess();

	enum BlendMode
	{
		Normal = 0,
		Additive = 1,
		Subtractive = 2
	};
	void SetBlendMode(BlendMode blendMode);
	BlendMode GetBlendMode();

	enum RenderMode
	{
		PointCloud = 0,
		Wireframe = 1,
		Polygon = 2
	};
	void SetRenderMode(RenderMode renderMode);
	RenderMode GetRenderMode();

	enum RenderSide
	{
		FrontFace = 0,
		BackFace = 1,
		DoubleSided = 2
	};
	void SetRenderSide(RenderSide renderSide);
	RenderSide GetRenderSide();

	void SetTexture(Texture* texture);
	void ClearTexture();
	Texture* GetTexture();

	virtual void Render();

private:

	GLuint		_list;

	Vector4f*	_materialColors;
	float		_shininess;

	BlendMode	_blendMode;
	RenderMode	_renderMode;
	RenderSide	_renderSide;

	Texture*	_texture;
};
typedef Object::GlobalList<Object> GlobalObjectList;


#endif // OBJECT_H