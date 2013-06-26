#include "perspective.h"

PerspectiveCamera::PerspectiveCamera( void )
	: Camera() {}

PerspectiveCamera::PerspectiveCamera(const Point& eye, const Point& target, const Vector& up, Film* film, float d, float exposure /* = 1.f */)
	: Camera(eye, target, up, exposure), d(d)
{
	this->film = film;
}

void PerspectiveCamera::GenerateRay(const CameraSample& sample, Ray* ray) const
{
	Pixel p;

	p.x = film->size * (sample.x - 0.5f * (film->width - 1.f));
	p.y = film->size * (sample.y - 0.5f * (film->height - 1.f));

	Vector dir = p.x * u + p.y * v - d * w;
	dir.Normalize();
	
	ray->o = eye;
	ray->d = dir;

	return;
}