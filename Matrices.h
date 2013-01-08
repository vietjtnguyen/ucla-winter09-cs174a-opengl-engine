#ifndef MATRICES_H
#define MATRICES_H


#include "Matrix33.h"
#include "Matrix44.h"


template <class T>
inline T Determinate22(T a, T b, T c, T d)
{
	return a*d-b*c;
}


template <class T>
inline T Determinate33(Matrix33<T> in)
{
	return in.a11*Determinate22<T>(in.a22, in.a23, in.a32, in.a33)
		  -in.a21*Determinate22<T>(in.a12, in.a13, in.a32, in.a33)
		  +in.a31*Determinate22<T>(in.a12, in.a13, in.a22, in.a23);
}


template <class T>
inline T Determinate44(Matrix44<T> in)
{
	return in.a11*Determinate33<T>(Matrix33<T>(in.a22, in.a23, in.a24, in.a32, in.a33, in.a34, in.a42, in.a43, in.a44))
		  -in.a21*Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a32, in.a33, in.a34, in.a42, in.a43, in.a44))
		  +in.a31*Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a22, in.a23, in.a24, in.a42, in.a43, in.a44))
		  -in.a41*Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a22, in.a23, in.a24, in.a32, in.a33, in.a34));
}


template <class T>
inline Matrix44<T> Adjoint44(Matrix44<T> in)
{
	Matrix44<T> out;
	
	out.a11 =  Determinate33<T>(Matrix33<T>(in.a22, in.a23, in.a24, in.a32, in.a33, in.a34, in.a42, in.a43, in.a44));
	out.a12 = -Determinate33<T>(Matrix33<T>(in.a21, in.a23, in.a24, in.a31, in.a33, in.a34, in.a41, in.a43, in.a44));
	out.a13 =  Determinate33<T>(Matrix33<T>(in.a21, in.a22, in.a24, in.a31, in.a32, in.a34, in.a41, in.a42, in.a44));
	out.a14 = -Determinate33<T>(Matrix33<T>(in.a21, in.a22, in.a23, in.a31, in.a32, in.a33, in.a41, in.a42, in.a43));
	
	out.a21 = -Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a32, in.a33, in.a34, in.a42, in.a43, in.a44));
	out.a22 =  Determinate33<T>(Matrix33<T>(in.a11, in.a13, in.a14, in.a31, in.a33, in.a34, in.a41, in.a43, in.a44));
	out.a23 = -Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a14, in.a31, in.a32, in.a34, in.a41, in.a42, in.a44));
	out.a24 =  Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a13, in.a31, in.a32, in.a33, in.a41, in.a42, in.a43));
	
	out.a31 =  Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a22, in.a23, in.a24, in.a42, in.a43, in.a44));
	out.a32 = -Determinate33<T>(Matrix33<T>(in.a11, in.a13, in.a14, in.a21, in.a23, in.a24, in.a41, in.a43, in.a44));
	out.a33 =  Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a14, in.a21, in.a22, in.a24, in.a41, in.a42, in.a44));
	out.a34 = -Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a13, in.a21, in.a22, in.a23, in.a41, in.a42, in.a43));
	
	out.a41 = -Determinate33<T>(Matrix33<T>(in.a12, in.a13, in.a14, in.a22, in.a23, in.a24, in.a32, in.a33, in.a34));
	out.a42 =  Determinate33<T>(Matrix33<T>(in.a11, in.a13, in.a14, in.a21, in.a23, in.a24, in.a31, in.a33, in.a34));
	out.a43 = -Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a14, in.a21, in.a22, in.a24, in.a31, in.a32, in.a34));
	out.a44 =  Determinate33<T>(Matrix33<T>(in.a11, in.a12, in.a13, in.a21, in.a22, in.a23, in.a31, in.a32, in.a33));

	out.Transpose();

	return out;
}


template <class T>
inline Matrix44<T> Inverted44(Matrix44<T> in)
{
	Matrix44<T> out = Adjoint44(in);

	T det = Determinate44<T>(in);

	if( abs(det) < 1e-8 )
	{
		out = 0;
		det = 1;
	}

	out /= det;

	return out;
}


#endif // MATRICES_H