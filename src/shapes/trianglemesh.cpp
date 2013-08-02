#include "trianglemesh.h"

#include <cstring>

TriangleMesh::TriangleMesh(int nf, int nv, const int *topo, Point *P, Material* mat)
	: Shape(mat)
{
	nfaces = nf;
	nverts = nv;

	topology = new int[3 * nfaces];
	memcpy(topology, topo, 3 * nfaces * sizeof(int));

	p = new Point[nverts];
	memcpy(p, P, nverts * sizeof(Point));

	refined = NULL;
}

TriangleMesh::~TriangleMesh()
{
	if (refined != NULL)
	{
		for (unsigned i = 0; i < refined->size(); i++)
		{
			delete (*refined)[i];
		}
		refined->clear();
		delete refined;
	}

	if (topology != NULL)
		delete[] topology;
	if (p != NULL)
		delete[] p;
	//delete[] n;
}

bool TriangleMesh::CanIntersect() const
{
	return false;
}

vector<Shape*>* TriangleMesh::Refine()
{
	if (refined == NULL)
	{
		refined = new vector<Shape*>;
		for (int i = 0; i < nfaces; i++)
		{
			refined->push_back(new Triangle(this, i));
		}
	}

	return refined;
}

////////////////Triangle////////////////////
Triangle::Triangle(TriangleMesh* m, int n)
	: Shape(NULL)
{
	mesh = m;
	v = &mesh->topology[3*n];
}

Triangle::~Triangle() {}

bool Triangle::Intersect(const Ray& ray, float& tmin, Intersection& sr) const
{
	const Point &p0 = mesh->p[v[0]];
	const Point &p1 = mesh->p[v[1]];
	const Point &p2 = mesh->p[v[2]];

	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;

	Vector P = Cross(ray.d, e2);
	float det = Dot(e1, P);

	if (det > -EPSILON && det < EPSILON) return false;

	float inv_det = 1.f / det;

	Vector T = ray.o - p0;

	float b1 = Dot(T, P) * inv_det;
	if (b1 < 0.f || b1 > 1.f) return false;

	Vector Q = Cross(T, e1);
	float b2 = Dot(ray.d, Q) * inv_det;
	if (b2 < 0.f || b1 + b2 > 1.f) return false;

	float t = Dot(e2, Q) * inv_det;
	if (t > EPSILON && t < sr.t)
	{
		tmin = t;
		sr.normal = Cross(e1, e2).Normalize();
		return true;
	}

	return false;
} 

bool Triangle::IntersectP(const Ray& ray) const
{
	const Point &p0 = mesh->p[v[0]];
	const Point &p1 = mesh->p[v[1]];
	const Point &p2 = mesh->p[v[2]];

	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;

	Vector P = Cross(ray.d, e2);
	float det = Dot(e1, P);

	if (det > -EPSILON && det < EPSILON) return false;

	float inv_det = 1.f / det;

	Vector T = ray.o - p0;

	float b1 = Dot(T, P) * inv_det;
	if (b1 < 0.f || b1 > 1.f) return false;

	Vector Q = Cross(T, e1);
	float b2 = Dot(ray.d, Q) * inv_det;
	if (b2 < 0.f || b1 + b2 > 1.f) return false;

	float t = Dot(e2, Q) * inv_det;
	if (t > EPSILON)
		return true;

	return false;
}