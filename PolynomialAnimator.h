#ifndef POLYNOMIAL_ANIMATOR_H
#define POLYNOMIAL_ANIMATOR_H


#include <vector>

#include "Animator.h"
#include "Vectors.h"


using namespace std;


template <class T>
class Polynomial : public Animator<T>
{
public:

	Polynomial()
	:Animator<T>()
	,_coeff()
	{
	}


	virtual ~Polynomial()
	{
	}


	virtual T GetValue(float t, float dt = 0.0f)
	{
		T sum = 0;
		for( unsigned int i = 0; i < this->_coeff.max_size(); ++i )
		{
			sum += this->_coeff.at(i) * (T)pow(t, (float)i);
		}
		return sum;
	}


	void SetCoeffNum(unsigned int coeffNum)
	{
		if( coeffNum >= 0 )
		{
			unsigned int oldSize = this->_coeff.max_size();

			this->_coeff.resize(coeffNum);

			// Set new values to zero
			if( this->_coeff.max_size() > oldSize )
			{
				for( unsigned int i = oldSize; i < this->_coeff.size(); ++i )
				{
					this->_coeff.at(i) = 0;
				}
			}
		}
	}


	unsigned int GetCoeffNum()
	{
		return this->_coeff.max_size();
	}


	void SetCoeff(unsigned int index, float coeff)
	{
		if( index >= 0 && index < this->_coeff.max_size() )
		{
			this->_coeff.at(index) = coeff;
		}
	}


	void ClearCoeffs()
	{
		this->_coeff.clear();
	}

protected:

	vector<T>	_coeff;
};
typedef Polynomial<float>		Polynomialf;
typedef Polynomial<Vector2f>	Polynomial2f;
typedef Polynomial<Vector3f>	Polynomial3f;
typedef Polynomial<Vector4f>	Polynomial4f;


#endif // POLYNOMIAL_ANIMATOR_H