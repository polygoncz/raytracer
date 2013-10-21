/*
 * Grid.cpp
 *
 *  Created on: 20. 8. 2013
 *      Author: polygoncz
 */

#include "agreggates/grid.h"

Grid::Grid(vector<Reference<Primitive>> &p)
{
	for (uint32_t i = 0; i < p.size(); i++)
	{
		if (p[i]->CanIntersect())
			primitives.push_back(p[i]);
		else
			p[i]->Refine(primitives);
	}

	for (uint32_t i = 0; i < primitives.size(); i++)
		bounds = Union(bounds, primitives[i]->Bounds());

	Vector delta = bounds.Diagonal();
	int maxAxis = bounds.MaxDimensionIndex();
	float invMaxWidth = 1.f / delta[maxAxis];
	float root = 3.f * powf(float(primitives.size()), 1.f/3.f);
	float voxelsPerUnit = root * invMaxWidth;

	for (int axis = 0; axis < 3; axis++)
	{
		nVoxels[axis] = Round2Int(delta[axis] * voxelsPerUnit);
		nVoxels[axis] = Clamp(nVoxels[axis], 1, MAX_VOXELS);
	}

	nv = nVoxels[0] * nVoxels[1] * nVoxels[2];

	for (int axis = 0; axis < 3; axis++)
	{
		width[axis] = delta[axis] / nVoxels[axis];
		invWidth[axis] = (width[axis] == 0.f) ? 0.f : 1.f / width[axis];
	}

	voxels = new Voxel*[nv];
	memset(voxels, 0, nv * sizeof(Voxel *));

	for (uint32_t i = 0; i < primitives.size(); i++)
	{
		BBox pb = primitives[i]->Bounds();
		int vmin[3], vmax[3];
		for (int axis = 0; axis < 3; axis++)
		{
			vmin[axis] = PosToVoxel(pb.pMin, axis);
			vmax[axis] = PosToVoxel(pb.pMax, axis);
		}

		for (int x = vmin[0]; x <= vmax[0]; x++)
			for (int y = vmin[1]; y <= vmax[1]; y++)
				for (int z = vmin[2]; z <= vmax[2]; z++)
				{
					int o = offset(x, y, z);
					if (!voxels[o])
					{
						voxels[o] = new Voxel;
						*voxels[o] = Voxel(primitives[i]);
					}
					else
					{
						voxels[o]->AddPrimitive(primitives[i]);
					}
				}
	}
}

Grid::~Grid()
{
	// TODO Auto-generated destructor stub
}

bool Grid::Intersect(const Ray &ray, Intersection &sr)
{
	//Kontrola jestli je paprsek uvnitr, pripadne jestli protne BBox sceny
	float rayT = 0.f;
	if (bounds.IsInside(ray(ray.mint)))
	{
		rayT = ray.mint;
	}
	else if (!bounds.IntersectP(ray, NULL, NULL))
	{
		return false;
	}
	Point gridIntersect = ray(rayT);

	// Set up 3D DDA for ray
	float nextCrossingT[3], deltaT[3];
	int step[3], out[3], pos[3];
	for (int axis = 0; axis < 3; ++axis)
	{
		// Compute current voxel for axis
		pos[axis] = PosToVoxel(gridIntersect, axis);
		if (ray.d[axis] >= 0)
		{
			// Handle ray with positive direction for voxel stepping
			nextCrossingT[axis] = rayT + (VoxelToPos(pos[axis]+1, axis) - gridIntersect[axis]) / ray.d[axis];
			deltaT[axis] = width[axis] / ray.d[axis];
			step[axis] = 1;
			out[axis] = nVoxels[axis];
		}
		else
		{
			// Handle ray with negative direction for voxel stepping
			nextCrossingT[axis] = rayT + (VoxelToPos(pos[axis], axis) - gridIntersect[axis]) / ray.d[axis];
			deltaT[axis] = -width[axis] / ray.d[axis];
			step[axis] = -1;
			out[axis] = -1;
		}
	}

	// Walk ray through voxel grid
	bool hitSomething = false;
	while(true)
	{
		// Check for intersection in current voxel and advance to next
		Voxel *voxel = voxels[offset(pos[0], pos[1], pos[2])];
		if (voxel != NULL)
			hitSomething |= voxel->Intersect(ray, sr);

		// Find stepAxis for stepping to next voxel
		int bits = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
		           ((nextCrossingT[0] < nextCrossingT[2]) << 1) +
		           ((nextCrossingT[1] < nextCrossingT[2]));
		const int cmpToAxis[8] = { 2, 1, 2, 1, 2, 2, 0, 0 };
		int stepAxis = cmpToAxis[bits];
		if (ray.maxt < nextCrossingT[stepAxis])
			break;
		pos[stepAxis] += step[stepAxis];
		if (pos[stepAxis] == out[stepAxis])
			break;
		nextCrossingT[stepAxis] += deltaT[stepAxis];
	}

	return hitSomething;
}

bool Grid::IntersectP(const Ray &ray)
{
	float rayT = 0.f;
	if (bounds.IsInside(ray(ray.mint)))
		rayT = ray.mint;
	else if (!bounds.IntersectP(ray, NULL, NULL))
	{
		return false;
	}
	Point gridIntersect = ray(rayT);

	// Set up 3D DDA for ray
	float nextCrossingT[3], deltaT[3];
	int step[3], out[3], pos[3];
	for (int axis = 0; axis < 3; ++axis)
	{
		// Compute current voxel for axis
		pos[axis] = PosToVoxel(gridIntersect, axis);
		if (ray.d[axis] >= 0)
		{
			// Handle ray with positive direction for voxel stepping
			nextCrossingT[axis] = rayT + (VoxelToPos(pos[axis]+1, axis) - gridIntersect[axis]) / ray.d[axis];
			deltaT[axis] = width[axis] / ray.d[axis];
			step[axis] = 1;
			out[axis] = nVoxels[axis];
		}
		else
		{
			// Handle ray with negative direction for voxel stepping
			nextCrossingT[axis] = rayT + (VoxelToPos(pos[axis], axis) - gridIntersect[axis]) / ray.d[axis];
			deltaT[axis] = -width[axis] / ray.d[axis];
			step[axis] = -1;
			out[axis] = -1;
		}
	}

	// Walk grid for shadow ray
	while(true)
	{
		int o = offset(pos[0], pos[1], pos[2]);
		Voxel *voxel = voxels[o];
		if (voxel && voxel->IntersectP(ray))
			return true;

		// Find _stepAxis_ for stepping to next voxel
		int bits = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
		    ((nextCrossingT[0] < nextCrossingT[2]) << 1) +
		    ((nextCrossingT[1] < nextCrossingT[2]));
		const int cmpToAxis[8] = { 2, 1, 2, 1, 2, 2, 0, 0 };
		int stepAxis = cmpToAxis[bits];
		if (ray.maxt < nextCrossingT[stepAxis])
			break;
		pos[stepAxis] += step[stepAxis];
		if (pos[stepAxis] == out[stepAxis])
			break;
		nextCrossingT[stepAxis] += deltaT[stepAxis];
	}

	return false;
}

BBox Grid::Bounds() const
{
	return BBox();
}

//--------------------Voxel's methods---------------------------
bool Voxel::Intersect(const Ray &ray, Intersection &inter) const
{
	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<Primitive> p = primitives[i];
		p->Intersect(ray, inter);
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
