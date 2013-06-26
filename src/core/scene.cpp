#include "constants.h"
#include "geometry.h"
#include "color.h"

#include "ligths/ambient.h"
#include "ligths/point.h"

#include "shapes/sphere.h"
#include "materials/phong.h"

#include "integrators/whitted.h"

#include "core/scene.h"

Scene::Scene()
    :   background(BLACK),
        ambient(NULL),
        pixelArea(NULL),
        tracer(NULL),
        vp(NULL)
{}

Scene::Scene(RenderThread* pixelArea)
    :   background(BLACK),
        ambient(NULL),
        pixelArea(pixelArea),
        tracer(NULL),
        vp(NULL)
{}

Scene::~Scene()
{
    for (unsigned long i = 0; i < lights.size(); i++)
    {
        delete lights[i];
    }
    lights.clear();

    for (unsigned long i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    objects.clear();

    if (tracer != NULL)
        delete tracer;

    if (vp != NULL)
        delete vp;

    if (ambient != NULL)
        delete ambient;
}

void Scene::displayPixel(int x, int y, RGBColor& in)
{
    RGBColor color = in.Clamp();

    pixelArea->setPixel(x, y, (int) (color.r * 255),
                              (int) (color.g * 255),
                              (int) (color.b * 255));
}

void Scene::addLight(Light* light)
{
    lights.push_back(light);
}

void Scene::addObject(Primitive* obj)
{
    objects.push_back(obj);
}

void Scene::build()
{
    vp = new Film(800, 800, 0.125);

    background = BLACK;
    
    ambient = new AmbientLight(0.3, RGBColor(1.0, 1.0, 1.0));

    Light* main = new PointLight(5.0, RGBColor(1.f, 1.f, 1.f), Point(50.f, -70.f, 80.f));
    Light* bottom = new PointLight(1.0, RGBColor(0.f, 0.f, 1.f), Point(0.f, 80.f, 100.f));
    Light* back = new PointLight(0.8, RGBColor(1.f, 0.f, 0.f), Point(-80.f, -80.f, 100.f));

    addLight(main);
    addLight(bottom);
    addLight(back);

    Primitive* sphere1 = new Sphere(Point(0.f, 0.f, 0.f), 40.f, new Phong(RGBColor(0.05f, 0.9f, 0.05f), RGBColor(1.f,1.f,1.f), 0.1f, 0.7f, 1000.f));
    Primitive* sphere2 = new Sphere(Point(-30.f, 20.f, 40.f), 25.f, new Phong(RGBColor(0.8f, 0.0f, 0.8f), RGBColor(1.f,1.f,1.f), 0.1f, 0.7f, 500.f));

    addObject(sphere1);
    addObject(sphere2);

    tracer = new WhittedTracer(this);
}

void Scene::render()
{
    Ray ray;
    double zw = 100.0;
    RGBColor color;

    ray.d = Vector(0, 0, -1);

    for (int r = 0; r < vp->height; r++)
    {
        for (int c = 0; c < vp->width; c++)
        {
            double x = vp->size * (c - 0.5 * (vp->width - 1.0));
            double y = vp->size * (r - 0.5 * (vp->height - 1.0));
            ray.o = Point(x, y, zw);
            color = tracer->traceRay(ray);

            displayPixel(c, r, color);
        }
    }
}