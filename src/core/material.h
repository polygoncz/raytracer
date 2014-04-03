#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H


#include "core/color.h"
#include "core/core.h"
#include "core/intersection.h"
#include "core/reference.h"
#include "core/brdf.h"

#include <cstdint>

#define MAX_BXDFS 8

class RGBColor;
class Intersection;

class BSDF
{
public:
	BSDF(void);
	~BSDF(void);
	void Add(BxDF* bxdf);
	uint32_t NumComponents() const;
	BxDF* operator[] (int i) const;

private:
	BxDF *bxdfs[MAX_BXDFS];
	uint32_t nBxDFs;
};

class Material : public ReferenceCounted
{
public:
	Material(void);
	Material(const Material& material);
	virtual ~Material(void);

	virtual BSDF* GetBSDF(const Vector& normal, const Vector& incident) const = 0;
};

float SchlickReflectance(const Vector& normal, const Vector& incident, float n1, float n2);
float FresnelReflectance(const Vector& normal, const Vector& incident, float n1, float n2);

#endif