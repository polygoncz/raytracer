#include "phong.h"
#include "brdf/lambert.h"
#include "brdf/specular.h"

Phong::Phong()
		: Material(), ambientBRDF(NULL), diffuseBRDF(NULL), specularBRDF(NULL)
{
}

Phong::Phong(const RGBColor& baseColor, const RGBColor& specularColor, float ca,
	float cd, float exp)
		: Material()
{
	ambientBRDF = new Lambert(ca, baseColor);
	diffuseBRDF = new Lambert(cd, baseColor);
	specularBRDF = new Specular(exp, specularColor);
}

Phong::Phong(const Phong& mat)
		: Material(mat)
{
	if (mat.ambientBRDF) ambientBRDF = mat.ambientBRDF->Clone();
	if (mat.diffuseBRDF) diffuseBRDF = mat.diffuseBRDF->Clone();
	if (mat.specularBRDF) specularBRDF = mat.specularBRDF->Clone();
}

Phong::~Phong(void)
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

	if (specularBRDF != NULL)
	{
		delete specularBRDF;
		specularBRDF = NULL;
	}
}

Material* Phong::Clone() const
{
	return new Phong(*this);
}
