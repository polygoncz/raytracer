#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H


#include "color.h"
#include "core.h"
#include "intersection.h"
#include "reference.h"

class RGBColor;
class Intersection;

class Material : public ReferenceCounted
{
public:
	Material(void)
	{
	}
	Material(const Material& material)
	{
	}
	virtual ~Material()
	{
	}

	virtual Material* Clone() const = 0;

	virtual RGBColor L(const Intersection& inter, const Vector& wi, const RGBColor& li) const = 0;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const = 0;
	virtual RGBColor Reflectivity() const { return BLACK; }
	virtual RGBColor Transmitance() const { return BLACK; }
};

#endif