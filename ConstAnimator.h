#ifndef CONST_ANIMATOR_H
#define CONST_ANIMATOR_H


#include "Animator.h"
#include "Vectors.h"


template <class T>
class Constant : public Animator<T>
{
public:

	Constant(T a)
	:Animator<T>()
	,_a(a)
	{
	}


	virtual ~Constant()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return this->_a;
	}


	void SetValue(T a)
	{
		this->_a = a;
	}


	T& GetValue()
	{
		return this->_a;
	}

protected:

	T	_a;
};
typedef Constant<float>		Constantf;
typedef Constant<Vector2f>	Constant2f;
typedef Constant<Vector3f>	Constant3f;
typedef Constant<Vector4f>	Constant4f;


#endif // CONST_ANIMATOR_H