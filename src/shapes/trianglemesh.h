#pragma once

#include "core/core.h"
#include "core/primitive.h"
#include "core/statistics.h"

struct Vertex
{
	int p; //Index of point
	int n; //Index of normal
};

class TriangleMesh: public Shape
{
public:
	TriangleMesh(int nf, int nv, int nn, const Vertex *topo, Point *P,
		Normal *N, const Reference<Material>& mat);
	virtual ~TriangleMesh();
	bool CanIntersect() const;
	virtual BBox Bounds() const;
	virtual vector<Shape*>* Refine();
	friend class Triangle;
public:
	int nfaces, nverts, nnorms;
	Vertex *topology;
	Point *p;
	Normal *n;
private:
	vector<Shape*>* refined;
};

class Triangle: public Shape
{
public:
	Triangle(TriangleMesh* m, int n);
	virtual ~Triangle();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;
private:
	Normal InterpolateNormal(const float beta, const float gamma);
private:
	TriangleMesh *mesh;
	Vertex *v;
};
