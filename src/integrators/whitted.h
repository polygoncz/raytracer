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
	WhittedTracer(Scene* scene);
	WhittedTracer(const WhittedTracer& tr);
	virtual ~WhittedTracer(void);

	virtual RGBColor L(const Ray& ray) const;
};
