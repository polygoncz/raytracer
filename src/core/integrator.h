#pragma once

#include "geometry.h"
#include "color.h"

class Integrator
{
public:
	Integrator(Scene* scene);
	Integrator(const Integrator& tr);
	virtual ~Integrator();

	virtual RGBColor L(const Ray& ray) const = 0;

protected:
	Scene* scene;
};
