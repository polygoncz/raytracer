#include "trianglemesh.h"
#include <cstdlib>
#include <cstdint>

TriangleMesh::TriangleMesh(int nf, int nv, int nn, const Vertex *topo, Point *P,
	Normal *N, Reference<Material>& mat)
		: GeometricPrimitive(mat)
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

TriangleMesh::TriangleMesh(int nf, vector<Vertex>& topo, vector<Point>& P, vector<Normal>& N, Reference<Material>& mat)
	: GeometricPrimitive(mat)
{
	nfaces = nf;
	nverts = P.size();
	nnorms = N.size();

	topology = new Vertex[topo.size()];
	for (uint32_t i = 0; i < topo.size(); i++)
	{
		topology[i] = topo[i];
	}

	p = new Point[nverts];
	for (uint32_t i = 0; i < nverts; i++)
	{
		p[i] = P[i];
	}

	n = new Normal[nnorms];
	for (uint32_t i = 0; i < nnorms; i++)
	{
		n[i] = N[i];
	}
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
		: mesh(m), GeometricPrimitive(m->material)
{
	mesh->count++;
	v = &mesh->topology[3 * n];
	STATS_ADD_TRIANGLE();
}

Triangle::~Triangle()
{ }

bool Triangle::Intersect(const Ray& ray, Intersection& sr)
{
	STATS_ADD_RAY_TRIANGLE();

	const Point &p0 = this->mesh->p[v[0].p];
	const Point &p1 = this->mesh->p[v[1].p];
	const Point &p2 = this->mesh->p[v[2].p];

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
		ray.rayEpsilon = 1e-3f * t;
		sr.normal = InterpolateNormal(b1, b2);
		sr.ray = ray;
		sr.t = t;
		sr.hitPoint = ray(t);
		sr.hitObject = true;
		sr.material = GetMaterial();

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

	return Union(BBox(p0, p1), p2);
}