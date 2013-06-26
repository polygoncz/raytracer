#include "sphere.h"

#include "core/constants.h"
#include "core/core.h"
#include "core/geometry.h"

#include <cmath>


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

    if (disc < 0.0)
    {
        return false;
    }
    else
    {
        float e = sqrt(disc);
        float lowerPart = 2.0 * a;
        float t = (-b - e) / lowerPart;

        if (t > EPSILON)
        {
            tmin = t;
            sr.normal = (temp + ray.d * t) / radius;
            sr.hitPoint = ray(t);
            return true;
        }

        t = (-b + e) / lowerPart;
        if (t > EPSILON)
        {
            tmin = t;
            sr.normal = (temp + ray.d * t) / radius;
            sr.hitPoint = ray(t);
            return true;
        }
    }

    return false;
}