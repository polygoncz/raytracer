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

	virtual BRDF* Clone() const = 0;

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const = 0;
	virtual RGBColor SampleF(const Vector& wi, const Vector& wo, const Normal& n) const = 0;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const = 0;
};