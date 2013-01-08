#ifndef COMPOSITE_4_ANIMATOR_H
#define COMPOSITE_4_ANIMATOR_H


#include "Animator.h"


template <class T>
class Composite4 : public Animator< Vector4<T> >
{
public:

	Composite4(Animator<T> a, Animator<T> b, Animator<T> c, Animator<T> d)
	:Animator< Vector4<T> >()
	,_a(a)
	,_b(b)
	,_c(c)
	,_d(d)
	{
	}


	virtual ~Composite4()
	{
	}


	virtual Vector4<T> GetValue(float t)
	{
		return Vector4<T>(
			this->_a.GetValue(t),
			this->_b.GetValue(t),
			this->_c.GetValue(t),
			this->_d.GetValue(t));
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


	Animator<T>& GetAnimatorD()
	{
		return this->_d;
	}

protected:

	Animator<T>	_a;
	Animator<T>	_b;
	Animator<T>	_c;
	Animator<T>	_d;
};
typedef Composite4<float>	Composite4f;


#endif // COMPOSITE_4_ANIMATOR_H