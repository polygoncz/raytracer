#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/material.h"
#include "core/brdf.h"
#include "core/scene.h"

class Phong : public Material
{
public:
    Phong(const Phong& mat);
    Phong(const RGBColor& baseColor, const RGBColor& specularColor, float ca, float cd, float exp);
    virtual ~Phong(void);

    virtual Material* clone() const;
    virtual RGBColor shade(const Intersection& sr) const;
private:
    Phong();
    BRDF* ambientBRDF;
    BRDF* diffuseBRDF;
    BRDF* specularBRDF;
};

inline RGBColor Phong::shade(const Intersection& sr) const
{
    Vector wo = -sr.ray.d;
    RGBColor L = ambientBRDF->rho(sr, wo) * sr.scene.ambient->L(sr);

    for (vector<Light*>::iterator itr = sr.scene.lights.begin(); itr != sr.scene.lights.end(); itr++)
    {
        Light* light = *itr;
        Vector wi = light->getDirection(sr);
        float ndotwi = Dot(sr.normal, wi);

        if (ndotwi > 0.0)
            L += (diffuseBRDF->f(sr, wi, wo) * light->L(sr) * ndotwi) + (specularBRDF->f(sr, wi, wo) * light->L(sr) * ndotwi);
    }

    return L;
}