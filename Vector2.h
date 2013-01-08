#ifndef VECTOR2_H
#define VECTOR2_H


#include "Generic.h"
#include "MathWrapper.h"


using namespace Degrees;


// Forward declarations
template <class T> class Vector2;
template <class T> class Vector3;
template <class T> class Vector4;
template <class T> class Matrix33;
template <class T> class Matrix44;


// Custom implementation of two-vector
template <class T>
class Vector2
{
public:

	// Data
	union { T x; T u; T width; };
	union { T y; T v; T height; };


// General functions
	

	// Default constructor
	Vector2(T x = 0, T y = 0)
	: x(x)
	, y(y)
	{
	}


	// Array constructor
	Vector2(T* vec)
	: x(vec[0])
	, y(vec[1])
	{
	}


	// Copy constructor
	Vector2(const Vector2<T> &other)
	: x(other.x)
	, y(other.y)
	{
	}


	// Array typecast
	inline operator T*()
	{
		return &(this->x);
	}


	// Index operator
	inline T& operator [](int i)
	{
		return *(&(this->x)+i);
	}


	// Destructor
	~Vector2()
	{
	}


	// Vector assignment operator
	inline Vector2<T>& operator =(const Vector2<T> &rhs)
	{
		if( this != &rhs )
		{
			Vector2<T> temp(rhs);
			Core::Swap<T>(this->x, temp.x);
			Core::Swap<T>(this->y, temp.y);
		}
		return *this;
	}


	// Scalar assignment operator
	inline Vector2<T>& operator =(const T &rhs)
	{
		this->x = rhs;
		this->y = rhs;
		return *this;
	}


	// Set values
	inline void Set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}


	// Negate
	inline Vector2<T> operator -()
	{
		return Vector2<T>(
			-this->x,
			-this->y
		);
	}


// Addition operators


	// Vector+Vector
	inline Vector2<T> operator +(Vector2<T> &rhs) const
	{
		return Vector2<T>(
			this->x+rhs.x,
			this->y+rhs.y
		);
	}


	// Vector+Scalar
	inline Vector2<T> operator +(T rhs) const
	{
		return Vector2<T>(
			this->x+rhs,
			this->y+rhs
		);
	}


	// Vector+Vector Assignment
	inline Vector2<T>& operator +=(Vector2<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}


	// Vector+Scalar Assignment
	inline Vector2<T>& operator +=(T rhs)
	{
		this->x += rhs;
		this->y += rhs;
		return *this;
	}

	
// Subtraction operators


	// Vector-Vector
	inline Vector2<T> operator -(Vector2<T> &rhs) const
	{
		return Vector2<T>(
			this->x-rhs.x,
			this->y-rhs.y
		);
	}


	// Vector-Scalar
	inline Vector2<T> operator -(T rhs) const
	{
		return Vector2<T>(
			this->x-rhs,
			this->y-rhs
		);
	}


	// Vector-Vector Assignment
	inline Vector2<T>& operator -=(Vector2<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}


	// Vector-Scalar Assignment
	inline Vector2<T>& operator -=(T rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		return *this;
	}


// Multiplication operators


	// Vector*Vector
	inline Vector2<T> operator *(Vector2<T> &rhs) const
	{
		return Vector2<T>(
			this->x*rhs.x,
			this->y*rhs.y
		);
	}


	// Vector*Scalar
	inline Vector2<T> operator *(T rhs) const
	{
		return Vector2<T>(
			this->x*rhs,
			this->y*rhs
		);
	}


	// Vector-Vector Assignment
	inline Vector2<T>& operator *=(Vector2<T> &rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector2<T>& operator *=(T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}


// Division operators


	// Vector/Vector
	inline Vector2<T> operator /(Vector2<T> &rhs) const
	{
		return Vector2<T>(
			this->x/rhs.x,
			this->y/rhs.y
		);
	}


	// Vector/Scalar
	inline Vector2<T> operator /(T rhs) const
	{
		return Vector2<T>(
			this->x/rhs,
			this->y/rhs
		);
	}


	// Vector/Vector Assignment
	inline Vector2<T>& operator /=(Vector2<T> &rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector2<T>& operator /=(T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}


// Comparison operators


	inline bool operator ==(Vector2<T> &rhs) const
	{
		return (this->x == rhs.x)&&
			   (this->y == rhs.y);
	}


	inline bool operator !=(Vector2<T> &rhs) const
	{
		return !(*this == rhs);
	}


// Vector functions


	// Dot product
	inline T Dot(Vector2<T> &rhs) const
	{
		return (this->x*rhs.x)+
			   (this->y*rhs.y);
	}


	// Projection
	inline Vector2<T> ProjectOnto(Vector2<T> &rhs) const
	{
		return rhs*(*this).Dot(rhs)/rhs.Dot(rhs);
	}


	// Vector length
	inline T Length() const
	{
		return sqrt(this->x*this->x+
					this->y*this->y);
	}


	// Normalize vector
	inline void Normalize()
	{
		T length = Length();
		this->x /= length;
		this->y /= length;
	}


	// Unit vector
	inline Vector2<T> Unit() const
	{
		Vector2<T> temp(*this);
		temp.Normalize();
		return temp;
	}


// Special vectors


	// Zero vector
	static inline Vector2<T> Zero()
	{
		return Vector2<T>(0, 0);
	}


	// Direction vector
	static inline Vector2<T> Direction(float az)
	{
		return Vector2<T>(Cos(az), Sin(az));
	}

};
typedef Vector2<char>			Vector2c;
typedef Vector2<unsigned char>	Vector2b;
typedef Vector2<short>			Vector2s;
typedef Vector2<unsigned short>	Vector2us;
typedef Vector2<int>			Vector2i;
typedef Vector2<unsigned int>	Vector2ui;
typedef Vector2<float>			Vector2f;
typedef Vector2<double>			Vector2d;


inline Vector2f Sin(Vector2f v)
{
	return Vector2f(Sin(v.x), Sin(v.y));
}


inline Vector2d Sin(Vector2d v)
{
	return Vector2d(Sin(v.x), Sin(v.y));
}


inline Vector2f Cos(Vector2f v)
{
	return Vector2f(Cos(v.x), Cos(v.y));
}


inline Vector2d Cos(Vector2d v)
{
	return Vector2d(Cos(v.x), Cos(v.y));
}


inline Vector2f Tan(Vector2f v)
{
	return Vector2f(Tan(v.x), Tan(v.y));
}


inline Vector2d Tan(Vector2d v)
{
	return Vector2d(Tan(v.x), Tan(v.y));
}


#endif // VECTOR2_H