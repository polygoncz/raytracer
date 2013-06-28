#include "lambert.h"

Lambert::Lambert(void)
{}

Lambert::Lambert(const Lambert& mat)
    : kd(mat.kd), cd(mat.cd)
{}

Lambert::Lambert(float _kd, const RGBColor& _cd)
    : kd(_kd), cd(_cd)
{}

Lambert::~Lambert(void)
{}

BRDF* Lambert::Clone() const
{
    return new Lambert(*this);
}