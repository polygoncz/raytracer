#include "raytracer.h"
#include "core/statistics.h"
#include "integrators/whitted.h"
#include <omp.h>

Raytracer::Raytracer(Scene* sc, RenderThread* thr, int perPixelSamples /*= 1*/, int numberOfThreads /*= 1*/)
		: perPixelSamples(perPixelSamples), numberOfThreads(numberOfThreads), pixelArea(thr), Renderer(sc)
{
	this->integrator = new WhittedTracer();
}

Raytracer::~Raytracer()
{
}

void Raytracer::Render() const
{
	int n = static_cast<int>(sqrt(perPixelSamples));
	float diff = 1.f / n;

	//omp_set_num_threads(numberOfThreads);

	//#pragma omp parallel for schedule(guided)
	for (int r = 0; r < film->height; r++)
	{
		for (int c = 0; c < film->width; c++)
		{
			RGBColor color;
			CameraSample sample;
			Ray ray;

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

			//#pragma omp critical
			{
				DisplayPixel(c, r, color);
			}
		}
	}
}

void Raytracer::DisplayPixel(int x, int y, RGBColor& in) const
{
	RGBColor color = in.Clamp();

	pixelArea->setPixel(x, y, (int) (color.r * 255), (int) (color.g * 255),
			(int) (color.b * 255));
}

void Raytracer::SetPixelArea(RenderThread* thread)
{
	this->pixelArea = thread;
}
