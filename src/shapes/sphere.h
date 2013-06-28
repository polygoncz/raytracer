#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/primitive.h"

class Sphere : public Primitive
{
public:
    Sphere(void);
    Sphere(const Point& _center, float _radius, Material* _material);
    Sphere(const Sphere& sphere);
    virtual ~Sphere(void);

    virtual bool Hit(const Ray& ray, float& tmin, Intersection& sr) const;
private:
    Point center;
    float radius;
};