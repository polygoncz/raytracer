/* 
 * File:   ObjImporter.cpp
 * Author: pavel
 * 
 * Created on 2. srpen 2013, 22:21
 */

#include "objimporter.h"

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
    vector<int> topology;
    int nf = 0;
    
    while (true)
    {
        char lineHeader[128];
        int res = fscanf(f, "%s", lineHeader);
        if (res == EOF)
            break;
        
        if (strcmp(lineHeader, "v") == 0)
        {
            Point p;
            fscanf(f, "%f %f %f\n", &p.x, &p.y, &p.z);
            points.push_back(p);
        }
        
        if (strcmp(lineHeader, "f") == 0)
        {
            int a = 0;
            for (int i = 0; i < 3; i++)
            {
                fscanf(f, "%d", &a);
                topology.push_back(--a);
            }
            nf++;
        }
    }
    
    fclose(f);
    
    TriangleMesh* mesh = new TriangleMesh(nf, points.size(), &topology[0], &points[0], NULL);
    return mesh;
}