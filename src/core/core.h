#pragma once

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

inline float Clamp(float val, float from, float to)
{
	if (val < from)
		return from;
	if (val > to)
		return to;

	return val;
}