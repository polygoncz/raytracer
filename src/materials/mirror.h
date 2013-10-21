#pragma once

#include "core/material.h"

class Mirror : public Material
{
public:
	Mirror() {};
	Mirror(const Mirror& mat) {};
	virtual ~Mirror() {};

	virtual Material* Clone() const;
	virtual RGBColor L(const Intersection& inter, const Vector& wi, const RGBColor& li) const;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const;
	virtual RGBColor Reflectivity() const { return WHITE; };
};