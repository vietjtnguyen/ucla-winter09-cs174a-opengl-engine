#ifndef EASE_ANIMATOR
#define EASE_ANIMATOR


#include "Animator.h"


template <class T>
class Ease : public Animator<T>
{
public:

	Ease(T a, T b, float amount = 1.0f)
	:_chSpline(Vector2<T>(0, a), Vector2<T>(amount, 0), Vector2<T>(1, b), Vector2<T>(amount, 0))
	{
	}


	virtual ~Ease()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return this->_chSpline.GetValue(t).y;
	}


	void SetA(T a)
	{
		this->_chSpline.SetFirstPoint(0, a);
	}


	T GetA()
	{
		return this->_chSpline.GetFirstPoint().y;
	}

protected:

	CubicHermiteSpline< Vector2<T> >	_chSpline;
};
typedef Ease<float>		Easef;
typedef Ease<Vector2f>	Ease2f;
typedef Ease<Vector3f>	Ease3f;
typedef Ease<Vector4f>	Ease4f;


#endif // EASE_ANIMATOR