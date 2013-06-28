#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/light.h"

class AmbientLight : public Light
{
public:
    AmbientLight(void);
    AmbientLight(const AmbientLight& light);
    AmbientLight(double _ls, const RGBColor& _c);
    virtual ~AmbientLight(void);

    virtual Vector GetDirection(const Intersection& sr) const;
    virtual RGBColor L(const Intersection& sr) const;

private:
    double ls; //Intensity
    RGBColor c; //Color
};

inline Vector AmbientLight::GetDirection(const Intersection& sr) const
{
    return Vector(0.0, 0.0, 0.0);
}

inline RGBColor AmbientLight::L(const Intersection& sr) const
{
    return (ls * c);
}