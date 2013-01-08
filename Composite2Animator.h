#ifndef COMPOSITE_2_ANIMATOR_H
#define COMPOSITE_2_ANIMATOR_H


#include "Animator.h"


template <class T>
class Composite2 : public Animator< Vector2<T> >
{
public:

	Composite2(Animator<T> a, Animator<T> b)
	:Animator< Vector2<T> >()
	,_a(a)
	,_b(b)
	{
	}


	virtual ~Composite2()
	{
	}


	virtual Vector2<T> GetValue(float t)
	{
		return Vector2<T>(
			this->_a.GetValue(t),
			this->_b.GetValue(t));
	}


	Animator<T>& GetAnimatorA()
	{
		return this->_a;
	}


	Animator<T>& GetAnimatorB()
	{
		return this->_b;
	}

protected:

	Animator<T>	_a;
	Animator<T>	_b;
};
typedef Composite2<float>	Composite2f;


#endif // COMPOSITE_2_ANIMATOR_H