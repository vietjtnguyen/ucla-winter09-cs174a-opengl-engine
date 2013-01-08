#ifndef TANK_H
#define TANK_H


#include "Entity.h"


class Mesh;
class Terrain;
class Texture;


class Tank : public Entity
{
public:

	Tank();

	virtual ~Tank();

	void OrientToTerrain(Terrain* terrain, float dt, bool draw = false);
	void ResetCornerHeights();

	void OrientTurret(float ax, float ay);
	Vector2f GetTurretOrientation();
	void PointTurret(Vector3f target);

	void SetTargetVelocity(float velocity);
	float GetTargetVelocity();
	float& TargetVelocity();

	void SetTargetPosition(Vector3f pos);
	Vector3f GetTargetPosition();
	Vector3f& TargetPosition();

	void Update(float dt, Terrain* terrain);

	void Explode(Terrain* terrain);

private:

	static const float		_turnSpeedFactor;
	static const float		_accelerationFactor;

	static const float		_floatSpeed;
	static const float		_floatHeight;

	static const Vector3f	_topOffset;
	static const Vector3f	_turretOffset;
	static const Vector3f	_turretTipOffset;
	static const Vector3f	_size;

	static Texture*			_texture;
	static Mesh*			_base;
	static Mesh*			_top;
	static Mesh*			_turret;

	Entity*					_topPivot;
	Entity*					_turretPivot;
	Entity*					_turretTip;

	Vector3f				_lbCornerPos;
	Vector3f				_rbCornerPos;
	Vector3f				_rfCornerPos;
	Vector3f				_lfCornerPos;

	float					_velocity;
	float					_targetVelocity;
	Vector3f				_targetPos;

	bool					_exploded;
	Vector3f				_baseVelocity;
	Vector3f				_topVelocity;
	Vector3f				_turretVelocity;

};


#endif // TANK_H