#include "sphere.h"

#include "core/constants.h"
#include "core/core.h"
#include "core/geometry.h"

#include <cmath>


float Min(float t1, float t2);
bool Quadratic(float a, float b, float c, float* t0, float* t1);

Sphere::Sphere(void) : Primitive() {}

Sphere::Sphere(const Point& _center, float _radius, Material* _material)
    : Primitive(_material), center(_center), radius(_radius)
{}

Sphere::Sphere(const Sphere& sphere)
    : Primitive(sphere.material), center(sphere.center), radius(sphere.radius)
{}

Sphere::~Sphere(void)
{}

bool Sphere::hit(const Ray& ray, float& tmin, Intersection& sr) const
{
    Vector temp = ray.o - center;
    float a = Dot(ray.d, ray.d);
    float b = 2 * Dot(temp, ray.d);
    float c = Dot(temp, temp) - radius * radius;
    float disc = b*b - 4*a*c;

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
            tmin = t;
            sr.normal = (temp + ray.d * t) / radius;
            return true;
        }
    }

    return false;
}

inline float Min(float t1, float t2)
{
	return t1 < t2 ? t1 : t2;
}

inline bool Quadratic(float a, float b, float c, float* t0, float* t1)
{
	float disc = b*b - 4*a*c;

	if (disc < 0.f)
	{
		return false;
	}

	float e = sqrt(disc);
	float lowerPart = 2.0 * a;

	*t0 = (-b + e) / lowerPart;
	*t1 = (-b - e) / lowerPart;

	return true;
}