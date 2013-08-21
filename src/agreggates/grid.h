/*
 * Grid.h
 *
 *  Created on: 20. 8. 2013
 *      Author: polygoncz
 */

#ifndef GRID_H_
#define GRID_H_

#include <agreggate.h>
#include <vector>
#include <stdint.h>

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
	vector<Reference<Primitive>> primitives;
};

class Grid: public Agreggate
{
public:
	Grid(const vector<Reference<Primitive>> &p);
	virtual ~Grid();

	virtual bool Intersect(const Ray& ray, float& tmin, Intersection& sr) const;
	virtual bool IntersectP(const Ray& ray) const;
	virtual BBox Bounds() const;

private:
	vector<Reference<Primitive>> primitives;
};

#endif /* GRID_H_ */
