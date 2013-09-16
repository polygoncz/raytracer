#pragma once

#include "core.h"
#include "wxgui/imagebuffer.h"
#include <vector>

#include "light.h"
#include "color.h"
#include "integrator.h"
#include "film.h"
#include "camera.h"
#include "intersection.h"
#include "reference.h"
#include "primitive.h"
#include "agreggate.h"

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void Build();
	void Render();
	bool Intersect(const Ray& ray, Intersection& inter) const;
	bool IntersectP(const Ray& ray) const;
	BBox Bounds() const;

private:
	void AddObject(GeometricPrimitive* obj);
	void AddLight(Light* light);

public:
	RGBColor background;
	Light* ambient;
	vector<Light*> lights;
	vector<Reference<GeometricPrimitive> > objects;
	Film* film;
	Camera* cam;
	Agreggate* agr;
};
