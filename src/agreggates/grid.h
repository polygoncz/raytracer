/*
 * Grid.h
 *
 *  Created on: 20. 8. 2013
 *      Author: polygoncz
 */

#ifndef GRID_H_
#define GRID_H_

#include "core/agreggate.h"
#include <vector>
#include "core/reference.h"
#include "core/primitive.h"
#include <stdint.h>

#define MAX_VOXELS 64

using namespace std;

struct Voxel
{
	Voxel(void) { }
	Voxel(Reference<Primitive> &p)
	{
		primitives.push_back(p);
	}

	void AddPrimitive(Reference<Primitive> &p)
	{
		primitives.push_back(p);
	}

	bool Intersect(const Ray &ray, Intersection &inter) const;
	bool IntersectP(const Ray &ray) const;

private:
	vector<Reference<Primitive> > primitives;
};

class Grid: public Agreggate
{
public:
	Grid(vector<Reference<Primitive> > &p);
	virtual ~Grid();

	virtual bool Intersect(const Ray& ray, Intersection& sr) const;
	virtual bool IntersectP(const Ray& ray) const;
	virtual BBox Bounds() const;

private:
	inline int posToVoxel(const Point &p, int axis) const
	{
		int v = (int) ((p[axis] - bounds.pMin[axis]) * invWidth[axis]);
		return Clamp(v, 0, nVoxels[axis] - 1);
	}

	inline int offset(int x, int y, int z) const
	{
		return x + y*nVoxels[0] + z*nVoxels[0]*nVoxels[1];
	}

private:
	int nv;
	int nVoxels[3];
	Vector width;
	Vector invWidth;
	Voxel** voxels;
	BBox bounds;
	vector<Reference<Primitive> > primitives;
};

#endif /* GRID_H_ */
