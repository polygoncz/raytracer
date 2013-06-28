#include "constants.h"
#include "geometry.h"
#include "color.h"
#include "intersection.h"

#include "ligths/ambient.h"
#include "ligths/point.h"

#include "shapes/sphere.h"
#include "shapes/plane.h"

#include "materials/phong.h"
#include "materials/matte.h"

#include "integrators/whitted.h"

#include "core/scene.h"

#include "cameras/perspective.h"

#include <vector>

using namespace std;

Scene::Scene()
    :   background(BLACK),
        ambient(NULL),
        pixelArea(NULL),
        tracer(NULL),
        film(NULL)
{}

Scene::Scene(RenderThread* pixelArea)
    :   background(BLACK),
        ambient(NULL),
        pixelArea(pixelArea),
        tracer(NULL),
        film(NULL)
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

    if (film != NULL)
        delete film;

    if (ambient != NULL)
        delete ambient;

	if (cam != NULL)
		delete cam;
}

void Scene::DisplayPixel(int x, int y, RGBColor& in)
{
    RGBColor color = in.Clamp();

    pixelArea->setPixel(x, y, (int) (color.r * 255),
                              (int) (color.g * 255),
                              (int) (color.b * 255));
}

void Scene::AddLight(Light* light)
{
    lights.push_back(light);
}

void Scene::AddObject(Primitive* obj)
{
    objects.push_back(obj);
}

bool Scene::Intersect(const Ray& ray, Intersection& inter) const
{
	float tMin = INFINITY;
	float t = 0.f;

	for (vector<Primitive*>::const_iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		Primitive* obj = (*itr);
		if (obj->Hit(ray, t, inter) && (t < tMin))
		{
			inter.hitObject = true;
			tMin = t;
			inter.material = obj->GetMaterial();
			inter.hitPoint = ray(tMin);
			inter.t = tMin;
		}
	}

	return inter.hitObject;
}

bool Scene::IntersectP(const Ray& ray) const
{
	Intersection inter;
	float tMin = INFINITY;
	float t = 0.f;

	for (vector<Primitive*>::const_iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		Primitive* obj = (*itr);
		if (obj->Hit(ray, t, inter))
		{
			return true;
		}
	}

	return false;
}

void Scene::Build()
{
    film = new Film(800, 800, 0.125);

    background = DARK_GREY;
    
    ambient = new AmbientLight(0.3, WHITE);

    Light* main = new PointLight(5.0, WHITE, Point(50.f, 50.f, 50.f));

    AddLight(main);

    Primitive* sphere1 = new Sphere(Point(0.f, 0.f, 0.f), 40.f, new Phong(RGBColor(0.05f, 0.9f, 0.05f), RGBColor(1.f,1.f,1.f), 0.1f, 0.7f, 1000.f));
    Primitive* sphere2 = new Sphere(Point(40.f, 0.f, 20.f), 25.f, new Matte(GREY, 0.1f, 0.7f));
	Primitive* plane = new Plane(Point(0.f, 0.f, 0.f), Normal(0.f, 1.f, 0.f), new Matte(GREY, 0.1f, 0.7f));

	AddObject(plane);
	AddObject(sphere1);
    AddObject(sphere2);

	cam = new PerspectiveCamera(Point(200.f, 45.f, -100.f), Point(20.f, 15.f, 0.f), Vector(0.f, 1.f, 0.f), film, 200.f);

    tracer = new WhittedTracer(this);
}