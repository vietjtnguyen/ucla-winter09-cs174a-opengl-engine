#ifndef SINE_ANIMATOR_H
#define SINE_ANIMATOR_H


#include "Animator.h"
#include "MathWrapper.h"
#include "Vectors.h"


template <class T>
class Sine : public Animator<T>
{
public:

	Sine(float freq, float amp, float offset = 0.0f)
	:Animator<T>()
	,_freq(freq)
	,_amp(amp)
	,_offset(offset)
	{
	}


	virtual ~Sine()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return this->_amp*sin(this->_freq*t)+this->_offset;
	}


	void SetFrequency(float freq)
	{
		this->_freq = freq;
	}


	float& GetFrequency()
	{
		return this->_freq;
	}


	void SetAmplitude(float amp)
	{
		this->_amp = amp;
	}


	float& GetAmplitude()
	{
		return this->_amp;
	}


	void SetOffset(float offset)
	{
		this->_offset = offset;
	}


	float& GetOffset()
	{
		return this->_offset;
	}

protected:

	float	_freq;
	float	_amp;
	float	_offset;
};
typedef Sine<float>		Sinef;
typedef Sine<Vector2f>	Sine2f;
typedef Sine<Vector3f>	Sine3f;
typedef Sine<Vector4f>	Sine4f;


#endif // SINE_ANIMATOR_H