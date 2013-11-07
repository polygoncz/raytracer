#pragma once

#ifndef REFLECTION_BRDF_H
#define REFLECTION_BRDF_H

#include "core/brdf.h"
#include "core/color.h"

class Reflection : public BxDF
{
public:
	Reflection(const RGBColor& c);
	virtual ~Reflection();
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;

private:
	RGBColor c;
};



#endif // !REFLECTION_BRDF_H
