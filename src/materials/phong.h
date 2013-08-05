#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/material.h"
#include "core/brdf.h"
#include "core/scene.h"
#include <cmath>

class Phong: public Material
{
public:
	Phong(const Phong& mat);
	Phong(const RGBColor& baseColor, const RGBColor& specularColor, float ca,
		float cd, float exp);
	virtual ~Phong(void);

	virtual Material* Clone() const;
	virtual RGBColor L(const Intersection& inter, const Vector& wi,
		const RGBColor& li) const;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi,
		const RGBColor& li) const;
private:
	Phong();
	BRDF* ambientBRDF;
	BRDF* diffuseBRDF;
	BRDF* specularBRDF;
};

inline RGBColor Phong::Ambient(const Intersection& inter, const Vector& wi,
	const RGBColor& li) const
{
	return ambientBRDF->Rho(wi, -inter.ray.d, inter.normal) * li;
}

inline RGBColor Phong::L(const Intersection& inter, const Vector& wi,
	const RGBColor& li) const
{
	float ndotwi = Dot(inter.normal, wi);

	Vector wo = -inter.ray.d;

	if (ndotwi > 0.0) return (diffuseBRDF->F(wi, wo, inter.normal) * li * ndotwi)
			+ (specularBRDF->F(wi, wo, inter.normal) * li * ndotwi);

	return BLACK;
}
