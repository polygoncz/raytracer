#pragma once

#include "materials/phong.h"

class ReflectivePhong : public Phong
{
public:
	ReflectivePhong(const RGBColor& baseColor, const RGBColor& specularColor, float ca, float cd, float cr, float exp);
	ReflectivePhong(const RGBColor& baseColor, const RGBColor& specularColor, const RGBColor& reflectionColor, float ca, float cd, float cr, float exp);
	ReflectivePhong(const ReflectivePhong& mat);
	virtual ~ReflectivePhong() {};

	virtual Material* Clone() const;
	virtual BSDF* GetBSDF(const Vector& normal, const Vector& incident) const;

protected:
	float cr;
	RGBColor reflectionColor;
};