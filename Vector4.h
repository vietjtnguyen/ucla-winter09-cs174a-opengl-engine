#ifndef VECTOR4_H
#define VECTOR4_H


#include "Generic.h"
#include "MathWrapper.h"


using namespace Degrees;


// Forward declarations
template <class T> class Vector2;
template <class T> class Vector3;
template <class T> class Vector4;
template <class T> class Matrix33;
template <class T> class Matrix44;


// Custom implementation of three-vector
template <class T>
class Vector4
{
public:

	// Data
	union { T x; T r; T u; T width; };
	union { T y; T g; T v; T height; };
	union { T z; T b; T w; T depth; };
	union { T a; };


// General functions
	

	// Default constructor
	Vector4(T x = 0, T y = 0, T z = 0, T a = 0)
	: x(x)
	, y(y)
	, z(z)
	, a(a)
	{
	}


	// Array constructor
	Vector4(T* vec)
	: x(vec[0])
	, y(vec[1])
	, z(vec[2])
	, a(vec[3])
	{
	}


	// Vector3 constructor
	Vector4(Vector3<T> vec, T a = 0)
	: x(vec.x)
	, y(vec.y)
	, z(vec.z)
	, a(a)
	{
	}


	// Copy constructor
	Vector4(const Vector4<T> &other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
	, a(other.a)
	{
	}


	// Array typecast
	inline operator T*()
	{
		return &(this->x);
	}


	// Vector3 typecase
	inline operator Vector3<T>*()
	{
		return this;
	}


	// Vector2 typecase
	inline operator Vector2<T>*()
	{
		return this;
	}


	// Index operator
	inline T& operator [](int i)
	{
		return *(&(this->x)+i);
	}


	// Destructor
	~Vector4()
	{
	}


	// Vector assignment operator
	inline Vector4<T>& operator =(const Vector4<T> &rhs)
	{
		if( this != &rhs )
		{
			Vector4<T> temp(rhs);
			Core::Swap<T>(this->x, temp.x);
			Core::Swap<T>(this->y, temp.y);
			Core::Swap<T>(this->z, temp.z);
			Core::Swap<T>(this->a, temp.a);
		}
		return *this;
	}


	// Scalar assignment operator
	inline Vector4<T>& operator =(const T &rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;
		this->a = rhs;
		return *this;
	}


	// Set values
	inline void Set(T x, T y, T z, T a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}


	// Negate
	inline Vector4<T> operator -()
	{
		return Vector4<T>(
			-this->x,
			-this->y,
			-this->z,
			-this->a
		);
	}


// Addition operators


	// Vector+Vector
	inline Vector4<T> operator +(Vector4<T> &rhs) const
	{
		return Vector4<T>(
			this->x+rhs.x,
			this->y+rhs.y,
			this->z+rhs.z,
			this->a+rhs.a);
	}


	// Vector+Scalar
	inline Vector4<T> operator +(T rhs) const
	{
		return Vector4<T>(
			this->x+rhs,
			this->y+rhs,
			this->z+rhs,
			this->a+rhs);
	}


	// Vector+Vector Assignment
	inline Vector4<T>& operator +=(Vector4<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->a += rhs.z;
		return *this;
	}


	// Vector+Scalar Assignment
	inline Vector4<T>& operator +=(T rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		this->a += rhs;
		return *this;
	}

	
// Subtraction operators


	// Vector-Vector
	inline Vector4<T> operator -(Vector4<T> &rhs) const
	{
		return Vector4<T>(
			this->x-rhs.x,
			this->y-rhs.y,
			this->z-rhs.z,
			this->a-rhs.a);
	}


	// Vector-Scalar
	inline Vector4<T> operator -(T rhs) const
	{
		return Vector4<T>(
			this->x-rhs,
			this->y-rhs,
			this->z-rhs,
			this->a-rhs);
	}


	// Vector-Vector Assignment
	inline Vector4<T>& operator -=(Vector4<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->a -= rhs.a;
		return *this;
	}


	// Vector-Scalar Assignment
	inline Vector4<T>& operator -=(T rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		this->a -= rhs;
		return *this;
	}


// Multiplication operators


	// Vector*Vector
	inline Vector4<T> operator *(Vector4<T> &rhs) const
	{
		return Vector4<T>(
			this->x*rhs.x,
			this->y*rhs.y,
			this->z*rhs.z,
			this->a*rhs.a);
	}


	// Vector*Scalar
	inline Vector4<T> operator *(T rhs) const
	{
		return Vector4<T>(
			this->x*rhs,
			this->y*rhs,
			this->z*rhs,
			this->a*rhs);
	}


	// Vector-Vector Assignment
	inline Vector4<T>& operator *=(Vector4<T> &rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		this->a *= rhs.a;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector4<T>& operator *=(T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->a *= rhs;
		return *this;
	}


// Division operators


	// Vector/Vector
	inline Vector4<T> operator /(Vector4<T> &rhs) const
	{
		return Vector4<T>(
			this->x/rhs.x,
			this->y/rhs.y,
			this->z/rhs.z,
			this->a/rhs.a);
	}


	// Vector/Scalar
	inline Vector4<T> operator /(T rhs) const
	{
		return Vector4<T>(
			this->x/rhs,
			this->y/rhs,
			this->z/rhs,
			this->a/rhs);
	}


	// Vector/Vector Assignment
	inline Vector4<T>& operator /=(Vector4<T> &rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		this->a /= rhs.a;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector4<T>& operator /=(T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->a /= rhs;
		return *this;
	}


// Comparison operators


	inline bool operator ==(Vector4<T> &rhs) const
	{
		return (this->x == rhs.x)&&
			   (this->y == rhs.y)&&
			   (this->z == rhs.z)&&
			   (this->a == rhs.a);
	}


	inline bool operator !=(Vector4<T> &rhs) const
	{
		return !(*this == rhs);
	}


// Vector functions


	// Dot product
	inline T Dot(Vector4<T> &rhs) const
	{
		return (this->x*rhs.x)+
			   (this->y*rhs.y)+
			   (this->z*rhs.z)+
			   (this->a*rhs.a);
	}


	// Projection
	inline Vector4<T> ProjectOnto(Vector4<T> &rhs) const
	{
		return rhs*(*this).Dot(rhs)/rhs.Dot(rhs);
	}


	// Vector length
	inline T Length() const
	{
		return sqrt(this->x*this->x+
					this->y*this->y+
					this->z*this->z+
					this->a*this->a);
	}


	// Normalize vector
	inline void Normalize()
	{
		T length = Length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
		this->a /= length;
	}


	// Unit vector
	inline Vector4<T> Unit() const
	{
		Vector4<T> temp(*this);
		temp.Normalize();
		return temp;
	}


// Special vectors


	// Zero vector
	static inline Vector4<T> Zero()
	{
		return Vector4<T>(0, 0, 0, 0);
	}

};
typedef Vector4<char>			Vector4c;
typedef Vector4<unsigned char>	Vector4b;
typedef Vector4<short>			Vector4s;
typedef Vector4<unsigned short>	Vector4us;
typedef Vector4<int>			Vector4i;
typedef Vector4<unsigned int>	Vector4ui;
typedef Vector4<float>			Vector4f;
typedef Vector4<double>			Vector4d;


inline Vector4f Sin(Vector4f v)
{
	return Vector4f(Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.a));
}


inline Vector4d Sin(Vector4d v)
{
	return Vector4d(Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.a));
}


inline Vector4f Cos(Vector4f v)
{
	return Vector4f(Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.a));
}


inline Vector4d Cos(Vector4d v)
{
	return Vector4d(Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.a));
}


inline Vector4f Tan(Vector4f v)
{
	return Vector4f(Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.a));
}


inline Vector4d Tan(Vector4d v)
{
	return Vector4d(Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.a));
}


#endif // VECTOR4_H