#include "Camera.h"
#include "Texture.h"

#include "Particle.h"

#include <GL/glut.h>


Particle::Particle()
:_type(ScreenFacing)
,_blendMode(Normal)
,_life(0.0f)
,_maxLife(0.0f)
,_position()
,_direction()
,_color(1.0f, 1.0f, 1.0f, 1.0f)
,_size(NULL)
,_depth(0.0f)
{
}


Particle::~Particle()
{
}


Particle::Type& Particle::GetType()
{
	return this->_type;
}


Particle::BlendMode& Particle::GetBlendMode()
{
	return this->_blendMode;
}


float& Particle::Life()
{
	return this->_life;
}


float& Particle::MaxLife()
{
	return this->_maxLife;
}


float& Particle::Rotation()
{
	return this->_rotation;
}


Vector3f& Particle::Position()
{
	return this->_position;
}


Vector3f& Particle::Velocity()
{
	return this->_velocity;
}


Vector3f& Particle::Direction()
{
	return this->_direction;
}


Vector4f& Particle::Color()
{
	return this->_color;
}


Animator2f*& Particle::Size()
{
	return this->_size;
}


void Particle::SetTexture(Texture* texture)
{
	this->_texture = texture;
}


Texture* Particle::GetTexture()
{
	return this->_texture;
}


float& Particle::Depth()
{
	return this->_depth;
}


void Particle::Update(float dt)
{
	this->_life -= dt;
	this->_position += this->_velocity*dt;
}


void Particle::Render(Camera* camera, unsigned int i, bool drawAxes)
{
	switch( this->_type )
	{
	case BillBoard:
		break;
	case VectorAligned:
		break;
	case ScreenFacing:
	default:
		{
			Vector3f particleToCamera = camera->GetPosition()-this->_position;
			this->_depth = particleToCamera.Length();

			Vector3f cameraYAxis = camera->GetEulerRotation()*Vector3f(sin(this->_rotation), cos(this->_rotation), 0.0f);
			Vector3f localX = cameraYAxis.Cross(particleToCamera);
			Vector3f localY = particleToCamera.Cross(localX);

			localX.Normalize();
			localY.Normalize();

			// Set blend mode
			switch( this->_blendMode )
			{
			case Subtractive:
				glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
				break;
			case Additive:
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
			case Normal:
			default:
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			}

			// Evaluate animators
			float t = 1.0f-this->_life/this->_maxLife;

			Vector2f size = this->_size->GetValue(t);

			// Bind texture
			if( this->_texture )
			{
				glBindTexture(GL_TEXTURE_2D, this->_texture->GetTextureName());
			}

			// Render
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			glBegin(GL_QUADS);

				glColor4f(this->_color.r, this->_color.g, this->_color.b, this->_color.a);

				// TODO (Viet Nguyen): Get rid of texture coordinate hacks!!!!

				glTexCoord2f(0.0f, 0.0f);
				glVertex3fv((float*)
					(this->_position+(-localX)*size.width+(-localY)*size.height));
				
				glTexCoord2f(1.0f/4.0f/*!!!!*/, 0.0f);
				glVertex3fv((float*)
					(this->_position+localX*size.width+(-localY)*size.height));
				
				glTexCoord2f(1.0f/4.0f/*!!!!*/, 1.0f);
				glVertex3fv((float*)
					(this->_position+localX*size.width+localY*size.height));
				
				glTexCoord2f(0.0f, 1.0f);
				glVertex3fv((float*)
					(this->_position+(-localX)*size.width+localY*size.height));

			glEnd();
				
			// Unbind texture
			if( this->_texture)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if( drawAxes )
			{
				glBegin(GL_LINES);
					glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

					glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
					glVertex3fv((float*)(this->_position));
					glVertex3fv((float*)(this->_position+localX*size.width));

					glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
					glVertex3fv((float*)(this->_position));
					glVertex3fv((float*)(this->_position+localY*size.height));

				glEnd();
			}
		}
	}
}