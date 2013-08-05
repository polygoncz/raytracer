#pragma once

#include <cmath>

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
class Shape;
class Film;
class Camera;
class Statistics;

inline float Clamp(float val, float from, float to)
{
	if (val < from) return from;
	if (val > to) return to;

	return val;
}

inline float Min(float t1, float t2)
{
	return t1 < t2 ? t1 : t2;
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
