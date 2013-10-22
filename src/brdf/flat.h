#pragma once

#ifndef FLAT_H
#define FLAT_H


#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

class Ambient: public BxDF
{
public:
	Ambient(const Ambient& mat);
	Ambient(const RGBColor& _cd);
	virtual ~Ambient(void);

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

private:
	RGBColor cd;
};
#endif // !AMBIENT_BRDF_H