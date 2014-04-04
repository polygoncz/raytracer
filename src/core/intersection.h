#pragma once

/**
 * @file
 */

#include "core.h"

#include "constants.h"
#include "scene.h"
#include "geometry.h"
#include "material.h"

/**
 * Třída uchovává atributy, které představují souhrn 
 * informací o průsečíku paprsku s objektem ve scéně.
 * Všechny její atributy jsou veřejné.
 */
class Intersection
{
public:
	Intersection()
			: hitObject(false), material(NULL), depth(0), t(INFINITY)
	{
	}
	Intersection(const Intersection& sr)
			: hitObject(sr.hitObject), hitPoint(sr.hitPoint), normal(sr.normal), ray(
					sr.ray), material(sr.material), depth(sr.depth), t(sr.t)
	{
	}

	bool hitObject; ///< protnul paprsek objekt?
	Point hitPoint; ///< Souřadnice místa dopadu
	Normal normal; ///< Normála v místě dopadu
	Ray ray; ///< Paprsek, pro který se provádí výpočet
	Reference<Material> material; ///< Reference na materiál objektu
	int depth; ///< Hloubka rekurze
	float t; ///< hodnota parametru t v místě dopadu
};
