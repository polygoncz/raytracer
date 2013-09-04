#pragma once

#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include "core/agreggate.h"
#include "core/reference.h"
#include "core/primitive.h"

#include <vector>

using namespace std;

class BruteForce : public Agreggate
{
public:
	BruteForce(vector<Reference<Primitive> > &p);
	virtual ~BruteForce();

	virtual bool Intersect(const Ray& ray, Intersection& sr) const;
	virtual bool IntersectP(const Ray& ray) const;
	virtual BBox Bounds() const;

private:
	mutable vector<Reference<Primitive> > primitives;
};

#endif