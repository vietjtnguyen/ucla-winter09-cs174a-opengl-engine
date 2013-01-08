#ifndef ANIMATOR_H
#define ANIMATOR_H


#include <iostream>

#include "MathWrapper.h"
#include "Trash.h"
#include "Vectors.h"
#include "World.h"


using namespace std;


enum AnimPlayState
{
	Stop = 0,
	Forever = 1,
	OneShot = 2,
	Loop = 3,
	PingPong = 4
};


template <class T>
class Animator : public Trash
{
public:

	Animator()
	:Trash()
	,_t(0.0f)
	,_state(Stop)
	,_increasing(true)
	{
#ifdef DEBUG
		cout << "Animator constructor " << this << endl;
#endif
	}


	virtual ~Animator()
	{
#ifdef DEBUG
		cout << "Animator destructor " << this << endl;
#endif
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return t;
	}


	operator T()
	{
		return this->GetValue(this->_t);
	}


	T GetValue()
	{
		return this->GetValue(this->_t);
	}


	T operator ()(float t)
	{
		return this->GetValue(t);
	}


	T operator ()()
	{
		return this->GetValue();
	}


	void SetTime(float t)
	{
		this->_dt = 0.0f;
		this->_t = t;
	}


	void StepTime(float dt)
	{
		this->_dt = dt;
		this->_t += dt;
	}


	float& GetTime()
	{
		return this->_t;
	}


	void SetPlayState(AnimPlayState playState)
	{
		this->_state = playState;
	}


	AnimPlayState& GetPlayState()
	{
		return this->_state;
	}


	virtual void Update(float dt, float maxTime = 1.0f)
	{
		switch( this->_state )
		{
		case Forever:
			this->_dt = dt;
			this->_t += dt;
			break;
		case OneShot:
			this->_increasing = true;
			this->_dt = dt;
			this->_t += dt;
			if( this->_t > maxTime )
			{
				this->_t = maxTime;
				this->_state = Stop;
			}
			break;
		case Loop:
			this->_increasing = true;
			this->_dt = dt;
			this->_t += dt;
			if( this->_t > maxTime )
			{
				this->_t = fmod(this->_t, maxTime);
			}
			break;
		case PingPong:
			if( this->_increasing )
			{
				this->_dt = dt;
				this->_t += dt;
			}
			else
			{
				this->_dt = -dt;
				this->_t -= dt;
			}

			if( this->_t > maxTime )
			{
				this->_t = maxTime+(maxTime-this->_t);
				this->_increasing = false;
			}
			if( this->_t < 0.0f )
			{
				this->_t = 0.0f+(0.0f-this->_t);
				this->_increasing = true;
			}
			break;
		case Stop:
		default:
			this->_increasing = true;
			break;
		}
	}

protected:

	float			_t;
	float			_dt;

	AnimPlayState	_state;
	bool			_increasing;
};
typedef Animator<float>		Animatorf;
typedef Animator<Vector2f>	Animator2f;
typedef Animator<Vector3f>	Animator3f;
typedef Animator<Vector4f>	Animator4f;


inline float Approach(float current, float target, float speed, float dt)
{
	if( speed <= 0.0f || abs(target-current) <= 0.0001f )
	{
		return target;
	}
	
	return current+(target-current)*speed*dt;
}


#endif // ANIMATOR_H