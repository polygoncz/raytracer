#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/color.h"
#include "core/brdf.h"

class Lambert: public BRDF
{
public:
	Lambert(void);
	Lambert(const Lambert& mat);
	Lambert(float _kd, const RGBColor& _cd);
	virtual ~Lambert(void);

	virtual BRDF* Clone() const;

	virtual RGBColor F(const Vector& wi, const Vector& wo,
		const Normal& n) const;
	virtual RGBColor SampleF(const Vector& wi, const Vector& wo,
		const Normal& n) const;
	virtual RGBColor Rho(const Vector& wi, const Vector& wo,
		const Normal& n) const;

private:
	float kd;
	RGBColor cd;
};

inline RGBColor Lambert::F(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	return (kd * cd) * INV_PI;
}

inline RGBColor Lambert::SampleF(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	return BLACK;
}

inline RGBColor Lambert::Rho(const Vector& wi, const Vector& wo,
	const Normal& n) const
{
	return kd * cd;
}
