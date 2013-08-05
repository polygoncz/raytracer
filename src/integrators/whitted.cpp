#include "whitted.h"
#include "core/geometry.h"

#include "core/constants.h"
#include "core/light.h"

#include <vector>

using namespace std;

class Light;

WhittedTracer::WhittedTracer(Scene* scene)
		: Integrator(scene)
{
}

WhittedTracer::WhittedTracer(const WhittedTracer& tr)
		: Integrator(tr)
{
}

WhittedTracer::~WhittedTracer(void)
{
}

RGBColor WhittedTracer::L(const Ray& ray) const
{
	Intersection inter;
	float tMin = INFINITY;
	float t = 0.f;

	if (scene->Intersect(ray, inter))
	{
		RGBColor l;
		inter.ray = ray;
		l += inter.material->Ambient(inter, scene->ambient->GetDirection(inter),
				scene->ambient->L(inter));

		for (vector<Light*>::const_iterator itr = scene->lights.begin();
				itr != scene->lights.end(); itr++)
		{
			Light* light = (*itr);
			Vector shDir = light->GetDirection(inter);
			Ray shadowRay(inter.hitPoint + inter.normal * inter.ray.rayEpsilon,
					shDir, 0.f, INFINITY, inter.ray.rayEpsilon);
			if (!scene->IntersectP(shadowRay))
			{
				l += inter.material->L(inter, light->GetDirection(inter),
						light->L(inter));
			}
		}

		return l;
	}

	return scene->background;
}
