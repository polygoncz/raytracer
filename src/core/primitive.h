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

    virtual bool Hit(const Ray& ray, float& tmin, Intersection& sr) const = 0;

    Material* GetMaterial(void) const;
    void SetMaterial(Material* _material);

protected:
    mutable Material* material;
};

