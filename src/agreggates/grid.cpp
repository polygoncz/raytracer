/*
 * Grid.cpp
 *
 *  Created on: 20. 8. 2013
 *      Author: polygoncz
 */

#include "agreggates/grid.h"

Grid::Grid(vector<Reference<GeometricPrimitive>> &p)
{
	//Refine primitives
	for (uint32_t i = 0; i < p.size(); i++)
	{
		if (p[i]->CanIntersect())
			primitives.push_back(p[i]);
		else
			p[i]->Refine(primitives);
	}

	//Compute bounding box of primitives
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
			vmin[axis] = posToVoxel(pb.pMin, axis);
			vmax[axis] = posToVoxel(pb.pMax, axis);
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

bool Grid::Intersect(const Ray &ray, Intersection &sr) const
{
	//Kontrola jestli je paprsek uvnitr, pripadne jestli protne BBox sceny
	float rayT = 0.f;
	if (!bounds.IsInside(ray.o))
		rayT = ray.mint;
	else if (!bounds.IntersectP(ray, &rayT, 0))
		return false;

	int exit[3], step[3], voxel[3];
	float deltaT[3], nextCrossingT[3];
	for (int axis = 0; axis < 3; ++axis)
	{
		float rayOrigCell = ((ray.o[axis] + ray.d[axis] * rayT) - bounds.pMin[axis]);
		voxel[axis] = Clamp<int>(Round2Int(rayOrigCell / invWidth[axis]), 0, nVoxels[axis] - 1);

		if (ray.d[axis] < 0)
		{
			float invDir = 1.f / ray.d[axis];
			deltaT[axis] = -width[axis] * invDir;
			nextCrossingT[axis] = ray.mint + (voxel[axis] * width[axis] - rayOrigCell) * invDir;
			exit[axis] = -1;
			step[axis] = -1;
		}
		else
		{
			float invDir = 1.f / ray.d[axis];
			deltaT[axis] = width[axis] * invDir;
			nextCrossingT[axis] = ray.mint + ((voxel[axis] + 1) * width[axis] - rayOrigCell) * invDir;
			exit[axis] = nVoxels[axis];
			step[axis] = 1;
		}
	}

	while(true)
	{
		int o = offset(voxel[0], voxel[1], voxel[2]);
		if (voxels[o] != NULL)
			if (voxels[o]->Intersect(ray, sr))
				return true;

		uint8_t k = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
				((nextCrossingT[0] < nextCrossingT[2]) << 1) +
				((nextCrossingT[1] < nextCrossingT[2]));

		static const uint8_t map[8] = {2, 1, 2, 1, 2, 2, 0, 0};
		uint8_t axis = map[k];

		if (ray.maxt < nextCrossingT[axis]) return false;
		voxel[axis] += step[axis];
		if (voxel[axis] == exit[axis]) return false;
		nextCrossingT[axis] += deltaT[axis];
	}

	return false;
}

bool Grid::IntersectP(const Ray &ray) const
{
	float rayT = 0.f;
	if (!bounds.IsInside(ray.o))
		rayT = ray.mint;
	else if (!bounds.IntersectP(ray, &rayT, 0))
		return false;

	int exit[3], step[3], voxel[3];
	float deltaT[3], nextCrossingT[3];
	for (int axis = 0; axis < 3; ++axis)
	{
		float rayOrigCell = ((ray.o[axis] + ray.d[axis] * rayT) - bounds.pMin[axis]);
		voxel[axis] = Clamp<int>(Round2Int(rayOrigCell / invWidth[axis]), 0, nVoxels[axis] - 1);

		if (ray.d[axis] < 0)
		{
			float invDir = 1.f / ray.d[axis];
			deltaT[axis] = -width[axis] * invDir;
			nextCrossingT[axis] = ray.mint + (voxel[axis] * width[axis] - rayOrigCell) * invDir;
			exit[axis] = -1;
			step[axis] = -1;
		}
		else
		{
			float invDir = 1.f / ray.d[axis];
			deltaT[axis] = width[axis] * invDir;
			nextCrossingT[axis] = ray.mint + ((voxel[axis] + 1) * width[axis] - rayOrigCell) * invDir;
			exit[axis] = nVoxels[axis];
			step[axis] = 1;
		}
	}

	while(true)
	{
		int o = offset(voxel[0], voxel[1], voxel[2]);
		if (voxels[o] != NULL)
			if (voxels[o]->IntersectP(ray))
				return true;

		uint8_t k = ((nextCrossingT[0] < nextCrossingT[1]) << 2) +
				((nextCrossingT[0] < nextCrossingT[2]) << 1) +
				((nextCrossingT[1] < nextCrossingT[2]));

		static const uint8_t map[8] = {2, 1, 2, 1, 2, 2, 0, 0};
		uint8_t axis = map[k];

		if (ray.maxt < nextCrossingT[axis]) return false;
		voxel[axis] += step[axis];
		if (voxel[axis] == exit[axis]) return false;
		nextCrossingT[axis] += deltaT[axis];
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
	float tmin = INFINITY;
	float t = 0.f;

	for (size_t i = 0; i < primitives.size(); i++)
	{
		Reference<GeometricPrimitive> p = primitives[i];
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
		Reference<GeometricPrimitive> p = primitives[i];
		if (p->IntersectP(ray))
			return true;
	}

	return false;
}
