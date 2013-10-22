#include "lambert.h"

Lambert::Lambert(const Lambert& bxdf)
		: kd(bxdf.kd), cd(bxdf.cd),
		BxDF(BSDF_DIFFUSE)
{}

Lambert::Lambert(float _kd, const RGBColor& _cd)
		: kd(_kd), cd(_cd),
		BxDF(BSDF_DIFFUSE)
{}

Lambert::~Lambert(void)
{}

RGBColor Lambert::F(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return (kd * cd) * INV_PI;
}

RGBColor Lambert::SampleF(const Vector& wi, Vector& wo, const Normal& n) const
{
	return BLACK;
}

RGBColor Lambert::Rho(const Vector& wi, const Vector& wo, const Normal& n) const
{
	return kd * cd;
}
