#pragma once

#ifndef LAMBERT_H
#define LAMBERT_H


#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

class Lambert: public BxDF
{
public:
	Lambert(const Lambert& mat);
	Lambert(float _kd, const RGBColor& _cd);
	virtual ~Lambert(void);

	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

private:
	float kd;
	RGBColor cd;
};

#endif // !LAMBERT_H