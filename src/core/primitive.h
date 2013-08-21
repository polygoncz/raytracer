#pragma once

#include "geometry.h"
#include "material.h"
#include "intersection.h"
#include "reference.h"

#include <vector>

using namespace std;

class Shape
{
public:
	Shape(const Reference<Material>& _mat);
	Shape(const Shape& prm);

	virtual ~Shape();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual bool CanIntersect() const;
	virtual vector<Shape*>* Refine();
	virtual BBox Bounds() const = 0;

	Material* GetMaterial(void) const;
	void SetMaterial(const Reference<Material> &_material);

protected:
	mutable Reference<Material> material;
};
