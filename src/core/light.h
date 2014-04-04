#pragma once

/**
 * @file
 */

#include "geometry.h"
#include "color.h"
#include "intersection.h"

class Vector;
class RGBColor;

/**
 * Rozhraní pro objekty světel. Je možné z nich získat intezitu osvětlení daného bodu
 * a směr k danému bodu.
 */
class Light 
{
public:
	/**
	 * Bezparametrický konstruktor.
	 */
	Light(void)	{}

	/**
	 * Kopírovací konstruktor.
	 * @param light kopírovaná instance
	 */
	Light(const Light& light) {}

	/**
	 * Virtuální destruktor
	 */
	virtual ~Light() {}

	/**
	 * Vypočítá směr světla vzhledme k místu průsečíku.
	 * @param sr informace o průsečíku
	 * @return Vector směru světla
	 */
	virtual Vector GetDirection(const Intersection& sr) const = 0;

	/**
	 * Provede výpočet světelného příspěvku světla pro průsečík.
	 * @param sr informace o průsečíku
	 * @return hodnota světelného příspěvku
	 */
	virtual RGBColor L(const Intersection& sr) const = 0;
};
