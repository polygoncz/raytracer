#pragma once

#include "core/core.h"
#include "core/primitive.h"

#include <memory>

class TriangleMesh : public Shape
{
public:
	TriangleMesh(int nf, int nv, const int *topo, Point *P, Material* mat);
	virtual ~TriangleMesh();
	bool CanIntersect() const;
	virtual vector<Shape*>* Refine();
public:
	int nfaces, nverts;
	int *topology;
	Point *p;
	Normal *n;
private:
	vector<Shape*>* refined;
};

class Triangle : public Shape
{
public:
	Triangle(TriangleMesh* m, int n);
	virtual ~Triangle();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr) const;
	virtual bool IntersectP(const Ray& ray) const;
private:
	TriangleMesh *mesh;
	int *v;
};