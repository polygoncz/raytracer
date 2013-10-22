#include "specular.h"

Specular::Specular(float exp, const RGBColor& ks)
		: exp(exp), ks(ks),
		BxDF(BSDF_SPECULAR)
{}

Specular::Specular(const Specular& spec)
		: exp(spec.exp), ks(spec.ks),
		BxDF(BSDF_SPECULAR)
{}

Specular::~Specular(void)
{}

RGBColor Specular::F(const Vector& wi, const Vector& wo, const Normal& n) const
{
	float nDotWi = Dot(n, wi);
	Vector r = (n * nDotWi * 2) - wi;
	float rDotWo = Dot(r, wo);

	if (rDotWo > 0.0)
		return ks * powf(rDotWo, exp);

	return BLACK;
}

RGBColor Specular::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor Specular::Rho(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return BLACK;
}
