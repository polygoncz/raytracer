#include "bvh.h"

#include <cstdint>

static inline bool IntersectP(const BBox &bounds, const Ray &ray)
{
	float t0 = ray.mint, t1 = ray.maxt;
	for (int i = 0; i < 3; ++i) {
		float invRayDir = 1.f / ray.d[i];
		float tNear = (bounds.pMin[i] - ray.o[i]) * invRayDir;
		float tFar = (bounds.pMax[i] - ray.o[i]) * invRayDir;

		if (tNear > tFar) Swap(tNear, tFar);
		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar < t1 ? tFar : t1;
		if (t0 > t1) return false;
	}
	return true;
}

BVH::BVH(vector<Reference<Primitive> > &prims)
{
	if (prims.size() == 1)
	{
		*this = BVH(prims[0], prims[0]);
		return;
	}
	if (prims.size() == 2)
	{
		*this = BVH(prims[0], prims[1]);
		return;
	}

	for (uint32_t i = 0; i < prims.size(); i++)
		bounds = Union(bounds, prims[i]->Bounds());

	Point pivot = bounds.Centroid();

	int midpoint = Split(prims, 0, prims.size(), pivot[0], 0);

	left = BuildBranch(prims, 0, midpoint, 1);
	right = BuildBranch(prims, midpoint, prims.size(), 1);
}

BVH::BVH(Reference<Primitive> p1, Reference<Primitive> p2)
{
	left = p1;
	right = p2;
	bounds = Union(p1->Bounds(), p2->Bounds());
}

BVH::BVH(Reference<Primitive> p1, Reference<Primitive> p2, BBox bb)
{
	left = p1;
	right = p2;
	bounds = bb;
}

BVH::~BVH()
{ }

BBox BVH::Bounds() const
{
	return bounds;
}

bool BVH::Intersect(const Ray& ray, Intersection& sr)
{
	if (::IntersectP(bounds, ray))
	{
		bool isahit1 = false, isahit2 = false;

		isahit1 = left->Intersect(ray, sr);
		isahit2 = right->Intersect(ray, sr);

		return (isahit1 || isahit2);
	}
	else
	{
		return false;
	}
}

bool BVH::IntersectP(const Ray& ray)
{
	if (!bounds.IntersectP(ray, NULL, NULL)) return false;

	if (left->IntersectP(ray)) return true;
	return right->IntersectP(ray);
}

//Private constructor for recursion
Reference<Primitive> BVH::BuildBranch(vector<Reference<Primitive> > &prims, uint32_t start, uint32_t end, int axis)
{
	if (end - start == 1) return prims[start];
	if (end - start == 2) return Reference<Primitive>(new BVH(prims[start], prims[start + 1]));

	BBox b = prims[start]->Bounds();
	for (uint32_t i = start + 1; i < end; i++)
		b = Union(bounds, prims[i]->Bounds());

	Point pivot = b.Centroid();

	int midpoint = Split(prims, start, end, pivot[axis], axis);

	int newAxis = (axis + 1) % 3;
	Reference<Primitive> leftBranch(BuildBranch(prims, start, midpoint, newAxis));
	Reference<Primitive> rightBranch(BuildBranch(prims, midpoint, end, newAxis));

	return Reference<Primitive>(new BVH(leftBranch, rightBranch, b));
}

int BVH::Split(vector<Reference<Primitive> > &prims, uint32_t start, uint32_t end, float pivot, int axis)
{
	SortPrims(prims, start, end, axis);
	return (start + end) / 2;
}

void BVH::SortPrims(vector<Reference<Primitive> > &prims, uint32_t start, uint32_t end, int axis)
{
	for (uint32_t i = start; i < end; i++)
	{
		for (uint32_t j = start; j < end - 1; j++)
		{
			if (prims[j]->Bounds().Centroid()[axis] < prims[j + 1]->Bounds().Centroid()[axis])
			{
				Reference<Primitive> temp = prims[j];
				prims[j] = prims[j + 1];
				prims[j + 1] = temp;
			}
		}
	}
}