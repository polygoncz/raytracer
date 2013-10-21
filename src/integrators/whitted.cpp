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
		return BLACK;

	RGBColor l;
	Reference<Material> mat = inter.material;
	l += mat->Ambient(inter, scene.ambient->GetDirection(inter), scene.ambient->L(inter));

	for (uint32_t i = 0; i < scene.lights.size(); i++)
	{
		Light* light = scene.lights[i];
		Vector shDir = light->GetDirection(inter);
		STATS_ADD_SHADOW_RAY();
		Ray shadowRay(inter.hitPoint + inter.normal * inter.ray.rayEpsilon,	shDir, 0.f, INFINITY, inter.ray.rayEpsilon);
		if (!scene.IntersectP(shadowRay))
		{
			l += mat->L(inter, light->GetDirection(inter), light->L(inter));
		}
	}

	if (mat->Reflectivity() != BLACK)
	{
		Vector newDir = ray.d - 2 * Dot(inter.normal, ray.d) * inter.normal;
		newDir.Normalize();

		Ray newRay(inter.hitPoint + inter.normal * inter.ray.rayEpsilon, newDir, 0.0f, INFINITY, EPSILON, ray.depth + 1);

		Intersection intRefl;
		if (scene.Intersect(newRay, intRefl))
			l += mat->Reflectivity() * L(newRay, scene, intRefl);
	}

	//Piece of shit :D:D:D
	/*if (mat->Transmitance() != BLACK)
	{
		Vector wo = -ray.d;
		Normal n = inter.normal;

		float nDotWo = Dot(inter.normal, wo);
		if (nDotWo < 0.0f) //Uhel je ostry
		{

		}
	}*/

	return l;
}