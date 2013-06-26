#pragma once

#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

class BRDF
{
public:
	BRDF(void) {}
	BRDF(const BRDF& brdf) {}
	virtual ~BRDF() {}

	virtual BRDF* clone() const = 0;

	virtual RGBColor f(const Intersection& sr, const Vector& wi, const Vector& wo) const = 0;
	virtual RGBColor sampleF(const Intersection& sr, const Vector& wi, const Vector& wo) const = 0;
	virtual RGBColor rho(const Intersection& sr, const Vector& wo) const = 0;
};