#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

class Lambert : public BRDF
{
public:
    Lambert(void);
    Lambert(const Lambert& mat);
    Lambert(float _kd, const RGBColor& _cd);
    virtual ~Lambert(void);

    virtual BRDF* clone() const;

    virtual RGBColor f(const Intersection& sr, const Vector& wi, const Vector& wo) const;
    virtual RGBColor sampleF(const Intersection& sr, const Vector& wi, const Vector& wo) const;
    virtual RGBColor rho(const Intersection& sr, const Vector& wo) const;

private:
    float kd;
    RGBColor cd;
};

inline RGBColor Lambert::f(const Intersection& sr, const Vector& wi, const Vector& wo) const
{
    return (kd * cd) * INV_PI;
}

inline RGBColor Lambert::sampleF(const Intersection& sr, const Vector& wi, const Vector& wo) const
{
    return BLACK;
}

inline RGBColor Lambert::rho(const Intersection& sr, const Vector& wo) const
{
    return kd*cd;
}