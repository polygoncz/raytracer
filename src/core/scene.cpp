#include "constants.h"
#include "geometry.h"
#include "color.h"
#include "intersection.h"

#include "ligths/ambient.h"
#include "ligths/point.h"

#include "shapes/sphere.h"
#include "shapes/trianglemesh.h"

#include "materials/phong.h"
#include "materials/matte.h"
#include "materials/mirror.h"

#include "integrators/whitted.h"

#include "core/scene.h"

#include "cameras/perspective.h"
#include "import/objimporter.h"

#include "agreggates/bruteforce.h"
#include "agreggates/bvh.h"
#include "agreggates/grid.h"

#include "reference.h"

#include <vector>

#include "import/xmlsceneimporter.h"

using namespace std;

Scene::Scene()
		: background(WHITE), ambient(NULL), film(NULL)
{
}

Scene::~Scene()
{
	for (unsigned long i = 0; i < lights.size(); i++)
	{
		if (lights[i] != NULL)
			delete lights[i];
	}
	lights.clear();

	if (film != NULL) delete film;

	if (ambient != NULL) delete ambient;

	if (cam != NULL) delete cam;

	if (aggregator != NULL) delete aggregator;
}

BBox Scene::Bounds() const
{
	return aggregator->Bounds();
}

bool Scene::Intersect(const Ray& ray, Intersection& inter) const
{
	return aggregator->Intersect(ray, inter);
}

bool Scene::IntersectP(const Ray& ray) const
{
	return aggregator->IntersectP(ray);
}

void Scene::Build(const char* file)
{
	XmlSceneImporter imp(file);
	background = imp.LoadBackground();
	int u = 5;
	ambient = imp.LoadAmbient();
	imp.LoadLights(lights);

	vector<Reference<Primitive> > p;
	imp.LoadModels(p);

	film = imp.LoadFilm();
	cam = imp.LoadCamera(film);

	aggregator = imp.LoadAggregate(p);
}