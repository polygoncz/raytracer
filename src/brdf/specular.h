#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

#include <cmath>

class Specular: public BRDF
{
public:
	Specular(void);
	Specular(const Specular& spec);
	Specular(float exp, const RGBColor& ks);
	virtual ~Specular(void);

	virtual BRDF* Clone() const;

	virtual RGBColor F(const Vector& wi, const Vector& wo,
		const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, const Vector& wo,
		const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo,
		const Normal& n) const;
private:
	float exp;
	RGBColor ks;
};

inline RGBColor Specular::F(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	float nDotWi = Dot(n, wi);
	Vector r = (n * nDotWi * 2) - wi;
	float rDotWo = Dot(r, wo);

	if (rDotWo > 0.0) return ks * powf(rDotWo, exp);

	return BLACK;
}

inline RGBColor Specular::SampleF(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	return BLACK;
}

inline RGBColor Specular::Rho(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	return BLACK;
}
