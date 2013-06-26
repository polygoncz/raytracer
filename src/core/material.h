#pragma once

#include "color.h"
#include "core.h"
#include "intersection.h"

class RGBColor;
class Intersection;

class Material
{
public:
    Material(void) {}
    Material(const Material& material) {}
    virtual ~Material() {}

    virtual Material* clone() const = 0;

    virtual RGBColor shade(const Intersection& sr) const = 0;
};
