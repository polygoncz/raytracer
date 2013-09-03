#pragma once

#include <cmath>
//#include <mmintrin.h>
//#include <xmmintrin.h>

class BRDF;
class Light;
class Material;
class Point;
class Vector;
class Ray;
class Normal;
class Scene;
class Intersection;
class RGBColor;
class Integrator;
class Primitive;
class Film;
class Camera;
class Statistics;

inline float Clamp(float val, float from, float to)
{
	if (val < from) return from;
	if (val > to) return to;

	return val;
}

inline float Clamp(int val, int from, int to)
{
	if (val < from) return from;
	if (val > to) return to;

	return val;
}

template <class T>
inline T Clamp(T val, T from, T to)
{
	if (val < from) return from;
	if (val > to) return to;

	return val;
}

inline float Min(float t1, float t2)
{
	return t1 < t2 ? t1 : t2;
}

inline float Max(float t1, float t2)
{
	return t1 > t2 ? t1 : t2;
}

inline void Swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

inline float Lerp(float t, float a, float b)
{
	return (1.f - t) * a + t * b;
}

inline bool Quadratic(float a, float b, float c, float* t0, float* t1)
{
	float disc = b * b - 4 * a * c;

	if (disc < 0.f)
	{
		return false;
	}

	float e = sqrt(disc);
	float lowerPart = 2.0f * a;

	*t0 = (-b + e) / lowerPart;
	*t1 = (-b - e) / lowerPart;

	return true;
}

inline int Round2Int(float f)
{
	return (int) (f + 0.5f);
}
