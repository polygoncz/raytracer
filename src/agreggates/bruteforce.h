#pragma once

#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include "core/reference.h"
#include "core/primitive.h"

#include <vector>

using namespace std;

/**
 * Akcelerační struktura provádí výpočet průsečíku s každým tělesem scény.
 */
class BruteForce : public Agreggate
{
public:
	/**
	 * Vytvoří instanci se zadanými tělesy.
	 * @param p std::vector s tělesy.
	 */
	BruteForce(vector<Reference<Primitive> > &p);
	virtual ~BruteForce();

	/** @copydoc Primitive::Intersect() */
	virtual bool Intersect(const Ray& ray, Intersection& sr);

	/** @copydoc Primitive::Intersect() */
	virtual bool IntersectP(const Ray& ray);

	/** Vypočítá obalovou krychli kolem všech svých těles. */
	virtual BBox Bounds() const;

private:
	/**
	 * std::vector obsahující tělesa.
	 */
	mutable vector<Reference<Primitive> > primitives;
};

#endif