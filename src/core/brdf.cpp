#include "core/brdf.h"

BxDF::BxDF(BxDFType t)
	: type(t)
{}

BxDF::BxDF(const BxDF& brdf)
	: type(brdf.type)
{}

BxDF::~BxDF()
{}