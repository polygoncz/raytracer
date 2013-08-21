#include "plane.h"

#include "core/constants.h"
#include "core/core.h"
#include "core/geometry.h"
Plane::Plane(const Point& p, const Normal& n, Reference<Material> _material)
		: Shape(_material), p(p), n(n)
{
}

Plane::Plane(const Plane& pl)
		: Shape(pl.material), p(pl.p), n(pl.n)
{
}

Plane::~Plane(void)
{
}

bool Plane::IntersectP(const Ray& ray)
{
	float t = Dot(p - ray.o, n) / Dot(ray.d, n);

	if (t > EPSILON) return true;

	return false;
}

bool Plane::Intersect(const Ray& ray, float& tmin, Intersection& sr)
{
	float t = Dot(p - ray.o, n) / Dot(ray.d, n);

	if (t > EPSILON && t < sr.t)
	{
		tmin = t;
		sr.normal = n;
		return true;
	}

	return false;
}

BBox Plane::Bounds() const
{
	BBox b;
	return b;
}
