#include "core/brdf.h"

BxDF::BxDF(BxDFType t)
	: type(t)
{}

BxDF::BxDF(const BxDF& brdf)
	: type(brdf.type)
{}

BxDF::~BxDF()
{}

RGBColor BxDF::F(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor BxDF::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor BxDF::Rho(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return BLACK;
}

bool BxDF::MatchesType(BxDFType flags) const
{
	return (type & flags) == type;
}