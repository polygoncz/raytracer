#include "core/renderer.h"

class Raytracer: public Renderer
{
public:
	Raytracer(Scene* sc, RenderThread* thr, int perPixelSamples = 1, int numberOfThreads = 1);
	virtual ~Raytracer();

	virtual void Render() const;
private:
	int perPixelSamples;
	int numberOfThreads;
};
