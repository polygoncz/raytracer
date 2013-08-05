#include "matte.h"
#include "brdf/lambert.h"
#include "brdf/specular.h"

Matte::Matte()
		: Material(), ambientBRDF(NULL), diffuseBRDF(NULL)
{
}

Matte::Matte(const RGBColor& baseColor, float ca, float cd)
		: Material()
{
	ambientBRDF = new Lambert(ca, baseColor);
	diffuseBRDF = new Lambert(cd, baseColor);
}

Matte::Matte(const Matte& mat)
		: Material(mat)
{
	if (mat.ambientBRDF) ambientBRDF = mat.ambientBRDF->Clone();
	if (mat.diffuseBRDF) diffuseBRDF = mat.diffuseBRDF->Clone();
}

Matte::~Matte(void)
{
	if (ambientBRDF != NULL)
	{
		delete ambientBRDF;
		ambientBRDF = NULL;
	}

	if (diffuseBRDF != NULL)
	{
		delete diffuseBRDF;
		diffuseBRDF = NULL;
	}
}

Material* Matte::Clone() const
{
	return new Matte(*this);
}
