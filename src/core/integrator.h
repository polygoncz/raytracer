#pragma once

#include "geometry.h"
#include "color.h"

class Integrator
{
public:
    Integrator() {}
    Integrator(const Integrator& tr) {}
    virtual ~Integrator() {}

    virtual RGBColor traceRay(const Ray& ray) const = 0;
};