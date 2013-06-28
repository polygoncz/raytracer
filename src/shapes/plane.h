#pragma once

#include "core/core.h"
#include "core/primitive.h"
#include "core/geometry.h"

class Plane : public Primitive
{
public:
	Plane( void );
	Plane(const Point& p, const Normal& n, Material* _material);
	Plane (const Plane& pl);
	virtual ~Plane();

	virtual bool Hit(const Ray& ray, float& tmin, Intersection& sr) const;
private:
	Point p;
	Normal n;
};