#include "Animator.h"
#include "BitmapImage.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Terrain.h"
#include "Texture.h"

#include "Tank.h"


const float Tank::_turnSpeedFactor = 0.5f;
const float	Tank::_accelerationFactor = 5.0f;

const float Tank::_floatSpeed = 8.0f;
const float Tank::_floatHeight = 12.0f;

const Vector3f Tank::_topOffset(0.0f, 14.235f, 11.815f);
const Vector3f Tank::_turretOffset(0.0f, 20.781f, 1.678f);
const Vector3f Tank::_turretTipOffset(0.0f, 20.155f, -18.884);
const Vector3f Tank::_size(16.3675f, 36.009f, 25.512f);

Texture* Tank::_texture = NULL;
Mesh* Tank::_base = NULL;
Mesh* Tank::_top = NULL;
Mesh* Tank::_turret = NULL;


Tank::Tank()
:Entity()
,_topPivot(NULL)
,_turretPivot(NULL)
,_turretTip(NULL)
,_lbCornerPos()
,_rbCornerPos()
,_rfCornerPos()
,_lfCornerPos()
,_velocity(0.0f)
,_targetVelocity(0.0f)
,_targetPos()
,_exploded(false)
{
	// Initialize prototypes
	if( Tank::_texture == NULL )
	{
		Tank::_texture = new Texture(new BitmapImage("media/tankColor.bmp"));
	}

	if( Tank::_base == NULL )
	{
		Tank::_base = new Mesh("media/tankBase.3ds");
		Tank::_base->SetTexture(Tank::_texture);
	}

	if( Tank::_top == NULL )
	{
		Tank::_top = new Mesh("media/tankTop.3ds");
		Tank::_top->SetTexture(Tank::_texture);
		Tank::_top->TransformVertices(Matrix44f::Translate(-Tank::_topOffset.x, -Tank::_topOffset.y, -Tank::_topOffset.z));
		Tank::_top->Update();
	}

	if( Tank::_turret == NULL )
	{
		Tank::_turret = new Mesh("media/tankTurret.3ds");
		Tank::_turret->SetTexture(Tank::_texture);
		Tank::_turret->TransformVertices(Matrix44f::Translate(-Tank::_turretOffset.x, -Tank::_turretOffset.y, -Tank::_turretOffset.z));
		Tank::_turret->Update();
	}

	// Create hierarchy
	this->_topPivot = new Entity();
	this->_topPivot->Parent((Entity*)this);
	this->_topPivot->SetPosition(Tank::_topOffset);

	this->_turretPivot = new Entity();
	this->_turretPivot->Parent(this->_topPivot);
	this->_turretPivot->SetPosition(Tank::_turretOffset-this->_topPivot->Position());

	this->_turretTip = new Entity();
	this->_turretTip->Parent(this->_turretPivot);
	this->_turretTip->SetPosition(Tank::_turretTipOffset-this->_turretPivot->Position());

	// Parent prototypes to pivots
	Tank::_base->Parent((Entity*)this);
	Tank::_top->Parent(this->_topPivot);
	Tank::_turret->Parent(this->_turretPivot);
}


Tank::~Tank()
{
}


void Tank::OrientToTerrain(Terrain* terrain, float dt, bool draw)
{
	if( !this->_exploded )
	{
		Matrix33f localToWorldRot = this->GetRotationTransform();
		Vector3f localXInWorld = localToWorldRot*Vector3f(1.0f, 0.0f, 0.0f);
		Vector3f localZInWorld = localToWorldRot*Vector3f(0.0f, 0.0f, 1.0f);

		float oldLbCornerHeight = this->_lbCornerPos.y;
		float oldRbCornerHeight = this->_rbCornerPos.y;
		float oldRfCornerHeight = this->_rfCornerPos.y;
		float oldLfCornerHeight = this->_lfCornerPos.y;

		this->_lbCornerPos = this->_position
			+(-localXInWorld*Tank::_size.width)
			+( localZInWorld*Tank::_size.depth);
		this->_rbCornerPos = this->_position
			+( localXInWorld*Tank::_size.width)
			+( localZInWorld*Tank::_size.depth);
		this->_rfCornerPos = this->_position
			+( localXInWorld*Tank::_size.width)
			+(-localZInWorld*Tank::_size.depth);
		this->_lfCornerPos = this->_position
			+(-localXInWorld*Tank::_size.width)
			+(-localZInWorld*Tank::_size.depth);

		this->_lbCornerPos.y = Approach(oldLbCornerHeight, terrain->GetScaledHeight(this->_lbCornerPos)+Tank::_floatHeight, Tank::_floatSpeed, dt);
		this->_rbCornerPos.y = Approach(oldRbCornerHeight, terrain->GetScaledHeight(this->_rbCornerPos)+Tank::_floatHeight, Tank::_floatSpeed, dt);
		this->_rfCornerPos.y = Approach(oldRfCornerHeight, terrain->GetScaledHeight(this->_rfCornerPos)+Tank::_floatHeight, Tank::_floatSpeed, dt);
		this->_lfCornerPos.y = Approach(oldLfCornerHeight, terrain->GetScaledHeight(this->_lfCornerPos)+Tank::_floatHeight, Tank::_floatSpeed, dt);

		this->_position.y = (this->_lbCornerPos.y+this->_rbCornerPos.y+this->_rfCornerPos.y+this->_lfCornerPos.y)*0.25f;

		float fHeight = (this->_lfCornerPos.y+this->_rfCornerPos.y)*0.5f;
		float bHeight = (this->_lbCornerPos.y+this->_rbCornerPos.y)*0.5f;
		float lHeight = (this->_lfCornerPos.y+this->_lbCornerPos.y)*0.5f;
		float rHeight = (this->_rfCornerPos.y+this->_rbCornerPos.y)*0.5f;
		this->_eulerRotation.x = RadToDeg(atan2(Tank::_size.depth*2.0f, bHeight-fHeight))-90.0f;
		this->_eulerRotation.z = RadToDeg(atan2(Tank::_size.width*2.0f, lHeight-rHeight))-90.0f;

		// Debug drawing
		if( draw )
		{
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);

			glBegin(GL_LINES);
				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glVertex3fv((float*)this->_position);
				glVertex3fv((float*)(this->_position+localXInWorld*8.0f));

				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glVertex3fv((float*)this->_position);
				glVertex3fv((float*)(this->_position+localZInWorld*8.0f));

				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glVertex3fv((float*)this->_lbCornerPos);
				glVertex3fv((float*)this->_rbCornerPos);
				glVertex3fv((float*)this->_rbCornerPos);
				glVertex3fv((float*)this->_rfCornerPos);
				glVertex3fv((float*)this->_rfCornerPos);
				glVertex3fv((float*)this->_lfCornerPos);
				glVertex3fv((float*)this->_lfCornerPos);
				glVertex3fv((float*)this->_lbCornerPos);
			glEnd();

			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
		}
	}
}


// Reset corner heights to the current height
void Tank::ResetCornerHeights()
{
	this->_lbCornerPos.y = this->_position.y;
	this->_rbCornerPos.y = this->_position.y;
	this->_rfCornerPos.y = this->_position.y;
	this->_lfCornerPos.y = this->_position.y;
}


// Note (Viet Nguyen): ax positive up, ay positive ccw
void Tank::OrientTurret(float ax, float ay)
{
	this->_topPivot->SetEulerRotation(0.0f, ay, 0.0f);
	this->_turretPivot->SetEulerRotation(ax, 0.0f, 0.0f);
}


Vector2f Tank::GetTurretOrientation()
{
	return Vector2f(this->_turretPivot->GetEulerRotation().x, this->_topPivot->GetEulerRotation().y);
}


void Tank::PointTurret(Vector3f target)
{
}


void Tank::SetTargetVelocity(float velocity)
{
	this->_targetVelocity = velocity;
}


float Tank::GetTargetVelocity()
{
	return this->_targetVelocity;
}


float& Tank::TargetVelocity()
{
	return this->_targetVelocity;
}


void Tank::SetTargetPosition(Vector3f pos)
{
	this->_targetPos = pos;
}


Vector3f Tank::GetTargetPosition()
{
	return this->_targetPos;
}


Vector3f& Tank::TargetPosition()
{
	return this->_targetPos;
}


// Update movement
void Tank::Update(float dt, Terrain* terrain)
{
	if( !this->_exploded )
	{
		Vector3f direction = this->_targetPos-this->_position;
		if( Vector2f(direction.x, direction.z).Length() <= 96.0f )
		{
			this->_targetVelocity = 0.0f;
		}

		float targetAngle = RadToDeg(atan2(-direction.z, direction.x))-90.0f;
		this->_eulerRotation.y = Approach(this->_eulerRotation.y, targetAngle, Tank::_turnSpeedFactor, dt);

		this->_velocity = Approach(this->_velocity, this->_targetVelocity, Tank::_accelerationFactor, dt);
		this->_position.x += -Sin(this->_eulerRotation.y)*this->_velocity*dt;
		this->_position.z += -Cos(this->_eulerRotation.y)*this->_velocity*dt;
	}
	else
	{
		if( this->GetPosition().y > terrain->GetScaledHeight(this->GetPosition()) )
		{
			this->_baseVelocity.y -= 4.0f*dt;
			this->SetPosition(this->GetPosition()+this->_baseVelocity*dt);
		}

		//if( this->_topPivot->GetPosition().y > terrain->GetScaledHeight(this->_topPivot->GetPosition()) )
		//{
		//	this->_topVelocity.y -= 0.1f*dt;
		//	this->_topPivot->SetPosition(this->_topPivot->GetPosition()+this->_topVelocity*dt);
		//}

		//if( this->_turretPivot->GetPosition().y > terrain->GetScaledHeight(this->_turretPivot->GetPosition()) )
		//{
		//	this->_turretVelocity.y -= 0.1f*dt;
		//	this->_turretPivot->SetPosition(this->_turretPivot->GetPosition()+this->_turretVelocity*dt);
		//}
	}
}


void Tank::Explode(Terrain* terrain)
{
	//this->_topPivot->ClearParents();
	//this->_turretPivot->ClearParents();

	this->_position.y = terrain->GetScaledHeight(this->GetPosition())+32.0f;
	//this->_topPivot->SetPosition(this->_position);
	//this->_turretPivot->SetPosition(this->_position);

	this->_baseVelocity.Set(Rnd(-6.0f, 6.0f), Rnd(20.0f, 40.0f), Rnd(-6.0f, 6.0f));
	//this->_topVelocity.Set(Rnd(-6.0f, 6.0f), Rnd(10.0f, 16.0f), Rnd(-6.0f, 6.0f));
	//this->_turretVelocity.Set(Rnd(-6.0f, 6.0f), Rnd(10.0f, 16.0f), Rnd(-6.0f, 6.0f));

	this->_exploded = true;
}