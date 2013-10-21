#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/color.h"
#include "core/scene.h"
#include "core/integrator.h"
#include "core/primitive.h"

class WhittedTracer: public Integrator
{
public:
	WhittedTracer(int _maxDepth = 5);
	virtual ~WhittedTracer(void);

	virtual RGBColor L(const Ray& ray, const Scene& scene, Intersection& inter) const;

private:
	int maxDepth;
};
