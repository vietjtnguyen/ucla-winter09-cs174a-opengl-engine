#include <iostream>

#include "World.h"

#include "Light.h"


using namespace std;


vector<GlobalLightList*> GlobalLightList::_globalList;
vector<Light*> Light::_lightIdList;


// Default constructor
Light::Light(bool active)
:Entity(active)
,_lightId(0)
,_isDirectional(false)
,_ambientColor(0.0f, 0.0f, 0.0f, 1.0f)
,_diffuseColor(1.0f, 1.0f, 1.0f, 1.0f)
,_specularColor(1.0f, 1.0f, 1.0f, 1.0f)
,_shininess(5000.0f)
,_direction(0.0f, 0.0f, -1.0f)
,_spotExponent(0.0f)
,_spotCutoff(180.0f)
,_constantAttenuation(1.0f)
,_linearAttenuation(0.0f)
,_quadraticAttenuation(0.0f)
{
	for( this->_lightId = GL_LIGHT0; this->_lightId <= GL_LIGHT7; ++this->_lightId )
	{
		bool available = true;

		for( unsigned int i = 0; i < Light::_lightIdList.size(); ++i )
		{
			available = !(Light::_lightIdList.at(i)->_lightId == this->_lightId);
			if( !available )
			{
				break;
			}
		}

		if( available )
		{
			glEnable(this->_lightId);
			Light::_lightIdList.push_back(this);
			this->SetActiveState(active);
			break;
		}
		else
		{
			if( this->_lightId == GL_LIGHT7 )
			{
				this->_lightId = 0;
				break;
			}
			continue;
		}
	}

#ifdef DEBUG
	cout << "Light constructor " << this << endl;
#endif
}


// Destructor
Light::~Light()
{
	if( this->_lightId )
	{
		glDisable(this->_lightId);

		for( unsigned int i = 0; i < Light::_lightIdList.size(); ++i )
		{
			if( Light::_lightIdList.at(i)->_lightId == this->_lightId )
			{
				Light::_lightIdList.erase(Light::_lightIdList.begin()+i);
				break;
			}
		}
	}

#ifdef DEBUG
	cout << "Light destructor " << this << endl;
#endif
}


// Activate object
void Light::Activate()
{
	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_AMBIENT, (float*)this->_ambientColor);
		glLightfv(this->_lightId, GL_DIFFUSE, (float*)this->_diffuseColor);
		glLightfv(this->_lightId, GL_SPECULAR, (float*)this->_specularColor);
		glLightfv(this->_lightId, GL_SHININESS, &this->_shininess);
		glLightfv(this->_lightId, GL_SPOT_EXPONENT, &this->_spotExponent);
		glLightfv(this->_lightId, GL_SPOT_CUTOFF, &this->_spotCutoff);
		glLightfv(this->_lightId, GL_CONSTANT_ATTENUATION, &this->_constantAttenuation);
		glLightfv(this->_lightId, GL_LINEAR_ATTENUATION, &this->_linearAttenuation);
		glLightfv(this->_lightId, GL_QUADRATIC_ATTENUATION, &this->_quadraticAttenuation);
		Entity::Activate();
	}
}


// Deactivate object
void Light::Deactivate()
{
	Entity::Deactivate();
}


// Set object active status
void Light::SetActiveState(bool state)
{
	if( state && this->_lightId )
	{
		glLightfv(this->_lightId, GL_AMBIENT, (float*)this->_ambientColor);
		glLightfv(this->_lightId, GL_DIFFUSE, (float*)this->_diffuseColor);
		glLightfv(this->_lightId, GL_SPECULAR, (float*)this->_specularColor);
		glLightfv(this->_lightId, GL_SHININESS, &this->_shininess);
		glLightfv(this->_lightId, GL_SPOT_EXPONENT, &this->_spotExponent);
		glLightfv(this->_lightId, GL_SPOT_CUTOFF, &this->_spotCutoff);
		glLightfv(this->_lightId, GL_CONSTANT_ATTENUATION, &this->_constantAttenuation);
		glLightfv(this->_lightId, GL_LINEAR_ATTENUATION, &this->_linearAttenuation);
		glLightfv(this->_lightId, GL_QUADRATIC_ATTENUATION, &this->_quadraticAttenuation);
	}
	Entity::SetActiveState(state);
}


// Set the light to spot
void Light::MakeSpot()
{
	this->_isDirectional = false;
}


// Set the light to directional
void Light::MakeDirectional()
{
	this->_isDirectional = true;
}


// Get if the light is a spot light
bool Light::IsSpot()
{
	return !this->_isDirectional;
}


// Get if the light is direction light
bool Light::IsDirectional()
{
	return this->_isDirectional;
}


// Set light ambient color
void Light::SetAmbientColor(float r, float g, float b, float a)
{
	this->_ambientColor.r = r;
	this->_ambientColor.g = g;
	this->_ambientColor.b = b;
	this->_ambientColor.a = a;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_AMBIENT, (float*)this->_ambientColor);
	}
}

void Light::SetAmbientColor(Vector4f color)
{
	this->_ambientColor = color;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_AMBIENT, (float*)this->_ambientColor);
	}
}


// Get light ambient color
Vector4f Light::GetAmbientColor()
{
	return this->_ambientColor;
}


// Set light diffuse color
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	this->_diffuseColor.r = r;
	this->_diffuseColor.g = g;
	this->_diffuseColor.b = b;
	this->_diffuseColor.a = a;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_DIFFUSE, (float*)this->_diffuseColor);
	}
}

void Light::SetDiffuseColor(Vector4f color)
{
	this->_diffuseColor = color;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_DIFFUSE, (float*)this->_diffuseColor);
	}
}


// Get light diffuse color
Vector4f Light::GetDiffuseColor()
{
	return this->_diffuseColor;
}


// Set light specular color
void Light::SetSpecularColor(float r, float g, float b, float a)
{
	this->_specularColor.r = r;
	this->_specularColor.g = g;
	this->_specularColor.b = b;
	this->_specularColor.a = a;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_SPECULAR, (float*)this->_specularColor);
	}
}

void Light::SetSpecularColor(Vector4f color)
{
	this->_specularColor = color;

	if( this->_lightId )
	{
		glLightfv(this->_lightId, GL_SPECULAR, (float*)this->_specularColor);
	}
}


// Get light specular color
Vector4f Light::GetSpecularColor()
{
	return this->_specularColor;
}


// Set light shininess
void Light::SetShininess(float shininess)
{
	this->_shininess = shininess;

	glLightfv(this->_lightId, GL_SHININESS, &this->_shininess);
}


// Get light shininess
float Light::GetShininess()
{
	return this->_shininess;
}


// Set direction
void Light::SetDirection(float x, float y, float z)
{
	this->_direction.x = x;
	this->_direction.y = y;
	this->_direction.z = z;
}

void Light::SetDirection(Vector3f direction)
{
	this->_direction = direction;
}


// Get direction
Vector3f Light::GetDirection()
{
	return this->_direction;
}


// Set spot exponent
void Light::SetSpotExponent(float exponent)
{
	this->_spotExponent = exponent;
	glLightfv(this->_lightId, GL_SPOT_EXPONENT, &this->_spotExponent);
}


// Get spot exponent
float Light::GetSpotExponent()
{
	return this->_spotExponent;
}


// Set spot cutoff
void Light::SetSpotCutoff(float cutoff)
{
	this->_spotCutoff = cutoff;
	glLightfv(this->_lightId, GL_SPOT_CUTOFF, &this->_spotCutoff);
}


// Get spot cutoff
float Light::GetSpotCutoff()
{
	return this->_spotCutoff;
}


// Set constant attenuation
void Light::SetConstantAttenuation(float constant)
{
	this->_constantAttenuation = constant;
	glLightfv(this->_lightId, GL_CONSTANT_ATTENUATION, &this->_constantAttenuation);
}


// Set linear attenuation
void Light::SetLinearAttenuation(float constant)
{
	this->_linearAttenuation = constant;
	glLightfv(this->_lightId, GL_LINEAR_ATTENUATION, &this->_linearAttenuation);
}


// Set quadratic attenuation
void Light::SetQuadraticAttenuation(float constant)
{
	this->_quadraticAttenuation = constant;
	glLightfv(this->_lightId, GL_QUADRATIC_ATTENUATION, &this->_quadraticAttenuation);
}


// Get constant attenuation
float Light::GetConstantAttenuation()
{
	return this->_constantAttenuation;
}


// Get linear attenuation
float Light::GetLinearAttenuation()
{
	return this->_linearAttenuation;
}


// Get quadratic attenuation
float Light::GetQuadraticAttenuation()
{
	return this->_quadraticAttenuation;
}


// Render light
void Light::Render()
{
	// Set light position
	if( this->IsActive() )
	{
		glEnable(this->_lightId);

		if( this->_lightId )
		{
			if( this->_isDirectional )
			{
				glLightfv(this->_lightId, GL_POSITION, (float*)Vector4f(this->_direction.x, this->_direction.y, this->_direction.z, 0.0f));
			}
			else
			{
				glLightfv(this->_lightId, GL_POSITION, (float*)Vector4f(this->_position.x, this->_position.y, this->_position.z, 1.0f));
			}

			glLightfv(this->_lightId, GL_SPOT_DIRECTION, (float*)this->_direction);
		}

		// Render children
		Entity::Render();
	}
	else
	{
		glDisable(this->_lightId);
	}
}