#ifndef ENTITY_H
#define ENTITY_H


#include <vector>

#include "GlobalList.h"
#include "Matrices.h"
#include "Trash.h"
#include "Vectors.h"


using namespace std;


class RenderOrderItem;


class Entity : public GlobalList<Entity>, public Trash
{
public:

	Entity(bool active = true);

	virtual ~Entity();

	// TODO (Viet Nguyen): Check if these should these be implemented.
	Entity(const Entity& other);
	Entity& operator=(const Entity& other);

	virtual void Activate();
	virtual void Deactivate();
	virtual void SetActiveState(bool state);
	bool IsActive();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3f position);
	Vector3f GetPosition();
	Vector3f& Position();

	void SetEulerRotation(float x, float y, float z);
	void SetEulerRotation(Vector3f eulerRotation);
	Vector3f GetEulerRotation();
	Vector3f& EulerRotation();
	Matrix33f GetRotationTransform();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3f scale);
	Vector3f GetScale();
	Vector3f& Scale();

	void Parent(Entity* parent);
	void Unparent(Entity* parent);

	// TODO (Viet Nguyen): Fix pivot functionality.
	void SetPivot(float x, float y, float z);
	void SetPivot(Vector3f pivot);
	Vector3f GetPivot();
	Vector3f& Pivot();

	unsigned int CountParents();
	void ClearParents();
	unsigned int CountChildren();
	void ClearChildren();

	void SetInheritPosition(bool state);
	bool DoInheritPosition();
	void SetInheritRotation(bool state);
	bool DoInheritRotation();
	void SetInheritScale(bool state);
	bool DoInheritScale();

	enum RenderOrder
	{
		Midground = 0,
		Foreground = 1,
		Background = 2
	};
	void SetRenderOrder(RenderOrder renderOrder);
	RenderOrder GetRenderOrder();

	void SetDrawAxes(bool state);
	bool DoDrawAxes();

	virtual void Render();

protected:

	bool				_active;

	Vector3f			_position;
	Vector3f			_eulerRotation;
	Vector3f			_scale;

	vector<Entity*>		_parentList;
	vector<Entity*>		_childList;
	Vector3f			_pivot;

	bool				_inheritPosition;
	bool				_inheritRotation;
	bool				_inheritScale;

	RenderOrder			_renderOrder;
	RenderOrderItem*	_renderOrderItem;

	bool				_drawAxes;

};
typedef Entity::GlobalList<Entity> GlobalEntityList;


#endif // ENTITY_H