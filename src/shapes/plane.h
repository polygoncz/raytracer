#pragma once

#include "core/core.h"
#include "core/primitive.h"
#include "core/geometry.h"

class Plane: public GeometricPrimitive
{
public:
	Plane(const Point& p, const Normal& n, Reference<Material> _material);
	Plane(const Plane& pl);
	virtual ~Plane();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;
private:
	Point p;
	Normal n;
};
