#include <iostream>

#include "Renderer.h"
#include "Texture.h"

#include "Object.h"


using namespace std;


vector<GlobalObjectList*> GlobalObjectList::_globalList;


// Constructor
Object::Object(bool active)
:Entity(active)
,_list(NULL)
,_materialColors(NULL)
,_shininess(0.0f)
,_blendMode(Normal)
,_renderMode(Polygon)
,_renderSide(FrontFace)
,_texture(NULL)
{
	this->_list = glGenLists(1);

	this->_materialColors = new Vector4f[4];
	this->_materialColors[Ambient].Set(0.2f, 0.2f, 0.2f, 1.0f);
	this->_materialColors[Diffuse].Set(0.8f, 0.8f, 0.8f, 1.0f);
	this->_materialColors[Specular].Set(0.0f, 0.0f, 0.0f, 1.0f);
	this->_materialColors[Emission].Set(0.0f, 0.0f, 0.0f, 1.0f);

#ifdef DEBUG
	cout << "Object constructor " << this << endl;
#endif
}


// Destructor
Object::~Object()
{
	if( this->_list )
	{
		glDeleteLists(this->_list, 1);
	}

	if( this->_materialColors )
	{
		// TODO (Viet Nguyen): Figure out why this fails.
		//delete this->_materialColors;
	}

#ifdef DEBUG
	cout << "Object destructor " << this << endl;
#endif
}


// Begin recording mesh commands
void Object::StartRecording()
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);
	}
}


// Stop recording mesh commands
void Object::StopRecording()
{
	if( this->_list )
	{
		glEndList();
	}
}


// Clear mesh
void Object::Clear()
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);
		glEndList();
	}
}


// Create plane
void Object::CreatePlane(float width, float length)
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);

			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, 0.0f, -length);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0.0f, -length);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(width, 0.0f, length);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, 0.0f, length);
			glEnd();

		glEndList();
	}
}


// Create cube
void Object::CreateCube(float size)
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);

		glutSolidCube(size);

		glEndList();
	}
}


// Create cone
void Object::CreateCone(float radius, float height, unsigned int slices, unsigned int stacks)
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);

		glutSolidCone(radius, height, slices, stacks);

		glEndList();
	}
}


// Create sphere
void Object::CreateSphere(float radius, unsigned int slices, unsigned int stacks)
{
	if( this->_list )
	{
		glNewList(this->_list, GL_COMPILE);

		GLUquadric* quadric;
		if( quadric = gluNewQuadric() )
		{
			gluQuadricTexture(quadric, GL_TRUE);
			gluQuadricNormals(quadric, GLU_SMOOTH);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			gluSphere(quadric, radius, slices, stacks);
			gluDeleteQuadric(quadric);
		}

		glEndList();
	}
}


// Set material color
void Object::SetColor(MaterialType type, Vector4f rgba)
{
	this->_materialColors[(unsigned int)type] = rgba;
}


// Get material color
Vector4f Object::GetColor(MaterialType type)
{
	return this->_materialColors[(unsigned int)type];
}


// Access material color
Vector4f& Object::Color(MaterialType type)
{
	return this->_materialColors[(unsigned int)type];
}


// Set shininess
void Object::SetShininess(float shininess)
{
	this->_shininess = shininess;
}


// Get shininess
float Object::GetShininess()
{
	return this->_shininess;
}


// Access shininess
float& Object::Shininess()
{
	return this->_shininess;
}


// Set blend mode
void Object::SetBlendMode(BlendMode blendMode)
{
	this->_blendMode = blendMode;
}


// Get blend mode
Object::BlendMode Object::GetBlendMode()
{
	return this->_blendMode;
}


// Set render mode
void Object::SetRenderMode(RenderMode renderMode)
{
	this->_renderMode = renderMode;
}


// Get render mode
Object::RenderMode Object::GetRenderMode()
{
	return this->_renderMode;
}


// Set render side
void Object::SetRenderSide(RenderSide renderSide)
{
	this->_renderSide = renderSide;
}


// Get render side
Object::RenderSide Object::GetRenderSide()
{
	return this->_renderSide;
}


// Set texture
void Object::SetTexture(Texture* texture)
{
	if( texture )
	{
		if( texture->IsValid() )
		{
			this->_texture = texture;
		}
	}
}


// Clear texture
void Object::ClearTexture()
{
	this->_texture = NULL;
}


// Get texture
Texture* Object::GetTexture()
{
	return this->_texture;
}


// Render object
void Object::Render()
{
	static GLuint renderModeMap[3];
	renderModeMap[0] = GL_POINT;
	renderModeMap[1] = GL_LINE;
	renderModeMap[2] = GL_FILL;

	if( this->IsActive() )
	{

		// Draw meshes
		if( this->_list )
		{
			glPushMatrix();

				glTranslatef(this->_position.x, this->_position.y, this->_position.z);
				glRotatef(this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
				glRotatef(this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
				glRotatef(this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
				glScalef(this->_scale.x, this->_scale.y, this->_scale.z);
				glTranslatef(-this->_pivot.x, -this->_pivot.y, -this->_pivot.z);

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

				// Set render mode
				glPolygonMode(GL_FRONT_AND_BACK, renderModeMap[(int)this->_renderMode]);

				// Set render side
				switch( this->_renderSide )
				{
				case BackFace:
					glFrontFace(GL_CW);
					glEnable(GL_CULL_FACE);
					break;
				case DoubleSided:
					glFrontFace(GL_CCW);
					glDisable(GL_CULL_FACE);
					break;
				case FrontFace:
				default:
					glFrontFace(GL_CCW);
					glEnable(GL_CULL_FACE);
					break;
				}

				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
				glColor4fv((float*)&this->_materialColors[Ambient]);

				glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
				glColor4fv((float*)&this->_materialColors[Diffuse]);

				glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
				glColor4fv((float*)&this->_materialColors[Specular]);

				glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
				glColor4fv((float*)&this->_materialColors[Emission]);

				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &this->_shininess);
				
				if( this->_texture )
				{
					glBindTexture(GL_TEXTURE_2D, this->_texture->GetTextureName());
				}

				glCallList(this->_list);
				
				if( this->_texture)
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}

			glPopMatrix();
		}

		// Draw children
		Entity::Render();
	}
}