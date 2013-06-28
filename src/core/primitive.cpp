#include "primitive.h"

Primitive::Primitive( void )
	: material(NULL) { }

Primitive::Primitive(Material* _mat)
	: material(_mat) { }

Primitive::Primitive(const Primitive& prm)
{
	if (prm.material != NULL)
		material = prm.material->Clone();
	else material = NULL;
}

Primitive::~Primitive( void )
{
	if (material != NULL)
	{
		delete material;
		material = NULL;
	}
}

Material* Primitive::GetMaterial() const
{
	return material;
}

void Primitive::SetMaterial(Material* _material)
{
	if (material != NULL)
		delete material;

	material = _material;
}