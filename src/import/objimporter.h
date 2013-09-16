/* 
 * File:   ObjImporter.h
 * Author: pavel
 *
 * Created on 2. srpen 2013, 22:21
 */

#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H

#include "shapes/trianglemesh.h"
#include "core/reference.h"

class ObjImporter
{
public:
	ObjImporter();
	Reference<GeometricPrimitive> LoadObj(const char* path) const;
private:

};

#endif	/* OBJIMPORTER_H */

