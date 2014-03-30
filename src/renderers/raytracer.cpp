#include "raytracer.h"
#include "core/statistics.h"
#include "integrators/whitted.h"
#include <omp.h>

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
	#pragma omp parallel for schedule(guided)
	for (int r = 0; r < film->height; r++)
	{
		for (int c = 0; c < film->width; c++)
		{
			RGBColor color;
			CameraSample sample;
			Ray ray;

			int n = 3;
			float diff = 1.f / n;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					sample.x = c + i * diff;
					sample.y = r + j * diff;
					cam->GenerateRay(sample, &ray);

					STATS_ADD_PRIMARY_RAY();

					Intersection inter;
					if (scene->Intersect(ray, inter))
					{
						color += integrator->L(ray, *scene, inter);
					}
					else
					{
						color += scene->background;
					}
				}
			}

			color /= (n*n);

			#pragma omp critical
			{
				DisplayPixel(c, r, color);
			}
		}
	}
}
