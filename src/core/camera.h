#pragma once

#include "core.h"

#include "geometry.h"
#include "film.h"

struct CameraSample
{
	float x, y;
};

struct Pixel
{
	float x, y;
};

class Camera
{
public:
	Camera( void );
	Camera(const Point& eye, const Point& target, const Vector& up, float exposure = 1.f);

	virtual void GenerateRay(const CameraSample& sample, Ray* ray) const = 0;

protected:
	void ComputeUVW();

protected:
	Film* film;
	Point eye, target;
	Vector up;
	Vector u, v, w;
	float exposure;
};