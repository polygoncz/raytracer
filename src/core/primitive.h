#pragma once

#include "geometry.h"
#include "material.h"
#include "intersection.h"

#include <vector>

using namespace std;

class Shape
{
public:
	Shape(void);
	Shape(Material* _mat);
	Shape(const Shape& prm);

	virtual ~Shape();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual bool CanIntersect() const;
	virtual vector<Shape*>* Refine();

	Material* GetMaterial(void) const;
	void SetMaterial(Material* _material);

protected:
	mutable Material* material;
};
