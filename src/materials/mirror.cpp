#include "materials/mirror.h"

Material* Mirror::Clone() const
{
	return new Mirror(*this);
}

RGBColor Mirror::Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const
{
	return BLACK;
}

RGBColor Mirror::L(const Intersection& inter, const Vector& wi, const RGBColor& li) const
{
	return BLACK;
}