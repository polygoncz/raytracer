#pragma once

#ifndef GLASS_H
#define GLASS_H

#include "core/material.h"

class Glass : public Material
{
public:
	Glass();
	Glass(const Glass& mat) {};
	virtual ~Glass() {};

	virtual Material* Clone() const;
	virtual BSDF* GetBSDF(const Vector& normal, const Vector& incident) const;

private:
	float ior;
};

#endif // !GLASS_H
