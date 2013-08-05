#include "camera.h"

Camera::Camera(void)
{
}

Camera::Camera(const Point& eye, const Point& target, const Vector& up,
	float exposure /* = 1.f */)
		: eye(eye), target(target), up(up), exposure(exposure)
{
	ComputeUVW();
}

void Camera::ComputeUVW()
{
	w = eye - target;
	w.Normalize();
	u = Cross(up, w);
	u.Normalize();
	v = Cross(u, w);
	v.Normalize();
}
