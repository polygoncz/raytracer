#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

#include <cmath>

class Specular : public BRDF
{
public:
    Specular(void);
    Specular(const Specular& spec);
    Specular(float exp, const RGBColor& ks);
    virtual ~Specular(void);

    virtual BRDF* clone() const;

    virtual RGBColor f(const Intersection& sr, const Vector& wi, const Vector& wo) const;
    virtual RGBColor sampleF(const Intersection& sr, const Vector& wi, const Vector& wo) const;
    virtual RGBColor rho(const Intersection& sr, const Vector& wo) const;
private:
    float exp;
    RGBColor ks;
};

inline RGBColor Specular::f(const Intersection& sr, const Vector& wi, const Vector& wo) const
{
    RGBColor L = BLACK;
    float nDotWi = Dot(sr.normal, wi);
    Vector r = (sr.normal * nDotWi * 2) - wi;
    float rDotWo = Dot(r, wo);

    if (rDotWo > 0.0)
        L = ks * powf(rDotWo, exp);

    return L;
}

inline RGBColor Specular::sampleF(const Intersection& sr, const Vector& wi, const Vector& wo) const
{
    return BLACK;
}

inline RGBColor Specular::rho(const Intersection& sr, const Vector& wo) const
{
    return BLACK;
}