#ifndef VECTOR3_H
#define VECTOR3_H


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
class Vector3
{
public:

	// Data
	union { T x; T r; T u; T width; };
	union { T y; T g; T v; T height; };
	union { T z; T b; T w; T depth; };


// General functions
	

	// Default constructor
	Vector3(T x = 0, T y = 0, T z = 0)
	: x(x)
	, y(y)
	, z(z)
	{
	}


	// Array constructor
	Vector3(T* vec)
	: x(vec[0])
	, y(vec[1])
	, z(vec[2])
	{
	}


	// Copy constructor
	Vector3(const Vector3<T> &other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
	{
	}


	// Array typecast
	inline operator T*()
	{
		return &(this->x);
	}


	// Vector2 typecast
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
	~Vector3()
	{
	}


	// Vector assignment operator
	inline Vector3<T>& operator =(const Vector3<T> &rhs)
	{
		if( this != &rhs )
		{
			Vector3<T> temp(rhs);
			Core::Swap<T>(this->x, temp.x);
			Core::Swap<T>(this->y, temp.y);
			Core::Swap<T>(this->z, temp.z);
		}
		return *this;
	}


	// Scalar assignment operator
	inline Vector3<T>& operator =(const T &rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;
		return *this;
	}


	// Set values
	inline void Set(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	// Negate
	inline Vector3<T> operator -()
	{
		return Vector3<T>(
			-this->x,
			-this->y,
			-this->z
		);
	}


// Addition operators


	// Vector+Vector
	inline Vector3<T> operator +(Vector3<T> &rhs) const
	{
		return Vector3<T>(
			this->x+rhs.x,
			this->y+rhs.y,
			this->z+rhs.z);
	}


	// Vector+Scalar
	inline Vector3<T> operator +(T rhs) const
	{
		return Vector3<T>(
			this->x+rhs,
			this->y+rhs,
			this->z+rhs);
	}


	// Vector+Vector Assignment
	inline Vector3<T>& operator +=(Vector3<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}


	// Vector+Scalar Assignment
	inline Vector3<T>& operator +=(T rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		return *this;
	}

	
// Subtraction operators


	// Vector-Vector
	inline Vector3<T> operator -(Vector3<T> &rhs) const
	{
		return Vector3<T>(
			this->x-rhs.x,
			this->y-rhs.y,
			this->z-rhs.z);
	}


	// Vector-Scalar
	inline Vector3<T> operator -(T rhs) const
	{
		return Vector3<T>(
			this->x-rhs,
			this->y-rhs,
			this->z-rhs);
	}


	// Vector-Vector Assignment
	inline Vector3<T>& operator -=(Vector3<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}


	// Vector-Scalar Assignment
	inline Vector3<T>& operator -=(T rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		return *this;
	}


// Multiplication operators


	// Vector*Vector
	inline Vector3<T> operator *(Vector3<T> &rhs) const
	{
		return Vector3<T>(
			this->x*rhs.x,
			this->y*rhs.y,
			this->z*rhs.z);
	}


	// Vector*Scalar
	inline Vector3<T> operator *(T rhs) const
	{
		return Vector3<T>(
			this->x*rhs,
			this->y*rhs,
			this->z*rhs);
	}


	// Vector-Vector Assignment
	inline Vector3<T>& operator *=(Vector3<T> &rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector3<T>& operator *=(T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		return *this;
	}


// Division operators


	// Vector/Vector
	inline Vector3<T> operator /(Vector3<T> &rhs) const
	{
		return Vector3<T>(
			this->x/rhs.x,
			this->y/rhs.y,
			this->z/rhs.z);
	}


	// Vector/Scalar
	inline Vector3<T> operator /(T rhs) const
	{
		return Vector3<T>(
			this->x/rhs,
			this->y/rhs,
			this->z/rhs);
	}


	// Vector/Vector Assignment
	inline Vector3<T>& operator /=(Vector3<T> &rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Vector3<T>& operator /=(T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		return *this;
	}


// Comparison operators


	inline bool operator ==(Vector3<T> &rhs) const
	{
		return (this->x == rhs.x)&&
			   (this->y == rhs.y)&&
			   (this->z == rhs.z);
	}


	inline bool operator !=(Vector3<T> &rhs) const
	{
		return !(*this == rhs);
	}


// Vector functions


	// Dot product
	inline T Dot(Vector3<T> &rhs) const
	{
		return (this->x*rhs.x)+
			   (this->y*rhs.y)+
			   (this->z*rhs.z);
	}


	// Cross product
	inline Vector3<T> Cross(Vector3<T> &rhs) const
	{
		return Vector3<T>(this->y*rhs.z-rhs.y*this->z,
						  this->z*rhs.x-rhs.z*this->x,
						  this->x*rhs.y-rhs.x*this->y);
	}


	// Projection
	inline Vector3<T> ProjectOnto(Vector3<T> &rhs) const
	{
		return rhs*(*this).Dot(rhs)/rhs.Dot(rhs);
	}


	// Vector length
	inline T Length() const
	{
		return sqrt(this->x*this->x+
					this->y*this->y+
					this->z*this->z);
	}


	// Normalize vector
	inline void Normalize()
	{
		T length = Length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}


	// Unit vector
	inline Vector3<T> Unit() const
	{
		Vector3<T> temp(*this);
		temp.Normalize();
		return temp;
	}


// Special vectors


	// Zero vector
	static inline Vector3<T> Zero()
	{
		return Vector3<T>(0, 0, 0);
	}


	// Direction vector
	static inline Vector3<T> Direction(float ax, float ay)
	{
		return Vector3<T>(-Sin(ay)*Cos(ax), Sin(ax), Cos(ay)*Cos(ax));
	}

};
typedef Vector3<char>			Vector3c;
typedef Vector3<unsigned char>	Vector3b;
typedef Vector3<short>			Vector3s;
typedef Vector3<unsigned short>	Vector3us;
typedef Vector3<int>			Vector3i;
typedef Vector3<unsigned int>	Vector3ui;
typedef Vector3<float>			Vector3f;
typedef Vector3<double>			Vector3d;


inline Vector3f Sin(Vector3f v)
{
	return Vector3f(Sin(v.x), Sin(v.y), Sin(v.z));
}


inline Vector3d Sin(Vector3d v)
{
	return Vector3d(Sin(v.x), Sin(v.y), Sin(v.z));
}


inline Vector3f Cos(Vector3f v)
{
	return Vector3f(Cos(v.x), Cos(v.y), Cos(v.z));
}


inline Vector3d Cos(Vector3d v)
{
	return Vector3d(Cos(v.x), Cos(v.y), Cos(v.z));
}


inline Vector3f Tan(Vector3f v)
{
	return Vector3f(Tan(v.x), Tan(v.y), Tan(v.z));
}


inline Vector3d Tan(Vector3d v)
{
	return Vector3d(Tan(v.x), Tan(v.y), Tan(v.z));
}


#endif // VECTOR3_H