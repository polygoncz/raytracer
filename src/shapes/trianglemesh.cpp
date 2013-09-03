#include "trianglemesh.h"
#include <cstdlib>
#include <cstdint>

TriangleMesh::TriangleMesh(int nf, int nv, int nn, const Vertex *topo, Point *P,
	Normal *N, const Reference<Material>& mat)
		: Primitive(mat)
{
	nfaces = nf;
	nverts = nv;
	nnorms = nn;

	topology = new Vertex[3 * nfaces];
	memcpy(topology, topo, 3 * nfaces * sizeof(Vertex));

	p = new Point[nverts];
	memcpy(p, P, nverts * sizeof(Point));

	n = new Normal[nn];
	memcpy(n, N, nn * sizeof(Normal));

	//material = mat;
}

TriangleMesh::~TriangleMesh()
{
	if (topology != NULL) delete[] topology;
	if (p != NULL) delete[] p;
	if (n != NULL) delete[] n;
}

bool TriangleMesh::CanIntersect() const
{
	return false;
}

void TriangleMesh::Refine(vector<Reference<Primitive> > &refined)
{
	for (uint32_t i = 0; i < nfaces; i++)
		refined.push_back(new Triangle(this, i));
}

BBox TriangleMesh::Bounds() const
{
	BBox ret;
	for(int i = 0; i < nverts; i++)
		ret = Union(ret, p[i]);
	return ret;
}

////////////////Triangle////////////////////
Triangle::Triangle(TriangleMesh* m, int n)
		: Primitive(m->material)
{
	mesh = m;
	v = &mesh->topology[3 * n];
	STATS_ADD_TRIANGLE();
}

Triangle::~Triangle()
{
}

bool Triangle::Intersect(const Ray& ray, float& tmin, Intersection& sr)
{
	STATS_ADD_RAY_TRIANGLE();

	const Point &p0 = mesh->p[v[0].p];
	const Point &p1 = mesh->p[v[1].p];
	const Point &p2 = mesh->p[v[2].p];

	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;

	Vector P = Cross(ray.d, e2);
	float det = Dot(e1, P);

	if (det == 0.f) return false;

	float inv_det = 1.f / det;

	Vector T = ray.o - p0;

	float b1 = Dot(T, P) * inv_det;
	if (b1 < 0.f || b1 > 1.f) return false;

	Vector Q = Cross(T, e1);
	float b2 = Dot(ray.d, Q) * inv_det;
	if (b2 < 0.f || b1 + b2 > 1.f) return false;

	float t = Dot(e2, Q) * inv_det;
	if (t > ray.maxt || t < ray.mint) return false;

	if (t < sr.t)
	{
		tmin = t;
		sr.normal = InterpolateNormal(b1, b2);
		ray.rayEpsilon = 1e-3f * t;
		return true;
	}

	return false;
}

bool Triangle::IntersectP(const Ray& ray)
{
	STATS_ADD_RAY_TRIANGLE();

	const Point &p0 = mesh->p[v[0].p];
	const Point &p1 = mesh->p[v[1].p];
	const Point &p2 = mesh->p[v[2].p];

	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;

	Vector P = Cross(ray.d, e2);
	float det = Dot(e1, P);

	if (det == 0.f) return false;

	float inv_det = 1.f / det;

	Vector T = ray.o - p0;

	float b1 = Dot(T, P) * inv_det;
	if (b1 < 0.f || b1 > 1.f) return false;

	Vector Q = Cross(T, e1);
	float b2 = Dot(ray.d, Q) * inv_det;
	if (b2 < 0.f || b1 + b2 > 1.f) return false;

	float t = Dot(e2, Q) * inv_det;
	if (t > ray.rayEpsilon) return true;

	return false;
}

Normal Triangle::InterpolateNormal(float beta, float gamma)
{
	Normal n((1.f - beta - gamma) * mesh->n[v[0].n] + beta * mesh->n[v[1].n]
					+ gamma * mesh->n[v[2].n]);
	n.Normalize();
	return n;
}

BBox Triangle::Bounds() const
{
	const Point &p0 = mesh->p[v[0].p];
	const Point &p1 = mesh->p[v[1].p];
	const Point &p2 = mesh->p[v[2].p];

	BBox b(p0, p1);
	return Union(b, p2);
}
