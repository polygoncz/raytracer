#include "brdf/reflection.h"

Reflection::Reflection(const RGBColor& c)
	: c(c), BxDF(BSDF_REFLECTION)
{}

Reflection::~Reflection()
{}

RGBColor Reflection::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	wo = wi - 2 * Dot(n, wi) * n;
	wo.Normalize();

	return c;
}