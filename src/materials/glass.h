#pragma once

#ifndef GLASS_H
#define GLASS_H

#include "core/material.h"

class Glass : public Material
{
public:
	Glass();
	Glass(const Glass& mat) {};
	virtual ~Glass() {};

	virtual Material* Clone() const;
	virtual RGBColor L(const Intersection& inter, const Vector& wi, const RGBColor& li) const;
	virtual RGBColor Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const;
	virtual RGBColor Transmitance() const { return WHITE; };

private:
	float ior;
};

#endif // !GLASS_H
