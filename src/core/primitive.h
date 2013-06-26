#pragma once

#include "geometry.h"
#include "material.h"
#include "intersection.h"

class Primitive
{
public:
    Primitive(void);
    Primitive(Material* _mat);
    Primitive(const Primitive& prm);

    virtual ~Primitive();

    virtual bool hit(const Ray& ray, float& tmin, Intersection& sr) const = 0;

    Material* getMaterial(void) const;
    void setMaterial(Material* _material);

protected:
    mutable Material* material;
};

