#ifndef LERP_ANIMATOR_H
#define LERP_ANIMATOR_H


#include "Animator.h"
#include "Vectors.h"


template <class T>
class Lerp : public Animator<T>
{
public:

	Lerp(T a, T b)
	:Animator<T>()
	,_a(a)
	,_b(b)
	{
	}


	virtual ~Lerp()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return this->_a*(1.0f-t)+this->_b*t;
	}


	void SetA(T a)
	{
		this->_a = a;
	}


	T& GetA()
	{
		return this->_a;
	}


	void SetB(T b)
	{
		this->_b = b;
	}


	T& GetB()
	{
		return this->_b;
	}

protected:

	T	_a;
	T	_b;
};
typedef Lerp<float>		Lerpf;
typedef Lerp<Vector2f>	Lerp2f;
typedef Lerp<Vector3f>	Lerp3f;
typedef Lerp<Vector4f>	Lerp4f;


#endif // LERP_ANIMATOR_H