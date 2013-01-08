#ifndef CUBIC_HERMITE_SPLINE_ANIMATOR_H
#define CUBIC_HERMITE_SPLINE_ANIMATOR_H


#include "Animator.h"


template <class T>
class CubicHermiteSpline : public Animator<T>
{
public:

	CubicHermiteSpline(T p0, T m0, T p1, T m1)
	:Animator<T>()
	,_p0(p0)
	,_m0(m0)
	,_p1(p1)
	,_m1(m1)
	{
	}


	virtual ~CubicHermiteSpline()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return
			this->_p0*(2*t*t*t-3*t*t+1)+
			this->_m0*(t*t*t-2*t*t+t)+
			this->_p1*(-2*t*t*t+3*t*t)+
			this->_m1*(t*t*t-t*t);
	}
	

	void SetFirstPoint(T p0)
	{
		this->_p0 = p0;
	}


	T& GetFirstPoint()
	{
		return this->_p0;
	}
	

	void SetFirstTangent(T m0)
	{
		this->_m0 = m0;
	}


	T& GetFirstTangent()
	{
		return this->_m0;
	}
	

	void SetSecondPoint(T p1)
	{
		this->_p1 = p1;
	}


	T& GetSecondPoint()
	{
		return this->_p1;
	}
	

	void SetSecondTangent(T m1)
	{
		this->_m1 = m1;
	}


	T& GetSecondTangent()
	{
		return this->_m1;
	}

protected:

	T	_p0;
	T	_m0;
	T	_p1;
	T	_m1;
};
typedef CubicHermiteSpline<float>		CubicHermiteSplinef;
typedef CubicHermiteSpline<Vector2f>	CubicHermiteSpline2f;
typedef CubicHermiteSpline<Vector3f>	CubicHermiteSpline3f;
typedef CubicHermiteSpline<Vector4f>	CubicHermiteSpline4f;


#endif // CUBIC_HERMITE_SPLINE_ANIMATOR_H