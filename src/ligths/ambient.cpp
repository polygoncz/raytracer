#include "ambient.h"

AmbientLight::AmbientLight(void)
{}

AmbientLight::AmbientLight(const AmbientLight& light)
    : ls(light.ls), c(light.c)
{}

AmbientLight::AmbientLight(double _ls, const RGBColor& _c)
    : ls(_ls), c(_c)
{}

AmbientLight::~AmbientLight(void)
{}