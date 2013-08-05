#pragma once

#include "color.h"
#include "core.h"
#include "intersection.h"

class RGBColor;
class Intersection;

class Material
{
public:
	Material(void)
	{
	}
	Material(const Material& material)
	{
	}
	virtual ~Material()
	{
	}

	virtual Material* Clone() const = 0;

	virtual RGBColor L(const Intersection& inter, const Vector& wi,
		const RGBColor& li) const = 0;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi,
		const RGBColor& li) const = 0;
};
