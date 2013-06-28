#include "raytracer.h"

Raytracer::Raytracer(Scene* sc, RenderThread* thr)
	: Renderer(sc, thr) { }

Raytracer::~Raytracer() { }

void Raytracer::Render() const
{
	Ray ray;
	double zw = 100.0;
	RGBColor color;

	for (int r = 0; r < film->height; r++)
	{
		for (int c = 0; c < film->width; c++)
		{
			CameraSample sample;
			sample.x = c;
			sample.y = r;
			cam->GenerateRay(sample, &ray);
			color = integrator->L(ray);

			DisplayPixel(c, r, color);
		}
	}
}