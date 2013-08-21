#include "raytracer.h"
#include "core/statistics.h"
#include "integrators/whitted.h"

Raytracer::Raytracer(Scene* sc, RenderThread* thr)
		: Renderer(sc, thr)
{
	this->integrator = new WhittedTracer(scene);
}

Raytracer::~Raytracer()
{
}

void Raytracer::Render() const
{
	Ray ray;
	RGBColor color;

	for (int r = 0; r < film->height; r++)
	{
		for (int c = 0; c < film->width; c++)
		{
			CameraSample sample;
			sample.x = c;
			sample.y = r;
			cam->GenerateRay(sample, &ray);
			STATS_ADD_PRIMARY_RAY();
			color = integrator->L(ray);

			DisplayPixel(c, r, color);
		}
	}
}
