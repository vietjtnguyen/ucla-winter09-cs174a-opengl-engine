#ifndef VECTORS_H
#define VECTORS_H


#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


// Calculate a reflected vector
inline Vector3f Reflect(Vector3f l, Vector3f n)
{
	return l+(l.ProjectOnto(n)-l)*2.0f;
}


#endif // VECTORS_H