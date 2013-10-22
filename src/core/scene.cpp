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

using namespace std;

Scene::Scene()
		: background(WHITE), ambient(NULL), film(NULL)
{
}

Scene::~Scene()
{
	for (unsigned long i = 0; i < lights.size(); i++)
	{
		delete lights[i];
	}
	lights.clear();

	if (film != NULL) delete film;

	if (ambient != NULL) delete ambient;

	if (cam != NULL) delete cam;

	if (agr != NULL) delete agr;
}

BBox Scene::Bounds() const
{
	BBox b;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		Reference<GeometricPrimitive> p = objects[i];
		b = Union(b, p->Bounds());
	}
	return b;
}

void Scene::AddLight(Light* light)
{
	lights.push_back(light);
}

void Scene::AddObject(GeometricPrimitive* obj)
{
	objects.push_back(obj);
}

bool Scene::Intersect(const Ray& ray, Intersection& inter) const
{
	return agr->Intersect(ray, inter);
}

bool Scene::IntersectP(const Ray& ray) const
{
	return agr->IntersectP(ray);
}

/* SCENA 01
 void Scene::Build()
 {
 film = new Film(800, 800, 0.125);

 ambient = new AmbientLight(0.3, WHITE);

 Light* main = new PointLight(5.0, WHITE, Point(50.f, 50.f, 50.f));
 Light* back = new PointLight(1.2, WHITE, Point(200.f, 45.f, -100.f));

 AddLight(main);
 AddLight(back);

 Primitive* sphere1 = new Sphere(Point(0.f, 0.f, 0.f), 40.f, new Phong(RGBColor(0.05f, 0.9f, 0.05f), RGBColor(0.7f, 0.7f, 0.7f), 0.1f, 0.7f, 100.f));
 Primitive* sphere2 = new Sphere(Point(40.f, 25.f, 20.f), 10.f, new Matte(RED, 0.1f, 0.7f));
 Primitive* sphere3 = new Sphere(Point(9.f, 5.f, -35.f), 20.f, new Matte(BLUE, 0.1f, 0.7f));
 Primitive* plane = new Plane(Point(0.f, 0.f, 0.f), Normal(0.f, 1.f, 0.f), new Matte(GREY, 0.1f, 0.7f));

 AddObject(sphere1);
 AddObject(sphere2);
 AddObject(sphere3);
 AddObject(plane);

 cam = new PerspectiveCamera(Point(200.f, 45.f, -100.f), Point(0.f, 7.f, -20.f), Vector(0.f, 1.f, 0.f), film, 220.f);

 tracer = new WhittedTracer(this);
 }*/

/*//Triangle
 void Scene::Build()
 {
 film = new Film(800, 800, 0.125);

 ambient = new AmbientLight(0.3, WHITE);

 Light* main = new PointLight(1.0, WHITE, Point(0.f, 1.f, 0.f));
 Light* back = new PointLight(0.2, WHITE, Point(200.f, 45.f, -100.f));

 AddLight(main);
 AddLight(back);

 
 Primitive* t1 = new Triangle(Point(1.f, 0.f, 1.f), Point(1.f, 0.f, -1.f), Point(-1.f, 0.f, 0.f), new Matte(RED, 0.1f, 1.f));
 //Primitive* sphere = new Sphere(Point(0,0,0), 0.5f, new Matte(BLUE, 0.1, 1.f));
 //Primitive* plane = new Plane(Point(0.f, 0.f, 0.f), Normal(0.f, 1.f, 0.f), new Matte(GREY, 0.1f, 0.7f));

 
 //AddObject(plane);
 AddObject(t1);
 //AddObject(sphere);

 cam = new PerspectiveCamera(Point(1.f, 10.f, 1.f), Point(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f), film, 220.f);

 tracer = new WhittedTracer(this);
 }*/

/*//SCENA JEDNA
 void Scene::Build()
 {
 film = new Film(800, 800, 0.125);

 ambient = new AmbientLight(0.6, WHITE);

 Light* main = new PointLight(4.0, WHITE, Point(-10.f, 7.5f, 10.f));
 Light* back = new PointLight(0.7, RED, Point(10.f, 10.f, -10.f));

 AddLight(main);
 AddLight(back);

 Point *v = new Point[8];

 v[0] = Point(1.f, -1.f, -1.f);
 v[1] = Point(1.f, -1.f, 1.f);
 v[2] = Point(-1.f, -1.f, 1.f);
 v[3] = Point(-1.f, -1.f, -1.f);
 v[4] = Point(-0.182651f, 0.940792f, -1.f);
 v[5] = Point(-0.182652f, 0.940792f, 1.f);
 v[6] = Point(-1.f, 0.940792f, 1.f);
 v[7] = Point(-1.f, 0.940792f, -1.f);

 int topology[36];

 topology[0] = 0; topology[1] = 1; topology[2] = 3;
 topology[3] = 4; topology[4] = 7; topology[5] = 5;
 topology[6] = 0; topology[7] = 4; topology[8] = 1;
 topology[9] = 1; topology[10] = 5; topology[11] = 6;
 topology[12] = 2; topology[13] = 6; topology[14] = 3;
 topology[15] = 4; topology[16] = 0; topology[17] = 7;
 topology[18] = 1; topology[19] = 2; topology[20] = 3;
 topology[21] = 7; topology[22] = 6; topology[23] = 5;
 topology[24] = 4; topology[25] = 5; topology[26] = 1;
 topology[27] = 2; topology[28] = 1; topology[29] = 6;
 topology[30] = 6; topology[31] = 7; topology[32] = 3;
 topology[33] = 0; topology[34] = 3; topology[35] = 7;

 Shape* mesh = new TriangleMesh(12, 8, topology, v, new Phong(RED, RGBColor(0.7f, 0.7f, 0.7f), 0.1f, 0.7f, 100.f));
 

 Shape* plane = new Plane(Point(0.f, -1.0f, 0.f), Normal(0.f, 1.f, 0.f), new Matte(GREY, 0.1f, 0.7f));
 AddObject(plane);

 Shape* sphere = new Sphere(Point(0.f, 0 , 2.f), 0.5f, new Phong(RGBColor(0.05f, 0.9f, 0.05f), RGBColor(0.7f, 0.7f, 0.7f), 0.1f, 0.7f, 100.f));
 AddObject(sphere);
 AddObject(mesh);

 cam = new PerspectiveCamera(Point(10.f, 6.5f, 10.f), Point(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f), film, 220.f);

 tracer = new WhittedTracer(this);
 }*/

void Scene::Build()
{
	film = new Film(800, 800, 0.008f);

	ambient = new AmbientLight(1.f, WHITE);

	Light* main = new PointLight(4.0, WHITE, Point(-10.f, 7.5f, 10.f));
	//Light* back = new PointLight(0.7, RED, Point(10.f, 10.f, -10.f));

	AddLight(main);
	//AddLight(back);

	vector<Reference<Primitive> > p;

	ObjImporter imp;
	Reference<Primitive> mesh = imp.LoadObj("C:/Users/Pavel Lokvenc/Documents/demon.obj", new Phong(GREEN, WHITE, 0.2, 0.8, 1000.f));

	mesh->Refine(p);

	cam = new PerspectiveCamera(Point(20.f, 4.f, 27.f), Point(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f), film, 50.f);

	agr = new Grid(p);
}

/*void Scene::Build()
 {
	 film = new Film(800, 800, 0.008f);

	 ambient = new AmbientLight(1.f, WHITE);

	 Light* main = new PointLight(4.0, WHITE, Point(-10.f, 7.5f, 10.f));
	 AddLight(main);

	 vector<Reference<Primitive> > p;
	 Reference<Material> mirror1(new Phong(RGBColor(0.05f, 0.9f, 0.05f), RGBColor(0.7f, 0.7f, 0.7f), 0.1f, 0.7f, 100.f));
	 Reference<Material> mirror2(new Phong(RGBColor(0.0f, 0.8f, 0.5f), RGBColor(0.7f, 0.7f, 0.7f), 0.1f, 0.7f, 100.f));

	 Reference<Primitive> sphere1(new Sphere(Point(-1.f, -1.f, -1.f), 1.f, mirror1));
	 p.push_back(sphere1);

	 Reference<Primitive> sphere2(new Sphere(Point(-1.f, 1.f, -1.f), 1.f, mirror2));
	 p.push_back(sphere2);
	 
	 cam = new PerspectiveCamera(Point(15.f, 6.5f, 15.f), Point(0.f, 0.f, 0.f),
		 Vector(0.f, 1.f, 0.f), film, 50.f);

	 agr = new Grid(p);
 }*/

 /*void Scene::Build()
 {
	 film = new Film(800, 800, 0.008f);

	 ambient = new AmbientLight(1.f, WHITE);

	 Light* main = new PointLight(4.0, WHITE, Point(0.f, 1.95f, 0.f));
	 AddLight(main);

	 vector<Reference<Primitive> > p;

	 ObjImporter imp;

	 Reference<Primitive> sphere = imp.LoadObj("D:/_scenes/cornell/koule.obj");
	 p.push_back(sphere);

	 Reference<Primitive> box = imp.LoadObj("D:/_scenes/cornell/krychle.obj");
	 p.push_back(box);

	 Reference<Primitive> bottom = imp.LoadObj("D:/_scenes/cornell/stena_bottom.obj");
	 p.push_back(bottom);

	 Reference<Primitive> back = imp.LoadObj("D:/_scenes/cornell/stena_back.obj");
	 p.push_back(back);

	 Reference<Primitive> top = imp.LoadObj("D:/_scenes/cornell/stena_top.obj");
	 p.push_back(top);

	 Reference<Primitive> left = imp.LoadObj("D:/_scenes/cornell/stena_left.obj");
	 p.push_back(left);

	 Reference<Primitive> right = imp.LoadObj("D:/_scenes/cornell/stena_right.obj");
	 p.push_back(right);

	 cam = new PerspectiveCamera(Point(30.f, 2.f, 0.f), Point(10.f, 2.f, 0.f),
		 Vector(0.f, 1.f, 0.f), film, 50.f);

	 agr = new Grid(p);
 }*/