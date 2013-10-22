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
	{
		if (bxdfs[i] != NULL)
			delete bxdfs[i];
	}
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