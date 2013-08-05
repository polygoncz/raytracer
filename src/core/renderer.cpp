#include "renderer.h"

Renderer::Renderer(Scene* sc, RenderThread* thread)
		: scene(sc), pixelArea(thread)
{
	cam = scene->cam;
	film = scene->film;
	integrator = scene->tracer;
}

Renderer::~Renderer()
{
	if (scene != NULL) delete scene;
}

void Renderer::DisplayPixel(int x, int y, RGBColor& in) const
{
	RGBColor color = in.Clamp();

	pixelArea->setPixel(x, y, (int) (color.r * 255), (int) (color.g * 255),
			(int) (color.b * 255));
}

void Renderer::SetPixelArea(RenderThread* thread)
{
	this->pixelArea = thread;
}
