#include "phong.h"
#include "brdf/lambert.h"
#include "brdf/specular.h"
#include "brdf/flat.h"
#include "brdf/reflection.h"
#include "brdf/transmittance.h"

Phong::Phong(const RGBColor& baseColor, const RGBColor& specularColor,
			 float ca, float cd, float exp)
		: baseColor(baseColor), specularColor(specularColor),
		  ca(ca), cd(cd), exp(exp), Material()
{}

Phong::~Phong(void)
{}

BSDF* Phong::GetBSDF(const Vector& normal, const Vector& incident) const
{
	BSDF* bsdf = new BSDF();

	bsdf->Add(new Ambient(baseColor * ca));
	bsdf->Add(new Lambert(cd, baseColor));
	bsdf->Add(new Specular(exp, specularColor));

	return bsdf;
}