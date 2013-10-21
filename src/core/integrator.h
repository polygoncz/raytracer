#pragma once

#include "geometry.h"
#include "color.h"

class Integrator
{
public:
	Integrator();
	Integrator(const Integrator& tr);
	virtual ~Integrator();

	virtual RGBColor L(const Ray& ray, const Scene& scene, Intersection& inter) const = 0;
};
