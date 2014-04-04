#include "core/renderer.h"

class Raytracer: public Renderer
{
public:
	Raytracer(Scene* sc, RenderThread* thr, int perPixelSamples = 1, int numberOfThreads = 1);
	virtual ~Raytracer();

	virtual void Render() const;

	void SetPixelArea(RenderThread* thread);

private:
	void DisplayPixel(int x, int y, RGBColor& in) const;
private:
	Integrator* integrator;
	RenderThread* pixelArea;
	int perPixelSamples;
	int numberOfThreads;
};
