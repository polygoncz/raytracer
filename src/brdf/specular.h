#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

#include <cmath>

class Specular: public BxDF
{
public:
	Specular(const Specular& spec);
	Specular(float exp, const RGBColor& ks);
	virtual ~Specular(void);

	virtual BxDF* Clone() const;

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

private:
	float exp;
	RGBColor ks;
};