#include "agreggates/bruteforce.h"
#include "core/constants.h"

/**
 * Nad každým tělesem zkusí provést Primitive::Refine() tak,
 * aby bylo možné s každým tělesem provést výpočet průsečíku.
 */
BruteForce::BruteForce(vector<Reference<Primitive> > &p)
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
		Union(b, primitives[i]->Bounds()); //sjednocování BBox
	return b;
}

bool BruteForce::Intersect(const Ray& ray, Intersection& sr)
{
	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<Primitive> p = primitives[i];
		p->Intersect(ray, sr);
	}

	return sr.hitObject;
}

bool BruteForce::IntersectP(const Ray& ray)
{
	for (unsigned int i = 0; i < primitives.size(); i++)
		if (primitives[i]->IntersectP(ray))
			return true;

	return false;
}