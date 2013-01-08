#ifndef COMPOSITE_3_ANIMATOR_H
#define COMPOSITE_3_ANIMATOR_H


#include "Animator.h"


template <class T>
class Composite3 : public Animator< Vector3<T> >
{
public:

	Composite3(Animator<T> a, Animator<T> b, Animator<T> c)
	:Animator< Vector3<T> >()
	,_a(a)
	,_b(b)
	,_c(c)
	{
	}


	virtual ~Composite3()
	{
	}


	virtual Vector3<T> GetValue(float t)
	{
		return Vector3<T>(
			this->_a.GetValue(t),
			this->_b.GetValue(t),
			this->_c.GetValue(t));
	}


	Animator<T>& GetAnimatorA()
	{
		return this->_a;
	}


	Animator<T>& GetAnimatorB()
	{
		return this->_b;
	}


	Animator<T>& GetAnimatorC()
	{
		return this->_c;
	}

protected:

	Animator<T>	_a;
	Animator<T>	_b;
	Animator<T>	_c;
};
typedef Composite3<float>	Composite3f;


#endif // COMPOSITE_3_ANIMATOR_H