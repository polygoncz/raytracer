#include "phong.h"
#include "brdf/lambert.h"
#include "brdf/specular.h"
#include "brdf/flat.h"
#include "brdf/reflection.h"
#include "brdf/transmittance.h"

Phong::Phong(const RGBColor& baseColor, const RGBColor& specularColor,
			 const RGBColor& reflectionColor, const RGBColor& refractionColor,
			 float ca, float cd, float exp, float ior)
		: baseColor(baseColor), specularColor(specularColor),
		  reflectionColor(reflectionColor), refractionColor(refractionColor),
		  ca(ca), cd(cd), exp(exp), ior(ior), Material()
{}

Phong::~Phong(void)
{}

BSDF* Phong::GetBSDF() const
{
	BSDF* bsdf = new BSDF();

	bsdf->Add(new Ambient(baseColor * ca));
	bsdf->Add(new Lambert(cd, baseColor));
	bsdf->Add(new Specular(exp, specularColor));
	bsdf->Add(new Reflection(reflectionColor));
	bsdf->Add(new Transmittance(refractionColor, ior));

	return bsdf;
}