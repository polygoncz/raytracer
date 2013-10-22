#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include "core/reference.h"
#include "core/primitive.h"
#include <stdint.h>

#define MAX_VOXELS 128

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

	virtual bool Intersect(const Ray& ray, Intersection& sr);
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;

private:
	inline int PosToVoxel(const Point &p, int axis) const
	{
		int v = (int) ((p[axis] - bounds.pMin[axis]) * invWidth[axis]);
		return Clamp(v, 0, nVoxels[axis] - 1);
	}

	float VoxelToPos(int p, int axis) const
	{
		return bounds.pMin[axis] + p * width[axis];
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