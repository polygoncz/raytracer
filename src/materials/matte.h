#pragma once

#ifndef MATTE_H
#define MATTE_H


#include "core/core.h"
#include "core/constants.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/material.h"
#include "core/brdf.h"
#include "core/scene.h"

class Ambient;

class Matte: public Material
{
public:
	Matte(const Matte& mat);
	Matte(const RGBColor& baseColor, float ca, float cd);
	virtual ~Matte(void);

	virtual BSDF* GetBSDF() const;

private:
	RGBColor color;
};

#endif // !MATTE_H