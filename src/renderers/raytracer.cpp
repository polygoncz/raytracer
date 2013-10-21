#include "raytracer.h"
#include "core/statistics.h"
#include "integrators/whitted.h"

Raytracer::Raytracer(Scene* sc, RenderThread* thr)
		: Renderer(sc, thr)
{
	this->integrator = new WhittedTracer();
}

Raytracer::~Raytracer()
{
}

void Raytracer::Render() const
{
	RGBColor color;
	CameraSample sample;

	for (int r = 0; r < film->height; r++)
	{
		for (int c = 0; c < film->width; c++)
		{
			Ray ray;
			sample.x = c;
			sample.y = r;
			cam->GenerateRay(sample, &ray);
			STATS_ADD_PRIMARY_RAY();

			Intersection inter;
			if (scene->Intersect(ray, inter))
			{
				color = integrator->L(ray, *scene, inter);
			}
			else
			{
				color = scene->background;
			}

			DisplayPixel(c, r, color);
		}
	}
}
