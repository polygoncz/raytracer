#include "plane.h"

#include "core/constants.h"
#include "core/core.h"
#include "core/geometry.h"

Plane::Plane(void) : Primitive() {}

Plane::Plane(const Point& p, const Normal& n, Material* _material)
	: Primitive(_material), p(p), n(n)
{}

Plane::Plane(const Plane& pl)
	: Primitive(pl.material), p(pl.p), n(pl.n)
{}

Plane::~Plane(void)
{}

bool Plane::Hit(const Ray& ray, float& tmin, Intersection& sr) const
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