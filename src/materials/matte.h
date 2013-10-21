#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/material.h"
#include "core/brdf.h"
#include "core/scene.h"
#include <cmath>

class Matte: public Material
{
public:
	Matte(const Matte& mat);
	Matte(const RGBColor& baseColor, float ca, float cd);
	virtual ~Matte(void);

	virtual Material* Clone() const;
	virtual RGBColor L(const Intersection& inter, const Vector& wi, const RGBColor& li) const;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const;

private:
	Matte();
	BxDF* ambientBRDF;
	BxDF* diffuseBRDF;
};

inline RGBColor Matte::Ambient(const Intersection& inter, const Vector& wi,
	const RGBColor& li) const
{
	return ambientBRDF->Rho(wi, -inter.ray.d, inter.normal) * li;
}

inline RGBColor Matte::L(const Intersection& inter, const Vector& wi,
	const RGBColor& li) const
{
	float ndotwi = Dot(inter.normal, wi);

	if (ndotwi > 0.0) return (diffuseBRDF->F(wi, -inter.ray.d, inter.normal)
			* li * ndotwi);
	return BLACK;
}
