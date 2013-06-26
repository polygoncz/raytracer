#include "specular.h"

Specular::Specular(void)
{}

Specular::Specular(float exp, const RGBColor& ks)
    : exp(exp), ks(ks)
{}

Specular::Specular(const Specular& spec)
    : exp(spec.exp), ks(spec.ks)
{}

Specular::~Specular(void)
{}

BRDF* Specular::clone() const
{
    return new Specular(*this);
}