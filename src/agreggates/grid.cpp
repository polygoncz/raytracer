/*
 * Grid.cpp
 *
 *  Created on: 20. 8. 2013
 *      Author: polygoncz
 */

#include "agreggates/grid.h"

Grid::Grid(const vector<Reference<Primitive>> &p)
{

}

Grid::~Grid()
{
	// TODO Auto-generated destructor stub
}

bool Grid::Intersect(const Ray &ray, float &tmin, Intersection &sr) const
{
	return false;
}

bool Grid::IntersectP(const Ray &ray) const
{
	return false;
}

BBox Grid::Bounds() const
{
	return BBox();
}

//--------------------Voxel's methods---------------------------
bool Voxel::Intersect(const Ray &ray, Intersection &inter) const
{
	float tmin = INFINITY;
	float t = 0.f;

	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<Primitive> p = primitives[i];
		if (p->Intersect(ray, t, inter) && (t < tmin))
		{
			inter.hitObject = true;
			tmin = t;
			inter.material = p->GetMaterial();
			inter.hitPoint = ray(tmin);
			inter.t = tmin;
		}
	}

	return inter.hitObject;
}

bool Voxel::IntersectP(const Ray &ray) const
{
	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<Primitive> p = primitives[i];
		if (p->IntersectP(ray))
			return true;
	}

	return false;
}
