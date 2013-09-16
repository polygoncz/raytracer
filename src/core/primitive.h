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
	Primitive() {}
	virtual ~Primitive() {}

	virtual bool Intersect(const Ray& ray, Intersection& sr) = 0;
	virtual bool IntersectP(const Ray& ray) = 0;
	virtual bool CanIntersect() const = 0;
	virtual void Refine(vector<Reference<GeometricPrimitive> > &refined) = 0;
	virtual BBox Bounds() const = 0;
};

class GeometricPrimitive : public Primitive
{
public:
	GeometricPrimitive(const Reference<Material>& _mat);
	GeometricPrimitive(const GeometricPrimitive& prm);

	virtual ~GeometricPrimitive();

	virtual bool Intersect(const Ray& ray, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual bool CanIntersect() const;
	virtual void Refine(vector<Reference<GeometricPrimitive> > &refined);

	Material* GetMaterial(void) const;
	void SetMaterial(const Reference<Material> &_material);

protected:
	mutable Reference<Material> material;
};

class Agreggate : public Primitive
{
public:
	virtual bool CanIntersect() const { return true; }
	virtual void Refine(vector<Reference<GeometricPrimitive> > &refined)
	{ return; }
};