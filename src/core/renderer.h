#pragma once

#include "color.h"
#include "wxgui/imagebuffer.h"
#include "film.h"
#include "camera.h"
#include "scene.h"
#include "integrator.h"

class Renderer
{
public:
	Renderer(Scene* sc, RenderThread* thread);
	virtual ~Renderer();

	virtual void Render() const = 0;
	void SetPixelArea(RenderThread* thread);

protected:
	void DisplayPixel(int x, int y, RGBColor& in) const;

	Scene* scene;
	RenderThread* pixelArea;
	Integrator* integrator;
	Film* film;
	Camera* cam;
};
