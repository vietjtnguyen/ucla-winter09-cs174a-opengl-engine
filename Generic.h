#ifndef GENERIC_H
#define GENERIC_H


namespace Core
{


// Swap two objects
template <class T>
inline void Swap(T &a, T &b)
{
	T temp(b);
	b = a;
	a = temp;
}


// Return the smaller of two values
template <class T>
inline T Min(T a, T b)
{
	return ( a < b ) ? a : b;
}


// Return the larger of two values
template <class T>
inline T Max(T a, T b)
{
	return ( a > b ) ? a : b;
}


// Floor limit a value
template <class T>
inline T LoLimit(T a, T b)
{
	return ( a < b ) ? b : a;
}


// Ceiling limit a value
template <class T>
inline T HiLimit(T a, T b)
{
	return ( a > b ) ? b : a;
}


// Limits a value between two numbers
// Note: Assumes that b < c
template <class T>
inline T Limit(T a, T b, T c)
{
	a = ( a < b ) ? b : a;
	return ( a > c ) ? c : a;
}


// Normalizes a value between two values
template <class T>
inline T Normalize(T a, T b, T t)
{
	return (t-a)/(b-a);
}


// Normalizes a value between two values
template <class T>
inline T Lerp(T x1, T x2, T x, T y1, T y2)
{
	return Normalize<T>(x1, x2, x)*(y2-y1)+y1;
}


} // namespace Core


#endif // GENERIC_H