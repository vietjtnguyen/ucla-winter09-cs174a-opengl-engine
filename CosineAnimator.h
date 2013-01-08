#ifndef COSINE_ANIMATOR_H
#define COSINE_ANIMATOR_H


#include "Animator.h"
#include "MathWrapper.h"
#include "Vectors.h"


template <class T>
class Cosine : public Animator<T>
{
public:

	Cosine(float freq, float amp, float offset = 0.0f)
	:Animator<T>()
	,_freq(freq)
	,_amp(amp)
	,_offset(offset)
	{
	}


	virtual ~Cosine()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		return this->_amp*cos(this->_freq*t)+this->_offset;
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
typedef Cosine<float>		Cosinef;
typedef Cosine<Vector2f>	Cosine2f;
typedef Cosine<Vector3f>	Cosine3f;
typedef Cosine<Vector4f>	Cosine4f;


#endif // COSINE_ANIMATOR_H