#include "primitive.h"
Shape::Shape(cosnt Reference<Material>& _mat)
{
	material = _mat;
}

Shape::Shape(const Shape& prm)
{
	material = prm.material;
}

Shape::~Shape(void)
{
}

Material* Shape::GetMaterial() const
{
	return material.ptr;
}

void Shape::SetMaterial(const Reference<Material>& _material)
{
	material = _material;
}

bool Shape::CanIntersect() const
{
	return true;
}

vector<Shape*>* Shape::Refine()
{
	return NULL;
}

bool Shape::Intersect(const Ray& ray, float& tmin, Intersection& sr)
{
	return false;
}

bool Shape::IntersectP(const Ray& ray)
{
	return false;
}
