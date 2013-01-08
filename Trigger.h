#ifndef TRIGGER_H
#define TRIGGER_H


#include "Animator.h"


class Trigger : public Animator<float>
{
public:

	Trigger(float triggerTime)
	:Animator<float>()
	,_trigger(false)
	,_triggerTime(triggerTime)
	{
	}


	virtual ~Trigger()
	{
	}


	virtual float GetValue(float t, float dt = 0.0f)
	{
		return t;
	}


	void SetTriggerTime(float triggerTime)
	{
		this->_triggerTime = triggerTime;
	}


	float& GetTriggerTime()
	{
		return this->_triggerTime;
	}


	virtual void Update(float dt, float maxTime = 0.0f)
	{
		maxTime = this->_triggerTime;

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

				this->_trigger = true;
			}
			break;
		case Loop:
			this->_increasing = true;
			this->_dt = dt;
			this->_t += dt;
			if( this->_t > maxTime )
			{
				this->_t = fmod(this->_t, maxTime);

				this->_trigger = true;
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

				this->_trigger = true;
			}
			if( this->_t < 0.0f )
			{
				this->_t = 0.0f+(0.0f-this->_t);
				this->_increasing = true;

				this->_trigger = true;
			}
			break;
		case Stop:
		default:
			this->_trigger = false;
			this->_increasing = true;
			break;
		}
	}


	bool DoTrigger()
	{
		bool returnState = this->_trigger;
		this->_trigger = false;
		return returnState;
	}

protected:

	bool	_trigger;
	float	_triggerTime;
};


#endif // TRIGGER_H