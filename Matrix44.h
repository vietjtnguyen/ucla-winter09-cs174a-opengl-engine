#ifndef MATRIX44_H
#define MATRIX44_H


#include <cstring>

#include "Generic.h"
#include "MathWrapper.h"
#include "Vector3.h"
#include "Vector4.h"


// Forward declarations
template <class T> class Vector2;
template <class T> class Vector3;
template <class T> class Vector4;
template <class T> class Matrix33;
template <class T> class Matrix44;


// Custom implementation of three-vector
template <class T>
class Matrix44
{
public:

	// Data
	union
	{
		struct
		{
			T a11; T a12; T a13; T a14;
			T a21; T a22; T a23; T a24;
			T a31; T a32; T a33; T a34;
			T a41; T a42; T a43; T a44;
		};
		struct
		{
			T x1; T y1; T z1; T w1;
			T x2; T y2; T z2; T w2;
			T x3; T y3; T z3; T w3;
			T x4; T y4; T z4; T w4;
		};
		struct
		{
			Vector4<T> r1;
			Vector4<T> r2;
			Vector4<T> r3;
			Vector4<T> r4;
		};
		struct
		{
			Vector4<T> x;
			Vector4<T> y;
			Vector4<T> z;
			Vector4<T> w;
		};
	};


// General functions
	

	// Default constructor
	Matrix44(
		T a11 = 0, T a12 = 0, T a13 = 0, T a14 = 0,
		T a21 = 0, T a22 = 0, T a23 = 0, T a24 = 0,
		T a31 = 0, T a32 = 0, T a33 = 0, T a34 = 0,
		T a41 = 0, T a42 = 0, T a43 = 0, T a44 = 0)
	: x(a11, a12, a13, a14)
	, y(a21, a22, a23, a24)
	, z(a31, a32, a33, a34)
	, w(a41, a42, a43, a44)
	{
	}


	// Vector constructor
	Matrix44(
		Vector4<T> x,
		Vector4<T> y,
		Vector4<T> z,
		Vector4<T> w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
	{
	}


	// Array constructor
	Matrix44(T* vec)
	{
		memcpy(&a11, vec, sizeof(T)*16);
	}


	// Copy constructor
	Matrix44(const Matrix44<T> &other)
	: x(other.x)
	, y(other.y)
	, z(other.z)
	, w(other.w)
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
	~Matrix44()
	{
	}


	// Assignment operator
	inline Matrix44<T>& operator =(const Matrix44<T> &rhs)
	{
		if( this != &rhs )
		{
			Matrix44<T> temp(rhs);
			Core::Swap< Vector4<T> >(this->x, temp.x);
			Core::Swap< Vector4<T> >(this->y, temp.y);
			Core::Swap< Vector4<T> >(this->z, temp.z);
			Core::Swap< Vector4<T> >(this->w, temp.w);
		}
		return *this;
	}


	// Scalar assignment operator
	inline Matrix44<T>& operator =(const T &rhs)
	{
		this->x = rhs;
		this->y = rhs;
		this->z = rhs;
		this->w = rhs;
		return *this;
	}


	// Set values
	inline void Set(
		T a11, T a12, T a13, T a14,
		T a21, T a22, T a23, T a24,
		T a31, T a32, T a33, T a34,
		T a41, T a42, T a43, T a44)
	{
		this->a11 = a11;
		this->a12 = a12;
		this->a13 = a13;
		this->a14 = a14;
		this->a21 = a21;
		this->a22 = a22;
		this->a23 = a23;
		this->a24 = a24;
		this->a31 = a31;
		this->a32 = a32;
		this->a33 = a33;
		this->a34 = a34;
		this->a41 = a41;
		this->a42 = a42;
		this->a43 = a43;
		this->a44 = a44;
	}


	// Get row
	inline Vector4<T> GetRow(int row)
	{
		return *(&this->x+row);
	}


	// Get col
	inline Vector4<T> GetCol(int col)
	{
		return Vector4<T>(*(&a11+col), *(&a21+col), *(&a31+col), *(&a41+col));
	}


	// Negate
	inline const Matrix44<T> operator -()
	{
		return Matrix44<T>(
			-this->x,
			-this->y,
			-this->z,
			-this->w
		);
	}


// Addition operators


	// Vector+Vector
	inline Matrix44<T> operator +(Matrix44<T> &rhs) const
	{
		return Matrix44<T>(
			this->x+rhs.x,
			this->y+rhs.y,
			this->z+rhs.z,
			this->z+rhs.w);
	}


	// Vector+Scalar
	inline Matrix44<T> operator +(T rhs) const
	{
		return Matrix44<T>(
			this->x+rhs,
			this->y+rhs,
			this->z+rhs,
			this->w+rhs);
	}


	// Vector+Vector Assignment
	inline Matrix44<T>& operator +=(Matrix44<T> &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;
		return *this;
	}


	// Vector+Scalar Assignment
	inline Matrix44<T>& operator +=(T rhs)
	{
		this->x += rhs;
		this->y += rhs;
		this->z += rhs;
		this->w += rhs;
		return *this;
	}

	
// Subtraction operators


	// Vector-Vector
	inline Matrix44<T> operator -(Matrix44<T> &rhs) const
	{
		return Matrix44<T>(
			this->x-rhs.x,
			this->y-rhs.y,
			this->z-rhs.z,
			this->w-rhs.w);
	}


	// Vector-Scalar
	inline Matrix44<T> operator -(T rhs) const
	{
		return Matrix44<T>(
			this->x-rhs,
			this->y-rhs,
			this->z-rhs,
			this->w-rhs);
	}


	// Vector-Vector Assignment
	inline Matrix44<T>& operator -=(Matrix44<T> &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;
		return *this;
	}


	// Vector-Scalar Assignment
	inline Matrix44<T>& operator -=(T rhs)
	{
		this->x -= rhs;
		this->y -= rhs;
		this->z -= rhs;
		this->w -= rhs;
		return *this;
	}


// Multiplication operators


	// Vector*Vector
	inline Matrix44<T> operator *(Matrix44<T> &rhs) const
	{
		return Matrix44<T>(
			this->x*rhs.x,
			this->y*rhs.y,
			this->z*rhs.z,
			this->w*rhs.w);
	}


	// Vector*Scalar
	inline Matrix44<T> operator *(T rhs) const
	{
		return Matrix44<T>(
			this->x*rhs,
			this->y*rhs,
			this->z*rhs,
			this->w*rhs);
	}


	// Vector-Vector Assignment
	inline Matrix44<T>& operator *=(Matrix44<T> &rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		this->w *= rhs.w;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Matrix44<T>& operator *=(T rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->w *= rhs;
		return *this;
	}


// Division operators


	// Vector/Vector
	inline Matrix44<T> operator /(Matrix44<T> &rhs) const
	{
		return Matrix44<T>(
			this->x/rhs.x,
			this->y/rhs.y,
			this->z/rhs.z,
			this->w/rhs.w);
	}


	// Vector/Scalar
	inline Matrix44<T> operator /(T rhs) const
	{
		return Matrix44<T>(
			this->x/rhs,
			this->y/rhs,
			this->z/rhs,
			this->w/rhs);
	}


	// Vector/Vector Assignment
	inline Matrix44<T>& operator /=(Matrix44<T> &rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		this->w /= rhs.w;
		return *this;
	}


	// Vector*Scalar Assignment
	inline Matrix44<T>& operator /=(T rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->w /= rhs;
		return *this;
	}


// Comparison operators


	inline bool operator ==(Matrix44<T> &rhs) const
	{
		return (this->x == rhs.x)&&
			   (this->y == rhs.y)&&
			   (this->z == rhs.z)&&
			   (this->w == rhs.w);
	}

 
	inline bool operator !=(Matrix44<T> &rhs) const
	{
		return !(*this == rhs);
	}


// Vector functions


	// Multiply with vector3
	inline Vector4<T> Multiply(Vector3<T> rhs)
	{
		Vector4<T> temp(rhs.x, rhs.y, rhs.z, 1);
		return Vector4<T>(
			this->x.Dot(temp),
			this->y.Dot(temp),
			this->z.Dot(temp),
			this->w.Dot(temp)
		);
	}

	
	inline Vector4<T> operator *(Vector3<T> rhs)
	{
		Vector4<T> temp(rhs.x, rhs.y, rhs.z, 1);
		return Vector4<T>(
			this->x.Dot(temp),
			this->y.Dot(temp),
			this->z.Dot(temp),
			this->w.Dot(temp)
		);
	}


	// Multiply with vector4
	inline Vector4<T> Multiply(Vector4<T> rhs)
	{
		return Vector4<T>(
			this->x.Dot(rhs),
			this->y.Dot(rhs),
			this->z.Dot(rhs),
			this->w.Dot(rhs)
		);
	}

	
	inline Vector4<T> operator *(Vector4<T> rhs)
	{
		return Vector4<T>(
			this->x.Dot(rhs),
			this->y.Dot(rhs),
			this->z.Dot(rhs),
			this->w.Dot(rhs)
		);
	}


	// Multiply with matrix
	inline Matrix44<T> Multiply(Matrix44<T> rhs)
	{
		return Matrix44<T>(
			this->GetRow(0).Dot(rhs.GetCol(0)),
			this->GetRow(0).Dot(rhs.GetCol(1)),
			this->GetRow(0).Dot(rhs.GetCol(2)),
			this->GetRow(0).Dot(rhs.GetCol(3)),
			this->GetRow(1).Dot(rhs.GetCol(0)),
			this->GetRow(1).Dot(rhs.GetCol(1)),
			this->GetRow(1).Dot(rhs.GetCol(2)),
			this->GetRow(1).Dot(rhs.GetCol(3)),
			this->GetRow(2).Dot(rhs.GetCol(0)),
			this->GetRow(2).Dot(rhs.GetCol(1)),
			this->GetRow(2).Dot(rhs.GetCol(2)),
			this->GetRow(2).Dot(rhs.GetCol(3)),
			this->GetRow(3).Dot(rhs.GetCol(0)),
			this->GetRow(3).Dot(rhs.GetCol(1)),
			this->GetRow(3).Dot(rhs.GetCol(2)),
			this->GetRow(3).Dot(rhs.GetCol(3))
		);
	}

	
	inline Matrix44<T> operator *(Matrix44<T> rhs)
	{
		return Matrix44<T>(
			this->GetRow(0).Dot(rhs.GetCol(0)),
			this->GetRow(0).Dot(rhs.GetCol(1)),
			this->GetRow(0).Dot(rhs.GetCol(2)),
			this->GetRow(0).Dot(rhs.GetCol(3)),
			this->GetRow(1).Dot(rhs.GetCol(0)),
			this->GetRow(1).Dot(rhs.GetCol(1)),
			this->GetRow(1).Dot(rhs.GetCol(2)),
			this->GetRow(1).Dot(rhs.GetCol(3)),
			this->GetRow(2).Dot(rhs.GetCol(0)),
			this->GetRow(2).Dot(rhs.GetCol(1)),
			this->GetRow(2).Dot(rhs.GetCol(2)),
			this->GetRow(2).Dot(rhs.GetCol(3)),
			this->GetRow(3).Dot(rhs.GetCol(0)),
			this->GetRow(3).Dot(rhs.GetCol(1)),
			this->GetRow(3).Dot(rhs.GetCol(2)),
			this->GetRow(3).Dot(rhs.GetCol(3))
		);
	}


	// Transpose
	inline void Transpose()
	{
		Core::Swap<T>(this->a12, this->a21);
		Core::Swap<T>(this->a13, this->a31);
		Core::Swap<T>(this->a14, this->a41);
		Core::Swap<T>(this->a23, this->a32);
		Core::Swap<T>(this->a24, this->a42);
		Core::Swap<T>(this->a34, this->a43);
	}


	// Get transpose
	inline Matrix44<T> GetTranspose() const
	{
		return Matrix44<T>(
			a11, a21, a31, a41,
			a12, a22, a32, a42,
			a13, a23, a33, a43,
			a14, a24, a34, a44);
	}


// Special matrices


	// Identity
	inline void SetIdentity()
	{
		this->x.Set(1, 0, 0, 0);
		this->y.Set(0, 1, 0, 0);
		this->z.Set(0, 0, 1, 0);
		this->w.Set(0, 0, 0, 1);
	}


	static Matrix44 Identity()
	{
		Matrix44 temp;
		temp.SetIdentity();
		return temp;
	}


	// Translation
	inline void SetTranslate(T x, T y, T z)
	{
		this->x.Set(1, 0, 0, x);
		this->y.Set(0, 1, 0, y);
		this->z.Set(0, 0, 1, z);
		this->w.Set(0, 0, 0, 1);
	}


	static Matrix44 Translate(T x, T y, T z)
	{
		Matrix44 temp;
		temp.SetTranslate(x, y, z);
		return temp;
	}


	// Rotation
	inline void SetPitch(T angle)
	{
		this->x.Set(1, 0, 0, 0);
		this->y.Set(0, Cos(angle), -Sin(angle), 0);
		this->z.Set(0, Sin(angle), Cos(angle), 0);
		this->w.Set(0, 0, 0, 1);
	}


	inline void SetYaw(T angle)
	{
		this->x.Set(Cos(angle), 0, Sin(angle), 0);
		this->y.Set(0, 1, 0, 0);
		this->z.Set(-Sin(angle), 0, Cos(angle), 0);
		this->w.Set(0, 0, 0, 1);
	}


	inline void SetRoll(T angle)
	{
		this->x.Set(Cos(angle), -Sin(angle), 0, 0);
		this->y.Set(Sin(angle), Cos(angle), 0, 0);
		this->z.Set(0, 0, 1, 0);
		this->w.Set(0, 0, 0, 1);
	}


	static Matrix44 Pitch(T angle)
	{
		Matrix44 temp;
		temp.SetPitch(angle);
		return temp;
	}


	static Matrix44 Yaw(T angle)
	{
		Matrix44 temp;
		temp.SetYaw(angle);
		return temp;
	}


	static Matrix44 Roll(T angle)
	{
		Matrix44 temp;
		temp.SetRoll(angle);
		return temp;
	}


	static Matrix44 EulerRotate(T ax, T ay, T az)
	{
		return Matrix44<T>::Yaw(ay)*Matrix44<T>::Pitch(ax)*Matrix44<T>::Roll(az);
	}


	inline void SetScale(T x, T y, T z)
	{
		this->x.Set(x, 0, 0, 0);
		this->y.Set(0, y, 0, 0);
		this->z.Set(0, 0, z, 0);
		this->w.Set(0, 0, 0, 1);
	}


	static Matrix44 Scale(T x, T y, T z)
	{
		Matrix44 temp;
		temp.SetScale(x, y, z);
		return temp;
	}


	static Matrix44 FullTransform(
		T t_x, T t_y, T t_z,
		T r_x, T r_y, T r_z,
		T s_x, T s_y, T s_z)
	{
		return Matrix44<T>::Translate(t_x, t_y, t_z)*(Matrix44<T>::EulerRotate(r_x, r_y, r_z)*Matrix44<T>::Scale(s_x, s_y, s_z));
	}

};
typedef Matrix44<char>				Matrix44c;
typedef Matrix44<unsigned char>		Matrix44b;
typedef Matrix44<short>				Matrix44s;
typedef Matrix44<unsigned short>	Matrix44us;
typedef Matrix44<int>				Matrix44i;
typedef Matrix44<unsigned int>		Matrix44ui;
typedef Matrix44<float>				Matrix44f;
typedef Matrix44<double>			Matrix44d;


#endif // MATRIX44_H