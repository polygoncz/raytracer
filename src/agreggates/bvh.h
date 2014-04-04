#pragma once

#ifndef BVH_H_
#define BVH_H_

#include "core/primitive.h"
#include "core/geometry.h"
#include "core/reference.h"
#include <vector>
#include <cstdint>

using namespace std;

/**
 WIP WIP WIP
 */
class BVH : public Agreggate
{
public:
	BVH(vector<Reference<Primitive> > &prims);
	BVH(Reference<Primitive> p1, Reference<Primitive> p2);
	BVH(Reference<Primitive> p1, Reference<Primitive> p2, BBox bb);
	virtual ~BVH();

	virtual bool Intersect(const Ray& ray, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;

private:
	Reference<Primitive> BuildBranch(vector<Reference<Primitive> >& prims, uint32_t start, uint32_t end, int axis);
	int Split(vector<Reference<Primitive> >& prims, uint32_t start, uint32_t end, float pivot, int axis);
	void SortPrims(vector<Reference<Primitive> >& prims, uint32_t start, uint32_t end, int axis);

private:
	BBox bounds;
	Reference<Primitive> left;
	Reference<Primitive> right;
};

#endif