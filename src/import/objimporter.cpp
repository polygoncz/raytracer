/* 
 * File:   ObjImporter.cpp
 * Author: pavel
 * 
 * Created on 2. srpen 2013, 22:21
 */

#include "objimporter.h"
#include "core/reference.h"
#include "materials/matte.h"
#include <cstdlib>
#include <cstdio>

ObjImporter::ObjImporter()
{
}

TriangleMesh* ObjImporter::LoadObj(const char* path) const
{
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		cout << "Cannot open file." << endl;
		return NULL;
	}

	vector<Point> points;
	vector<Vertex> topology;
	vector<Normal> normals;
	int nf = 0;

	while (true)
	{
		char lineHeader[128];
		int res = fscanf(f, "%s", lineHeader);
		if (res == EOF) break;

		if (strcmp(lineHeader, "v") == 0)
		{
			Point p;
			fscanf(f, "%f %f %f\n", &p.x, &p.y, &p.z);
			points.push_back(p);
		}

		if (strcmp(lineHeader, "vn") == 0)
		{
			Normal n;
			fscanf(f, "%f %f %f\n", &n.x, &n.y, &n.z);
			normals.push_back(n);
		}

		if (strcmp(lineHeader, "f") == 0)
		{
			Vertex a;
			for (int i = 0; i < 3; i++)
			{
				fscanf(f, "%d//%d", &a.p, &a.n);
				--a.p;
				--a.n;
				topology.push_back(a);
			}
			nf++;
		}
	}

	fclose(f);

	Reference<Material> matte(new Matte(GREY, 0.1f, 0.8f));
	TriangleMesh* mesh = new TriangleMesh(nf, points.size(), normals.size(),
			&topology[0], &points[0], &normals[0], matte);
	return mesh;
}
