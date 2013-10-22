#include "brdf/flat.h"

Ambient::Ambient(const Ambient& bxdf)
	: cd(bxdf.cd),
	BxDF(BSDF_DIFFUSE)
{}

Ambient::Ambient(const RGBColor& _cd)
	: cd(_cd),
	BxDF(BSDF_AMBIENT)
{}

Ambient::~Ambient(void)
{}

RGBColor Ambient::F(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor Ambient::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor Ambient::Rho(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return cd;
}
