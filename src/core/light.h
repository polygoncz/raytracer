#pragma once

#include "geometry.h"
#include "color.h"
#include "intersection.h"

class Vector;
class RGBColor;

class Light
{
public:
	Light(void) {}
	Light(const Light& light) {}
	virtual ~Light() {}

	virtual Vector GetDirection(const Intersection& sr) const = 0;
	virtual RGBColor L(const Intersection& sr) const = 0;
};