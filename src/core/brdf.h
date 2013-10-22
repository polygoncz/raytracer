#pragma once

#ifndef BXDF_H
#define BXDF_H


#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

enum BxDFType
{
	BSDF_REFLECTION		= 1,
	BSDF_TRANSMISSION	= 2,
	BSDF_DIFFUSE		= 4,
	BSDF_SPECULAR		= 8,
	BSDF_AMBIENT		= 16
};

class BxDF
{
public:
	BxDF(BxDFType t);
	BxDF(const BxDF& brdf);
	virtual ~BxDF();

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

	bool MatchesType(BxDFType flags) const;
private:
	BxDFType type;
};

#endif // !BXDF_H