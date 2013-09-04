/*
 * agreggate.h
 *
 *  Created on: 5. 8. 2013
 *      Author: pavel
 */

#ifndef AGREGGATE_H_
#define AGREGGATE_H_

#include "core/geometry.h"

class Agreggate
{
public:
	Agreggate();
	virtual ~Agreggate();

	virtual bool Intersect(const Ray& ray, Intersection& sr) const = 0;
	virtual bool IntersectP(const Ray& ray) const = 0;
	virtual BBox Bounds() const = 0;
};

#endif /* AGREGGATE_H_ */
