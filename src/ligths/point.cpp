#include "point.h"

PointLight::PointLight(void)
{
}

PointLight::PointLight(const PointLight& light)
		: location(light.location), ls(light.ls), c(light.c)
{
}

PointLight::PointLight(double _ls, const RGBColor& _c, const Point& _loc)
		: ls(_ls), c(_c), location(_loc)
{
}

PointLight::~PointLight(void)
{
}
