#include "matte.h"
#include "brdf/lambert.h"
#include "brdf/flat.h"

Matte::Matte(const RGBColor& baseColor, float ca, float cd)
		: color(baseColor), Material()
{}

Matte::~Matte(void)
{}

BSDF* Matte::GetBSDF(const Vector& normal, const Vector& incident) const
{
	BSDF* bsdf = new BSDF();

	bsdf->Add(new Ambient(color));
	bsdf->Add(new Lambert(1.f, color));

	return bsdf;
}