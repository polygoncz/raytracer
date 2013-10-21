#pragma once

#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

enum BxDFType
{
	BSDF_REFLECTION		= 1,
	BSDF_TRANSMISSION	= 2,
	BSDF_DIFFUSE		= 4,
	BSDF_SPECULAR		= 8
};

class BxDF
{
public:
	BxDF(BxDFType t);
	BxDF(const BxDF& brdf);
	virtual ~BxDF();

	virtual BxDF* Clone() const = 0;

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const = 0;
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const = 0;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const = 0;
private:
	BxDFType type;
};
