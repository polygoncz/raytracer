#include "sphere.h"

#include "core/constants.h"
#include "core/core.h"
#include "core/geometry.h"

#include <cmath>
Sphere::Sphere(const Point& _center, float _radius, const Reference<Material>& _material)
		: GeometricPrimitive(_material), center(_center), radius(_radius)
{
}

Sphere::Sphere(const Sphere& sphere)
		: GeometricPrimitive(sphere.material), center(sphere.center), radius(sphere.radius)
{
}

Sphere::~Sphere(void)
{
}

bool Sphere::IntersectP(const Ray& ray)
{
	Vector temp = ray.o - center;
	float a = Dot(ray.d, ray.d);
	float b = 2 * Dot(temp, ray.d);
	float c = Dot(temp, temp) - radius * radius;

	float t1;
	float t2;

	if (!Quadratic(a, b, c, &t1, &t2)) return false;

	float t = Min(t1, t2);

	if (t > EPSILON) return true;

	return false;
}

bool Sphere::Intersect(const Ray& ray, Intersection& sr)
{
	Vector temp = ray.o - center;
	float a = Dot(ray.d, ray.d);
	float b = 2 * Dot(temp, ray.d);
	float c = Dot(temp, temp) - radius * radius;

	float t1;
	float t2;
	if (!Quadratic(a, b, c, &t1, &t2))
	{
		return false;
	}
	else
	{
		float t = Min(t1, t2);

		if (t > EPSILON && t < sr.t)
		{
			ray.rayEpsilon = 1e-3f * t;
			sr.normal = (temp + ray.d * t) / radius;
			sr.ray = ray;
			sr.t = t;
			sr.hitPoint = ray(t);
			sr.hitObject = true;
			sr.material = GetMaterial();
			return true;
		}
	}

	return false;
}

BBox Sphere::Bounds() const
{
	Vector dir(radius, radius, radius);
	return BBox(center - dir,
			center + dir);
}
