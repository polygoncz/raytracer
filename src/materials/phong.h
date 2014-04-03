#pragma once

#include "core/core.h"
#include "core/constants.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/material.h"
#include "core/brdf.h"
#include "core/scene.h"
#include <cmath>

class Phong: public Material
{
public:
	Phong(const RGBColor& baseColor, const RGBColor& specularColor,
		  float ca, float cd, float exp);
	virtual ~Phong(void);

	virtual BSDF* GetBSDF(const Vector& normal, const Vector& incident) const;
protected:
	RGBColor baseColor, specularColor;
	float exp;
	float ca, cd;
};