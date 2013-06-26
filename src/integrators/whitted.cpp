#include "whitted.h"
#include "core/geometry.h"

#include "core/constants.h"

using namespace std;

WhittedTracer::WhittedTracer(Scene* scene)
    : Integrator(), scene(scene)
{}

WhittedTracer::WhittedTracer(const WhittedTracer& tr)
    : Integrator(tr), scene(tr.scene)
{}

WhittedTracer::~WhittedTracer(void)
{}

RGBColor WhittedTracer::traceRay(const Ray& ray) const
{
    Intersection sr(*scene);
    float tMin = INFINITY;
    float t = 0.f;

    for (vector<Primitive*>::iterator itr = scene->objects.begin(); itr != scene->objects.end(); itr++)
    {
        Primitive* obj = (*itr);
        if (obj->hit(ray, t, sr) && (t < tMin))
        {
            sr.hitObject = true;
            tMin = t;
            sr.material = obj->getMaterial();
            sr.hitPoint = ray(t);
        }
    }

    if (sr.hitObject)
    {
        sr.ray = ray;
        return sr.material->shade(sr);
    }

    return scene->background;
}
