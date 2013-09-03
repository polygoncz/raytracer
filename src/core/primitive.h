#pragma once

#include "geometry.h"
#include "material.h"
#include "intersection.h"
#include "reference.h"

#include <vector>

using namespace std;

class Primitive : public ReferenceCounted
{
public:
	Primitive(const Reference<Material>& _mat);
	Primitive(const Primitive& prm);

	virtual ~Primitive();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual bool CanIntersect() const;
	virtual void Refine(vector<Reference<Primitive> > &refined);
	virtual BBox Bounds() const = 0;

	Material* GetMaterial(void) const;
	void SetMaterial(const Reference<Material> &_material);

protected:
	mutable Reference<Material> material;
};
