#ifndef MATHWRAPPER_H
#define MATHWRAPPER_H


#include <math.h>
#include <stdlib.h>


// Constants
#define PI			3.1415926535897932384626433832795
#define TWOPI		6.283185307179586476925286766559
#define HALFPI		1.5707963267948966192313216916395
#define QUARTERPI	0.78539816339744830961566084581975
#define THIRDPI		1.0471975511965977461542144610932
#define DEGTORAD	0.017453292519943295769236907684886
#define RADTODEG	57.295779513082320876798154814105
#define BIGNUMBER	1e8
#define SMALLNUMBER	1e-4


// Converts degrees to radians
#pragma warning(disable:4244)
inline float DegToRad(float degrees)
{
	return degrees*DEGTORAD;
}
inline double DegToRad(double degrees)
{
	return degrees*DEGTORAD;
}


// Converts radians to degrees
inline float RadToDeg(float radians)
{
	return radians*RADTODEG;
}
inline double RadToDeg(double radians)
{
	return radians*RADTODEG;
}


namespace Degrees
{
	// Sin
	inline float Sin(float degrees)
	{
		return sin(DegToRad(degrees));
	}
	inline double Sin(double degrees)
	{
		return sin(DegToRad(degrees));
	}

	// Cos
	inline float Cos(float degrees)
	{
		return cos(DegToRad(degrees));
	}
	inline double Cos(double degrees)
	{
		return cos(DegToRad(degrees));
	}

	// Tan
	inline float Tan(float degrees)
	{
		return tan(DegToRad(degrees));
	}
	inline double Tan(double degrees)
	{
		return tan(DegToRad(degrees));
	}
}


namespace Radians
{
	// Sin
	inline float Sin(float radians)
	{
		return sin(radians);
	}
	inline double Sin(double radians)
	{
		return sin(radians);
	}

	// Cos
	inline float Cos(float radians)
	{
		return cos(radians);
	}
	inline double Cos(double radians)
	{
		return cos(radians);
	}

	// Tan
	inline float Tan(float radians)
	{
		return tan(radians);
	}
	inline double Tan(double radians)
	{
		return tan(radians);
	}
}


// Generate a random float
inline float Rnd()
{
	return (float)rand()/(float)RAND_MAX;
}


// Generate a random float in a range
inline float Rnd(float low, float high)
{
	return low+Rnd()*(high-low);
}


#endif MATHWRAPPER_H