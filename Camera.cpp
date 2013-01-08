#include <iostream>

#include "MathWrapper.h"
#include "Object.h"
#include "PointManager.h"
#include "Renderer.h"
#include "RenderOrder.h"

#include "Camera.h"


using namespace std;


vector<GlobalCameraList*> GlobalCameraList::_globalList;


// Constructor
Camera::Camera(
	bool windowRelative,
	Vector2f viewportPosition, Vector2f viewportSize,
	float fov, float nearDraw, float farDraw,
	GLenum drawBuffer, bool active)
:Entity(active)
,_windowRelative(windowRelative)
,_viewportPosition(viewportPosition)
,_viewportSize(viewportSize)
,_actualViewportPosition()
,_actualViewportSize()
,_aspectRatio(0.0f)
,_fieldOfView(fov)
,_nearDraw(nearDraw)
,_farDraw(farDraw)
,_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
,_drawBuffer(drawBuffer)
{
	this->UpdateViewport();

#ifdef DEBUG
	cout << "Camera constructor " << this << endl;
#endif
}


// Destructor
Camera::~Camera()
{
#ifdef DEBUG
	cout << "Camera destructor " << this << endl;
#endif
}


// Set viewport window relative state
void Camera::SetViewportWindowRelative(bool state)
{
	this->_windowRelative = state;
}


// Get viewport window relative state
bool Camera::IsViewportWindowRelative()
{
	return this->_windowRelative;
}


// Set viewport position
void Camera::SetViewportPosition(float x, float y)
{
	this->_viewportPosition.Set(x, y);
	this->UpdateViewport();
}


// Set viewport position from vector
void Camera::SetViewportPosition(Vector2f position)
{
	this->SetViewportPosition(position.x, position.y);
}


// Get viewport position
Vector2f Camera::GetViewportPosition()
{
	return this->_viewportPosition;
}


// Set viewport size
void Camera::SetViewportSize(float width, float height)
{
	this->_viewportSize.Set(width, height);
	this->UpdateViewport();
}


// Set viewport size from vector
void Camera::SetViewportSize(Vector2f size)
{
	this->SetViewportSize(size.width, size.height);
}


// Get viewport size
Vector2f Camera::GetViewportSize()
{
	return this->_viewportSize;
}


// Get aspect ratio
float Camera::GetAspectRatio()
{
	return this->_aspectRatio;
}


// Set field of view (in degrees)
void Camera::SetFieldOfView(float degrees)
{
	this->_fieldOfView = degrees;
}


// Get field of view
float Camera::GetFieldOfView()
{
	return this->_fieldOfView;
}


// Set near draw distance
void Camera::SetNearDraw(float nearDraw)
{
	this->_nearDraw = nearDraw;
}


// Get near draw distance
float Camera::GetNearDraw()
{
	return this->_nearDraw;
}


// Set far draw distance
void Camera::SetFarDraw(float farDraw)
{
	this->_farDraw = farDraw;
}


// Get far draw distance
float Camera::GetFarDraw()
{
	return this->_farDraw;
}


// Set screen clear color
void Camera::SetClearColor(float r, float g, float b, float a)
{
	this->_clearColor.Set(r, g, b, a);
}

void Camera::SetClearColor(Vector4f color)
{
	this->SetClearColor(color.r, color.g, color.b, color.a);
}


// Get screen clear color
Vector4f Camera::GetClearColor()
{
	return this->_clearColor;
}


// Set draw buffer
void Camera::SetDrawBuffer(GLenum drawBuffer)
{
	this->_drawBuffer = drawBuffer;
}


// Get draw buffer
GLenum Camera::GetDrawBuffer()
{
	return this->_drawBuffer;
}


// Update viewport
void Camera::UpdateViewport()
{
	if( this->_windowRelative )
	{
		World* world = WorldSingleton::Get();

		this->_actualViewportPosition.x =
			(int)((float)world->GetWindowSize().width*this->_viewportPosition.x);
		this->_actualViewportPosition.y =
			(int)((float)world->GetWindowSize().height*this->_viewportPosition.y);

		this->_actualViewportSize.width =
			(int)((float)world->GetWindowSize().width*this->_viewportSize.width);
		this->_actualViewportSize.height =
			(int)((float)world->GetWindowSize().height*this->_viewportSize.height);

		this->_aspectRatio =
			(float)this->_actualViewportSize.width/(float)this->_actualViewportSize.height;
	}
	else
	{
		this->_actualViewportPosition.x = (int)this->_viewportPosition.x;
		this->_actualViewportPosition.y = (int)this->_viewportPosition.y;

		this->_actualViewportSize.width = (int)this->_viewportSize.width;
		this->_actualViewportSize.height = (int)this->_viewportSize.height;

		// NOTE (Viet Nguyen): This might not be necessary...
		this->_aspectRatio =
			(float)this->_actualViewportSize.width/(float)this->_actualViewportSize.height;
	}
}


// Render
void Camera::Draw()
{
	// Get world
	World* world = WorldSingleton::Get();

	glDrawBuffer(this->_drawBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(
		this->_actualViewportPosition.x, this->_actualViewportPosition.y,
		this->_actualViewportSize.width, this->_actualViewportSize.height);

	// Set camera transformations
	gluPerspective(this->_fieldOfView, this->_aspectRatio, this->_nearDraw, this->_farDraw);
	glRotatef(-this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
	glRotatef(-this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(-this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(-this->_position.x, -this->_position.y, -this->_position.z);

	// Render if active
	if( this->_active )
	{

		// Clear screen
		float* clearColor = this->GetClearColor();
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render objects
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Background scene
		for( unsigned int i = 0; i < GlobalBackgroundEntityList::GetListSize(); ++i )
		{
			Entity* entity = GlobalBackgroundEntityList::GetListItem(i)->GetEntity();
			if( entity->CountParents() == 0 && entity->IsActive() )
			{
				entity->Render();
			}
		}

		// Draw children (background)
		for( unsigned int i = 0; i < this->_childList.size(); ++i )
		{
			Entity* child = this->_childList.at(i);
			if( child )
			{
				if( child->IsActive() && child->GetRenderOrder() == Entity::Background )
				{
					glPushMatrix();

						if( child->DoInheritPosition() )
						{
							glTranslatef(this->_position.x, this->_position.y, this->_position.z);
						}
						if( child->DoInheritRotation() )
						{
							glRotatef(this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
							glRotatef(this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
							glRotatef(this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
						}
						if( child->DoInheritScale() )
						{
							glScalef(this->_scale.x, this->_scale.y, this->_scale.z);
						}

						child->Render();

					glPopMatrix();
				}
			}
		}

		glClear(GL_DEPTH_BUFFER_BIT);

		// Midground scene
		for( unsigned int i = 0; i < GlobalMidgroundEntityList::GetListSize(); ++i )
		{
			Entity* entity = GlobalMidgroundEntityList::GetListItem(i)->GetEntity();
			if( entity->CountParents() == 0 && entity->IsActive() )
			{
				entity->Render();
			}
		}

		// Draw children (midground)
		for( unsigned int i = 0; i < this->_childList.size(); ++i )
		{
			Entity* child = this->_childList.at(i);
			if( child )
			{
				if( child->IsActive() && child->GetRenderOrder() == Entity::Midground )
				{
					glPushMatrix();

						if( child->DoInheritPosition() )
						{
							glTranslatef(this->_position.x, this->_position.y, this->_position.z);
						}
						if( child->DoInheritRotation() )
						{
							glRotatef(this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
							glRotatef(this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
							glRotatef(this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
						}
						if( child->DoInheritScale() )
						{
							glScalef(this->_scale.x, this->_scale.y, this->_scale.z);
						}

						child->Render();

					glPopMatrix();
				}
			}
		}

		// Draw particles
		PointManager* pointManager = PointManagerSingleton::Get();
		pointManager->Render(this);

		// Foreground scene
		glDisable(GL_DEPTH_TEST);

		for( unsigned int i = 0; i < GlobalForegroundEntityList::GetListSize(); ++i )
		{
			Entity* entity = GlobalForegroundEntityList::GetListItem(i)->GetEntity();
			if( entity->CountParents() == 0 && entity->IsActive() )
			{
				entity->Render();
			}
		}

		// Draw children (foreground)
		for( unsigned int i = 0; i < this->_childList.size(); ++i )
		{
			Entity* child = this->_childList.at(i);
			if( child )
			{
				if( child->IsActive() && child->GetRenderOrder() == Entity::Foreground )
				{
					glPushMatrix();

						if( child->DoInheritPosition() )
						{
							glTranslatef(this->_position.x, this->_position.y, this->_position.z);
						}
						if( child->DoInheritRotation() )
						{
							glRotatef(this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
							glRotatef(this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
							glRotatef(this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
						}
						if( child->DoInheritScale() )
						{
							glScalef(this->_scale.x, this->_scale.y, this->_scale.z);
						}

						child->Render();

					glPopMatrix();
				}
			}
		}

		glEnable(GL_DEPTH_TEST);

		// Call render functions
		vector<WorldInitFunc>* renderFuncs = World::GetRenderFunctions();
		for( unsigned int i = 0; i < renderFuncs->size(); ++i )
		{
			WorldInitFunc func = renderFuncs->at(i);
			(*func)();
		}

	}
}


void Camera::Render()
{
}