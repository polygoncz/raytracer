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
		  const RGBColor& reflectionColor, const RGBColor& refractionColor,
		  float ca, float cd, float exp, float ior);
	virtual ~Phong(void);

	virtual BSDF* GetBSDF() const;
private:
	RGBColor baseColor, specularColor, reflectionColor, refractionColor;
	float exp;
	float ca, cd;
	float ior;
};