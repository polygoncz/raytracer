#include "core/renderer.h"

class Raytracer : public Renderer
{
public:
	Raytracer(Scene* sc, RenderThread* thr);
	virtual ~Raytracer();

	virtual void Render() const;
};