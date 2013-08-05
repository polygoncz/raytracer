#include "primitive.h"

Shape::Shape(void)
		: material(NULL)
{
}

Shape::Shape(Material* _mat)
		: material(_mat)
{
}

Shape::Shape(const Shape& prm)
{
	if (prm.material != NULL) material = prm.material->Clone();
	else material = NULL;
}

Shape::~Shape(void)
{

	if (material != NULL)
	{
		delete material;
		material = NULL;
	}
}

Material* Shape::GetMaterial() const
{
	return material;
}

void Shape::SetMaterial(Material* _material)
{
	if (material != NULL) delete material;

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
