#pragma once

#include "core/material.h"

class Mirror : public Material
{
public:
	Mirror() {};
	Mirror(const Mirror& mat) {};
	virtual ~Mirror() {};

	virtual Material* Clone() const;
	virtual BSDF* GetBSDF() const;
};