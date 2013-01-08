#include <iostream>

#include "Camera.h"
#include "Renderer.h"
#include "RenderOrder.h"
#include "World.h"

#include "Entity.h"

#include <GL/glut.h>


using namespace std;


vector<GlobalEntityList*> GlobalEntityList::_globalList;


// Constructor
Entity::Entity(bool active)
:_active(active)
,_position()
,_eulerRotation()
,_scale(1.0f, 1.0f, 1.0f)
,_parentList(NULL)
,_childList()
,_pivot()
,_inheritPosition(true)
,_inheritRotation(true)
,_inheritScale(false)
,_renderOrder(Midground)
,_drawAxes(false)
{
	this->_renderOrderItem = new MidgroundEntity(this);

#ifdef DEBUG
	cout << "Entity constructor " << this << endl;
#endif
}


// Destructor
Entity::~Entity()
{
	while( this->_parentList.size() > 0 )
	{
		this->Unparent(*(this->_parentList.begin()));
	}

#ifdef DEBUG
	cout << "Entity destructor " << this << endl;
#endif
}


// Activate object
void Entity::Activate()
{
	this->_active = true;
}


// Deactivate object
void Entity::Deactivate()
{
	this->_active = false;
}


// Set object active status
void Entity::SetActiveState(bool state)
{
	this->_active = state;
}


// Get object active state
bool Entity::IsActive()
{
	return this->_active;
}


// Set position by components
void Entity::SetPosition(float x, float y, float z)
{
	this->_position.Set(x, y, z);
}


// Set position by vector
void Entity::SetPosition(Vector3f position)
{
	this->SetPosition(position.x, position.y, position.z);
}


// Get position
Vector3f Entity::GetPosition()
{
	return this->_position;
}


// Access position
Vector3f& Entity::Position()
{
	return this->_position;
}


// Set euler rotation by components
void Entity::SetEulerRotation(float x, float y, float z)
{
	this->_eulerRotation.Set(x, y, z);
}


// Set euler rotation by vector
void Entity::SetEulerRotation(Vector3f eulerRotation)
{
	this->SetEulerRotation(eulerRotation.x, eulerRotation.y, eulerRotation.z);
}


// Get euler rotation
Vector3f Entity::GetEulerRotation()
{
	return this->_eulerRotation;
}


// Access euler rotation
Vector3f& Entity::EulerRotation()
{
	return this->_eulerRotation;
}


// Get rotation transformation matrix
Matrix33f Entity::GetRotationTransform()
{
	return Matrix33f::EulerRotate(this->_eulerRotation.x, this->_eulerRotation.y, this->_eulerRotation.z);
}


// Set scale by components
void Entity::SetScale(float x, float y, float z)
{
	this->_scale.Set(x, y, z);
}


// Set scale by vector
void Entity::SetScale(Vector3f scale)
{
	this->SetScale(scale.x, scale.y, scale.z);
}


// Get scale
Vector3f Entity::GetScale()
{
	return this->_scale;
}


// Access scale
Vector3f& Entity::Scale()
{
	return this->_scale;
}


// Parent entity
void Entity::Parent(Entity* parent)
{
	if( parent )
	{
		this->_parentList.push_back(parent);
		parent->_childList.push_back(this);
	}
}


// Unparent entity
void Entity::Unparent(Entity *parent)
{
	if( parent )
	{
		for( unsigned int i = 0; i < parent->_childList.size(); ++i )
		{
			if( parent->_childList.at(i) == this )
			{
				parent->_childList.erase(parent->_childList.begin()+i);
				break;
			}
		}
		
		for( unsigned int i = 0; i < this->_parentList.size(); ++i )
		{
			if( this->_parentList.at(i) == parent )
			{
				this->_parentList.erase(this->_parentList.begin()+i);
				break;
			}
		}
	}
}


// Set pivot by components
void Entity::SetPivot(float x, float y, float z)
{
	this->_pivot.Set(x, y, z);
}


// Set pivot by vector
void Entity::SetPivot(Vector3f pivot)
{
	this->SetPivot(pivot.x, pivot.y, pivot.z);
}


// Get pivot
Vector3f Entity::GetPivot()
{
	return this->_pivot;
}


// Access pivot
Vector3f& Entity::Pivot()
{
	return this->_pivot;
}


// Get number of parents
unsigned int Entity::CountParents()
{
	return this->_parentList.size();
}


// Clear parents
void Entity::ClearParents()
{
	for( unsigned int i = 0; i < this->_parentList.size(); ++i )
	{
		Entity* parent = this->_parentList.at(i);
		this->Unparent(parent);
	}
}


// Get number of children
unsigned int Entity::CountChildren()
{
	return this->_childList.size();
}


// Clear children
void Entity::ClearChildren()
{
	for( unsigned int i = 0; i < this->_childList.size(); ++i )
	{
		Entity* child = this->_childList.at(i);
		child->Unparent(this);
	}
}


// Set position inheritance
void Entity::SetInheritPosition(bool state)
{
	this->_inheritPosition = state;
}


// Get position inheritance
bool Entity::DoInheritPosition()
{
	return this->_inheritPosition;
}


// Set rotation inheritance
void Entity::SetInheritRotation(bool state)
{
	this->_inheritRotation = state;
}


// Get rotation inheritance
bool Entity::DoInheritRotation()
{
	return this->_inheritRotation;
}


// Set scale inheritance
void Entity::SetInheritScale(bool state)
{
	this->_inheritScale = state;
}


// Get scale inheritance
bool Entity::DoInheritScale()
{
	return this->_inheritScale;
}


// Set render order
void Entity::SetRenderOrder(RenderOrder renderOrder)
{
	if( this->_renderOrder != renderOrder )
	{
		this->_renderOrder = renderOrder;
		delete this->_renderOrderItem;
		
		switch( this->_renderOrder )
		{
		case Background:
			this->_renderOrderItem = new BackgroundEntity(this);
			break;
		case Midground:
			this->_renderOrderItem = new MidgroundEntity(this);
			break;
		case Foreground:
			this->_renderOrderItem = new ForegroundEntity(this);
			break;
		}
	}
}


// Get render order
Entity::RenderOrder Entity::GetRenderOrder()
{
	return this->_renderOrder;
}


// Set draw axes
void Entity::SetDrawAxes(bool state)
{
	this->_drawAxes = state;
}


// Do draw axes
bool Entity::DoDrawAxes()
{
	return this->_drawAxes;
}


// Render
void Entity::Render()
{	
	// Draw axes
	if( this->_drawAxes )
	{

		glPushMatrix();
			glTranslatef(this->_position.x, this->_position.y, this->_position.z);
			glRotatef(this->_eulerRotation.y, 0.0f, 1.0f, 0.0f);
			glRotatef(this->_eulerRotation.x, 1.0f, 0.0f, 0.0f);
			glRotatef(this->_eulerRotation.z, 0.0f, 0.0f, 1.0f);
			glScalef(this->_scale.x, this->_scale.y, this->_scale.z);

			DrawAxes(4.0f);
		glPopMatrix();
	}

	// Draw children
	for( unsigned int i = 0; i < this->_childList.size(); ++i )
	{
		Entity* child = this->_childList.at(i);
		if( child )
		{
			if( child->IsActive() )
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
}