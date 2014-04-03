#include "glass.h"

#include "brdf/reflection.h"
#include "brdf/transmittance.h"

Glass::Glass()
	: ior(1.333f)
{ }

Material* Glass::Clone() const
{
	return new Glass(*this);
}

BSDF* Glass::GetBSDF(const Vector& normal, const Vector& incident) const
{
	BSDF* bsdf = new BSDF();

	float r = SchlickReflectance(normal, incident, 1.f, ior);

	bsdf->Add(new Reflection(WHITE * r));
	bsdf->Add(new Transmittance((1 - r) * WHITE, ior));

	return bsdf;
}