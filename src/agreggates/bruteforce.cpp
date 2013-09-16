#include "agreggates/bruteforce.h"
#include "core/constants.h"

BruteForce::BruteForce(vector<Reference<GeometricPrimitive> > &p)
{
	for (unsigned int i = 0; i < p.size(); i++)
	{
		if (!p[i]->CanIntersect())
			p[i]->Refine(primitives);
		else
			primitives.push_back(p[i]);
	}
}

BruteForce::~BruteForce()
{ }

BBox BruteForce::Bounds() const
{
	BBox b;
	for (unsigned int i = 0; i < primitives.size(); i++)
		Union(b, primitives[i]->Bounds());
	return b;
}

bool BruteForce::Intersect(const Ray& ray, Intersection& sr) const
{
	float tmin = INFINITY;
	float t = 0.f;

	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<GeometricPrimitive> p = primitives[i];
		if (p->Intersect(ray, t, sr) && (t < tmin))
		{
			sr.hitObject = true;
			tmin = t;
			sr.material = p->GetMaterial();
			sr.hitPoint = ray(tmin);
			sr.t = tmin;
		}
	}

	return sr.hitObject;
}

bool BruteForce::IntersectP(const Ray& ray) const
{
	for (unsigned int i = 0; i < primitives.size(); i++)
		if (primitives[i]->IntersectP(ray))
			return true;

	return false;
}