#include "primitive.h"

Primitive::Primitive( void )
	: material(NULL) { }

Primitive::Primitive(Material* _mat)
	: material(_mat) { }

Primitive::Primitive(const Primitive& prm)
{
	if (prm.material != NULL)
		material = prm.material->clone();
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

Material* Primitive::getMaterial() const
{
	return material;
}

void Primitive::setMaterial(Material* _material)
{
	if (material != NULL)
		delete material;

	material = _material;
}