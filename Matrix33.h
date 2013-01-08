#ifndef MATRIX33_H
#define MATRIX33_H


#include <cstring>

#include "Generic.h"
#include "MathWrapper.h"
#include "Vector3.h"


// Forward declarations
template <class T> class Vector2;
template <class T> class Vector3;
template <class T> class Vector4;
template <class T> class Matrix33;
template <class T> class Matrix44;


// Custom implementation of three-vector
template <class T>
class Matrix33
{
public:

	// Data
	union
	{
		struct
		{
			T a11; T a12; T a13;
			T a21; T a22; T a23;
			T a31; T a32; T a33;
		};
		struct
		{
			T x1; T y1; T z1;
			T x2; T y2; T z2;
			T x3; T y3; T z3;
		};
		struct
		{
			Vector3<T> r1;
			Vector3<T> r2;
			Vector3<T> r3;
		};
		struct
		{
			Vector3<T> x;
			Vector3<T> y;
			Vector3<T> z;
		};
	};


// General functions
	

	// Default constructor
	Matrix33(
		T a11 = 0, T a12 = 0, T a13 = 0,
		T a21 = 0, T a22 = 0, T a23 = 0,
		T a31 = 0, T a32 = 0, T a33 = 0)
	: x(a11, a12, a13)
	, y(a21, a22, a23)
	, z(a31, a32, a33)
	{
	}


	// Vector constructor
	Matrix33(
		Vector3<T> x,
		Vector3<T> y,
		Vector3<T> z)
	: x(x)
	, y(y)
	, z(z)
	{
	}


	// Array constructor
	Matrix33(T* vec)
	{
		memcpy(&a11, vec, sizeof(T)*9);
	}


	// Copy constructor
	Matrix33(const Matrix33<T> &other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
	{
	}


	// Array typecast
	inline operator T*()
	{
		return &(this->a11);
	}


	// Index operator
	inline T& operator [](int i)
	{
		return *(&(this->x)+i);
	}


	// Destructor
	~Matrix33()
	{
	}


	// Assignment operator
	inline Matrix33<T>& operator =(const Matrix33<T> &rhs)
	{
		if( this != &rhs )
		{
			Matrix33<T> temp(rhs);
			Core::Swap< Vector3<T> >(this->x, temp.x);
			Core::Swap< Vector3<T> >(this->y, temp.y);
			Core::Swap< Vector3<T> >(this->z, temp.z);
		}
		return *this;
	}


	// Scalar assignment operator
	inline Matrix33<T>& operator =(const T &rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;
		return *this;
	}


	// Set values
	inline void Set(
		T a11, T a12, T a13,
		T a21, T a22, T a23,
		T a31, T a32, T a33)
	{
		this->a11 = a11;
		this->a12 = a12;
		this->a13 = a13;
		this->a21 = a21;
		this->a22 = a22;
		this->a23 = a23;
		this->a31 = a31;
		this->a32 = a32;
		this->a33 = a33;
	}


	// Get row
	inline Vector3<T> GetRow(int row)
	{
		return *(&this->x+row);
	}


	// Get col
	inline Vector3<T> GetCol(int col)
	{
		return Vector3<T>(*(&a11+col), *(&a21+col), *(&a31+col));
	}


	// Negate
	inline const Matrix33<T> operator -()
	{
		return Matrix33<T>(
			-this->x,
			-this->y,
			-this->z
		);
	}


// Addition operators


	// Vector+Vector
	inline Matrix33<T> operator +(Matrix33<T> &rhs) const
	{
		return Matrix33<T>(
			this->x+rhs.x,
			this->y+rhs.y,
			this->z+rhs.z);
	}


	// Vector+Scalar
	inline Matrix33<T> operator +(T rhs) const
	{
		return Matrix33<T>(
			this->x+rhs,
			this->y+rhs,
			this->z+rhs);
	}


	// Vector+Vector Assignment
	inline Matrix33<T>& operator +=(Matrix33<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}


	// Vector+Scalar Assignment
	inline Matrix33<T>& operator +=(T rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		return *this;
	}

	
// Subtraction operators


	// Vector-Vector
	inline Matrix33<T> operator -(Matrix33<T> &rhs) const
	{
		return Matrix33<T>(
			this->x-rhs.x,
			this->y-rhs.y,
			this->z-rhs.z);
	}


	// Vector-Scalar
	inline Matrix33<T> operator -(T rhs) const
	{
		return Matrix33<T>(
			this->x-rhs,
			this->y-rhs,
			this->z-rhs);
	}


	// Vector-Vector Assignment
	inline Matrix33<T>& operator -=(Matrix33<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}


	// Vector-Scalar Assignment
	inline Matrix33<T>& operator -=(T rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		return *this;
	}


// Multiplication operators


	// Vector*Vector
	inline Matrix33<T> operator *(Matrix33<T> &rhs) const
	{
		return Matrix33<T>(
			this->x*rhs.x,
			this->y*rhs.y,
			this->z*rhs.z);
	}


	// Vector*Scalar
	inline Matrix33<T> operator *(T rhs) const
	{
		return Matrix33<T>(
			this->x*rhs,
			this->y*rhs,
			this->z*rhs);
	}


	// Vector-Vector Assignment
	inline Matrix33<T>& operator *=(Matrix33<T> &rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Matrix33<T>& operator *=(T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		return *this;
	}


// Division operators


	// Vector/Vector
	inline Matrix33<T> operator /(Matrix33<T> &rhs) const
	{
		return Matrix33<T>(
			this->x/rhs.x,
			this->y/rhs.y,
			this->z/rhs.z);
	}


	// Vector/Scalar
	inline Matrix33<T> operator /(T rhs) const
	{
		return Matrix33<T>(
			this->x/rhs,
			this->y/rhs,
			this->z/rhs);
	}


	// Vector/Vector Assignment
	inline Matrix33<T>& operator /=(Matrix33<T> &rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Matrix33<T>& operator /=(T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		return *this;
	}


// Comparison operators


	inline bool operator ==(Matrix33<T> &rhs) const
	{
		return (this->x == rhs.x)&&
			   (this->y == rhs.y)&&
			   (this->z == rhs.z);
	}

 
	inline bool operator !=(Matrix33<T> &rhs) const
	{
		return !(*this == rhs);
	}


// Vector functions


	// Multiply with vector
	inline Vector3<T> Multiply(Vector3<T> rhs)
	{
		return Vector3<T>(
			this->x.Dot(rhs),
			this->y.Dot(rhs),
			this->z.Dot(rhs)
		);
	}

	
	inline Vector3<T> operator *(Vector3<T> rhs)
	{
		return Vector3<T>(
			this->x.Dot(rhs),
			this->y.Dot(rhs),
			this->z.Dot(rhs)
		);
	}


	// Multiply with matrix
	inline Matrix33<T> Multiply(Matrix33<T> rhs)
	{
		return Matrix33<T>(
			this->GetRow(0).Dot(rhs.GetCol(0)),
			this->GetRow(0).Dot(rhs.GetCol(1)),
			this->GetRow(0).Dot(rhs.GetCol(2)),
			this->GetRow(1).Dot(rhs.GetCol(0)),
			this->GetRow(1).Dot(rhs.GetCol(1)),
			this->GetRow(1).Dot(rhs.GetCol(2)),
			this->GetRow(2).Dot(rhs.GetCol(0)),
			this->GetRow(2).Dot(rhs.GetCol(1)),
			this->GetRow(2).Dot(rhs.GetCol(2))
		);
	}

	
	inline Matrix33<T> operator *(Matrix33<T> rhs)
	{
		return Matrix33<T>(
			this->GetRow(0).Dot(rhs.GetCol(0)),
			this->GetRow(0).Dot(rhs.GetCol(1)),
			this->GetRow(0).Dot(rhs.GetCol(2)),
			this->GetRow(1).Dot(rhs.GetCol(0)),
			this->GetRow(1).Dot(rhs.GetCol(1)),
			this->GetRow(1).Dot(rhs.GetCol(2)),
			this->GetRow(2).Dot(rhs.GetCol(0)),
			this->GetRow(2).Dot(rhs.GetCol(1)),
			this->GetRow(2).Dot(rhs.GetCol(2))
		);
	}


	// Transpose
	inline void Transpose()
	{
		Swap<T>(this->a12, this->a21);
		Swap<T>(this->a13, this->a31);
		Swap<T>(this->a23, this->a32);
	}


	// Get transpose
	inline Matrix33<T> GetTranspose() const
	{
		return Matrix33<T>(
			a11, a21, a31,
			a12, a22, a32,
			a13, a23, a33);
	}


// Special matrices


	// Identity
	inline void SetIdentity()
	{
		this->x.Set(1, 0, 0);
		this->y.Set(0, 1, 0);
		this->z.Set(0, 0, 1);
	}


	static Matrix33 Identity()
	{
		Matrix33 temp;
		temp.Identity();
		return temp;
	}


	// Rotation
	inline void SetPitch(T angle)
	{
		this->x.Set(1, 0, 0);
		this->y.Set(0, Cos(angle), -Sin(angle));
		this->z.Set(0, Sin(angle), Cos(angle));
	}


	inline void SetYaw(T angle)
	{
		this->x.Set(Cos(angle), 0, Sin(angle));
		this->y.Set(0, 1, 0);
		this->z.Set(-Sin(angle), 0, Cos(angle));
	}


	inline void SetRoll(T angle)
	{
		this->x.Set(Cos(angle), -Sin(angle), 0);
		this->y.Set(Sin(angle), Cos(angle), 0);
		this->z.Set(0, 0, 1);
	}


	static Matrix33 Pitch(T angle)
	{
		Matrix33 temp;
		temp.SetPitch(angle);
		return temp;
	}


	static Matrix33 Yaw(T angle)
	{
		Matrix33 temp;
		temp.SetYaw(angle);
		return temp;
	}


	static Matrix33 Roll(T angle)
	{
		Matrix33 temp;
		temp.SetRoll(angle);
		return temp;
	}


	static Matrix33 EulerRotate(T ax, T ay, T az)
	{
		return Matrix33<T>::Yaw(ay)*(Matrix33<T>::Pitch(ax)*Matrix33<T>::Roll(az));
	}


	inline void SetScale(T x, T y, T z)
	{
		this->x.Set(x, 0, 0);
		this->y.Set(0, y, 0);
		this->z.Set(0, 0, z);
	}


	static Matrix33 Scale(T x, T y, T z)
	{
		Matrix33 temp;
		temp.SetScale(x, y, z);
		return temp;
	}

};
typedef Matrix33<char>				Matrix33c;
typedef Matrix33<unsigned char>		Matrix33b;
typedef Matrix33<short>				Matrix33s;
typedef Matrix33<unsigned short>	Matrix33us;
typedef Matrix33<int>				Matrix33i;
typedef Matrix33<unsigned int>		Matrix33ui;
typedef Matrix33<float>				Matrix33f;
typedef Matrix33<double>			Matrix33d;


#endif // MATRIX33_H