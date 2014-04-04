#include "renderer.h"

Renderer::Renderer(Scene* sc)
		: scene(sc)
{
	cam = scene->cam;
	film = scene->film;
}

Renderer::~Renderer()
{
	if (scene != NULL)
	{
		delete scene;
		scene = NULL;
	}
}