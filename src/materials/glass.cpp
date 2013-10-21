#include "glass.h"

Glass::Glass()
	: ior(1.333f)
{ }

Material* Glass::Clone() const
{
	return new Glass(*this);
}

RGBColor Glass::Ambient(const Intersection& inter, const Vector& wi, const RGBColor& li) const
{
	return BLACK;
}

RGBColor Glass::L(const Intersection& inter, const Vector& wi, const RGBColor& li) const
{
	return BLACK;
}