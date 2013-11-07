#include "brdf/transmittance.h"
#include <cmath>

Transmittance::Transmittance(const RGBColor& c, float ior)
	: c(c), ior(ior), BxDF(BSDF_TRANSMISSION)
{}

Transmittance::~Transmittance()
{}

RGBColor Transmittance::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	float eta = ior;

	Normal ns = n;
	float nDotWi = Dot(wo, ns);
	if (nDotWi > 0.0f) //Uhel je tupy (jdeme zevnitr ven)
	{
		eta = 1.f / ior;
		ns = -ns;
	}

	float w = -(nDotWi) / (wi.Length() * n.Length());
	float r = eta;
	float k = sqrtf(1 + (w - r)*(w + r));

	wo = r*wi + (w - k)*n;

	return c;
}