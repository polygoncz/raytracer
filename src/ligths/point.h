#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/light.h"

class PointLight: public Light
{
public:
	PointLight(void);
	PointLight(const PointLight& light);
	PointLight(float _ls, const RGBColor& _c, const Point& _loc);
	virtual ~PointLight(void);

	virtual Vector GetDirection(const Intersection& sr) const;
	virtual RGBColor L(const Intersection& sr) const;

private:
	Point location; //position
	float ls; //intensity
	RGBColor c; //color
};

inline Vector PointLight::GetDirection(const Intersection& sr) const
{
	return (location - sr.hitPoint).Normalize();
}

inline RGBColor PointLight::L(const Intersection& sr) const
{
	return (ls * c);
}
