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

using namespace std;

class Scene
{
public:
	Scene();
	Scene(RenderThread* pixelArea);
	~Scene();

	void Build();
	void Render();
	bool Intersect(const Ray& ray, Intersection& inter) const;
	bool IntersectP(const Ray& ray) const;

private:
	void AddObject(Shape* obj);
	void AddLight(Light* light);
	void DisplayPixel(int x, int y, RGBColor& color);

public:
	RGBColor background;
	Light* ambient;
	vector<Light*> lights;
	vector<Shape*> objects;
	RenderThread* pixelArea;
	Film* film;
	Camera* cam;
	Integrator* tracer;
};
