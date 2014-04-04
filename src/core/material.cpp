#include "core/material.h"

#include <cassert>

/************************************************************************/
/* BSDF methods                                                         */
/************************************************************************/

BSDF::BSDF(void)
{
	nBxDFs = 0;
}

BSDF::~BSDF(void)
{
	for (uint32_t i = 0; i < nBxDFs; ++i)
		if (bxdfs[i] != NULL)
			delete bxdfs[i];
}

void BSDF::Add(BxDF* bxdf)
{
	assert(nBxDFs < MAX_BXDFS);
	bxdfs[nBxDFs++] = bxdf;
}

uint32_t BSDF::NumComponents() const
{
	return nBxDFs;
}

BxDF* BSDF::operator [](int i) const
{
	assert(i < nBxDFs);
	return bxdfs[i];
}

/************************************************************************/
/* Material methods                                                     */
/************************************************************************/

Material::Material(void)
{}

Material::Material(const Material& material)
{}

Material::~Material(void)
{}

/************************************************************************/
/* Helper functions                                                     */
/************************************************************************/
float SchlickReflectance(const Vector& normal, const Vector& incident, float n1, float n2)
{
	float r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	float cosI = -Dot(normal, incident);
	if (n1 > n2)
	{
		const float n = n1 / n2;
		const float sinT2 = n * n * (1.f - cosI * cosI);
		if (sinT2 > 1.f) return 1.f; //total internal reflection
		cosI = sqrtf(1.f - sinT2);
	}
	const float x = 1.f - cosI;
	return r0 + (1.0 - r0) * x * x * x * x * x;
}

float FresnelReflectance(const Vector& normal, const Vector& incident, float n1, float n2)
{
	const float n = n1 / n2;
	const float cosI = -Dot(normal, incident);
	const float sinT2 = n * n * (1.f - cosI * cosI);
	if (sinT2 > 1.f) return 1.f; // total internal reflection
	const float cosT = sqrtf(1.f - sinT2);

	float rs = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	rs *= rs;

	float rp = (n1 * cosT - n2 * cosI) / (n1 * cosT + n2 * cosI);
	rp *= rp;

	return (rs + rp) * 0.5f;
}