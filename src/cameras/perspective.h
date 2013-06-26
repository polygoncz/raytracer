#pragma once

#include "core/core.h"
#include "core/geometry.h"
#include "core/camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera( void );
	PerspectiveCamera(const Point& eye, const Point& target, const Vector& up, Film* film, float d, float exposure = 1.f);

	virtual void GenerateRay(const CameraSample& sample, Ray* ray) const;
private:
	float d;
};