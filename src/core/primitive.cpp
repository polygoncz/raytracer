#include "primitive.h"
#include <cstdlib>

Primitive::Primitive(const Reference<Material>& _mat)
	: material(_mat)
{ }

Primitive::Primitive(const Primitive& prm)
{
	material = prm.material;
}

Primitive::~Primitive(void)
{
}

Material* Primitive::GetMaterial() const
{
	return &material;
}

void Primitive::SetMaterial(const Reference<Material>& _material)
{
	material = _material;
}

bool Primitive::CanIntersect() const
{
	return true;
}

vector<Primitive*>* Primitive::Refine()
{
	return NULL;
}

bool Primitive::Intersect(const Ray& ray, float& tmin, Intersection& sr)
{
	return false;
}

bool Primitive::IntersectP(const Ray& ray)
{
	return false;
}
