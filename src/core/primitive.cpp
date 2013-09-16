#include "primitive.h"
#include <cstdlib>

GeometricPrimitive::GeometricPrimitive(const Reference<Material>& _mat)
	: material(_mat)
{ }

GeometricPrimitive::GeometricPrimitive(const GeometricPrimitive& prm)
{
	material = prm.material;
}

GeometricPrimitive::~GeometricPrimitive(void)
{
}

Material* GeometricPrimitive::GetMaterial() const
{
	return &material;
}

void GeometricPrimitive::SetMaterial(const Reference<Material>& _material)
{
	material = _material;
}

bool GeometricPrimitive::CanIntersect() const
{
	return true;
}

void GeometricPrimitive::Refine(vector<Reference<GeometricPrimitive> > &refined)
{ }

bool GeometricPrimitive::Intersect(const Ray& ray, Intersection& sr)
{
	return false;
}

bool GeometricPrimitive::IntersectP(const Ray& ray)
{
	return false;
}
