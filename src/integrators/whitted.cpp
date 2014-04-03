#include "whitted.h"
#include "core/geometry.h"

#include "core/constants.h"
#include "core/light.h"

#include "core/statistics.h"

#include <vector>
#include <cstdint>

using namespace std;

class Light;

WhittedTracer::WhittedTracer(int _maxDepth)
	: maxDepth(_maxDepth)
{}

WhittedTracer::~WhittedTracer(void)
{
}

RGBColor WhittedTracer::L(const Ray& ray, const Scene& scene, Intersection& inter) const
{
	if (ray.depth == maxDepth)
		return scene.background;

	RGBColor l;

	BSDF* bsdf = inter.material->GetBSDF(inter.normal, -inter.ray.d);

	for (uint32_t i = 0; i < bsdf->NumComponents(); ++i)
	{
		const BxDF* bxdf = bsdf->operator[](i);
		if (bxdf->MatchesType(BSDF_AMBIENT))
		{
			l += bxdf->F(scene.ambient->GetDirection(inter), inter.ray.d, inter.normal) * scene.ambient->L(inter);
		}
		else if (bxdf->MatchesType(BSDF_DIFFUSE) || bxdf->MatchesType(BSDF_SPECULAR))
		{
			for (uint32_t i = 0; i < scene.lights.size(); i++)
			{
				Light* light = scene.lights[i];
				Vector shDir = light->GetDirection(inter);
				STATS_ADD_SHADOW_RAY();
				Ray shadowRay(inter.hitPoint + inter.normal * inter.ray.rayEpsilon,	shDir, 0.f, INFINITY, inter.ray.rayEpsilon);
				if (!scene.IntersectP(shadowRay))
				{
					float ndotwi = Dot(inter.normal, shDir);
					if (ndotwi > 0.f)
						l += bxdf->F(shDir, -inter.ray.d, inter.normal) * light->L(inter) * ndotwi;
				}
			}
		}
		else if (bxdf->MatchesType(BSDF_REFLECTION) || bxdf->MatchesType(BSDF_TRANSMISSION))
		{
			Vector wo;
			const Vector wi = inter.ray.d;
			RGBColor fL = bxdf->SampleF(wi, wo, inter.normal);
			Intersection newInter;
			Ray newRay(inter.hitPoint + inter.normal * inter.ray.rayEpsilon, wo, 0.0f, INFINITY, EPSILON, ray.depth + 1);
			
			if (scene.Intersect(newRay, newInter))
				l += fL * L(newRay, scene, newInter);
			else
				l += fL * scene.background;
		}
	}

	delete bsdf;

	return l;
}