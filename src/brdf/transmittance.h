#pragma once

#ifndef TRANSMITTANCE_BRDF_H
#define TRANSMITTANCE_BRDF_H

#include "core/brdf.h"

class Transmittance : public BxDF
{
public:
	Transmittance(const RGBColor& c, float ior);
	virtual ~Transmittance();
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;

private:
	RGBColor c;
	float ior;
};


#endif // !TRANSMITTANCE_BRDF_H