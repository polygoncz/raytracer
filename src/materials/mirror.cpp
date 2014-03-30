#include "materials/mirror.h"

#include "brdf/reflection.h"

Material* Mirror::Clone() const
{
	return new Mirror(*this);
}

BSDF* Mirror::GetBSDF() const
{
	BSDF* bsdf = new BSDF();

	bsdf->Add(new Reflection(WHITE));

	return bsdf;
}