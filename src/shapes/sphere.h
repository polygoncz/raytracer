#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/primitive.h"

class Sphere: public GeometricPrimitive
{
public:
	Sphere(const Point& _center, float _radius, const Reference<Material>& _material);
	Sphere(const Sphere& sphere);
	virtual ~Sphere(void);

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;

private:
	Point center;
	float radius;
};
