#ifndef LIGHT_H
#define LIGHT_H


#include <vector>

#include "Entity.h"
#include "Generic.h"
#include "GlobalList.h"
#include "Vectors.h"

#include <GL/glut.h>


using namespace std;


class Light : public Entity, public GlobalList<Light>
{
public:

	Light(bool active = true);

	virtual ~Light();

	virtual void Activate();
	virtual void Deactivate();
	virtual void SetActiveState(bool state);

	void MakeSpot();
	void MakeDirectional();
	bool IsSpot();
	bool IsDirectional();

	void SetAmbientColor(float r, float g, float b, float a);
	void SetAmbientColor(Vector4f rgba);
	Vector4f GetAmbientColor();

	void SetDiffuseColor(float r, float g, float b, float a);
	void SetDiffuseColor(Vector4f rgba);
	Vector4f GetDiffuseColor();

	void SetSpecularColor(float r, float g, float b, float a);
	void SetSpecularColor(Vector4f rgba);
	Vector4f GetSpecularColor();

	void SetShininess(float shininess);
	float GetShininess();

	void SetDirection(float x, float y, float z);
	void SetDirection(Vector3f direction);
	Vector3f GetDirection();

	void SetSpotExponent(float exponent);
	float GetSpotExponent();

	void SetSpotCutoff(float cutoff);
	float GetSpotCutoff();

	void SetConstantAttenuation(float constant);
	void SetLinearAttenuation(float constant);
	void SetQuadraticAttenuation(float constant);
	float GetConstantAttenuation();
	float GetLinearAttenuation();
	float GetQuadraticAttenuation();

	virtual void Render();

private:

	GLuint					_lightId;

	bool					_isDirectional;

	Vector4f				_ambientColor;
	Vector4f				_diffuseColor;
	Vector4f				_specularColor;
	float					_shininess;

	Vector3f				_direction;

	float					_spotExponent;
	float					_spotCutoff;

	float					_constantAttenuation;
	float					_linearAttenuation;
	float					_quadraticAttenuation;

	static vector<Light*>	_lightIdList;
};
typedef Light::GlobalList<Light> GlobalLightList;


#endif // LIGHT_H