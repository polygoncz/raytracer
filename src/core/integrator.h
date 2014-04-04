#pragma once

/**
 * @file
 */

#include "geometry.h"
#include "color.h"

/**
 * Potomci rozhraní Integrator provádí výpočty světelného příspěvku
 * povrchu v místě průsečíku paprsku s objektem.
 */
class Integrator
{
public:
	Integrator();
	Integrator(const Integrator& tr);
	virtual ~Integrator();

	/**
	 * Metoda vrací světelný příspěvek vypočítáný v místě protnutí paprsku s objektem scény.
	 * @param ray paprsek pro který byl vypočten průsečík
	 * @param scene objekt scény, kvůli přístupu ke světlům
	 * @param inter informace o průsečíku
	 * @return světelný příspěvek v bodě
	 */
	virtual RGBColor L(const Ray& ray, const Scene& scene, Intersection& inter) const = 0;
};
