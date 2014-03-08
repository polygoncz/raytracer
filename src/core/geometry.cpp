#include "geometry.h"

#include <cstdint>

BBox Union(const BBox& b, const Point& p)
{
	BBox ret = b;
    ret.pMin.x = Min(b.pMin.x, p.x);
    ret.pMin.y = Min(b.pMin.y, p.y);
    ret.pMin.z = Min(b.pMin.z, p.z);
    ret.pMax.x = Max(b.pMax.x, p.x);
    ret.pMax.y = Max(b.pMax.y, p.y);
    ret.pMax.z = Max(b.pMax.z, p.z);
    return ret;
}

BBox Union(const BBox& b, const BBox& b2)
{
	BBox ret;
	ret.pMin.x = Min(b.pMin.x, b2.pMin.x);
	ret.pMin.y = Min(b.pMin.y, b2.pMin.y);
	ret.pMin.z = Min(b.pMin.z, b2.pMin.z);
	ret.pMax.x = Max(b.pMax.x, b2.pMax.x);
	ret.pMax.y = Max(b.pMax.y, b2.pMax.y);
	ret.pMax.z = Max(b.pMax.z, b2.pMax.z);
	return ret;
}

bool BBox::IntersectP(const Ray& ray, float* hitt0, float* hitt1) const
{
	
	float t0 = ray.mint, t1 = ray.maxt;
	for (int axis = 0; axis < 3; ++axis)
	{
		float invRayDir = 1.f / ray.d[axis];
		float tNear = (pMin[axis] - ray.o[axis]) * invRayDir;
		float tFar = (pMax[axis] - ray.o[axis]) * invRayDir;

		if (tNear > tFar) Swap(tNear, tFar);
		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar < t1 ? tFar : t1;
		if (t0 > t1) return false;
	}

	if (hitt0) *hitt0 = t0;
	if (hitt1) *hitt1 = t1;

	return true;
}
