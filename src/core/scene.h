#pragma once

/** @file 
 * Soubor obsahuje implementaci scény.
 */

#include "core.h"
#include <vector>

#include "light.h"
#include "color.h"
#include "integrator.h"
#include "film.h"
#include "camera.h"
#include "intersection.h"
#include "reference.h"
#include "primitive.h"

using namespace std;

/**
 * Třída implementuje vykreslovanou prostorovou scénu.
 * Obsahuje atributy o barvě pozadí, světlech, objektech, kamerách atd.
 */
class Scene
{
public:
	Scene();

	/**
	 * Odstraní veškerá data z paměti.
	 */
	~Scene();

	/**
	 * Vybuduje scénu podle souboru XML, který definuje scénu.
	 * Používá k tomu třídu XMLSceneImporter.
	 * @param file cesta k souboru
	 */
	void Build(const char* file);

	/**
	 * Vypočítá průsečík paprsku se scénou. Deleguje tento problém na tělesa ve scéně,
	 * nebo akcelerační struktury.
	 * @param ray paprsek se kterým je počítán průsečík
	 * @param sr reference na strukturu Intersection, kterou naplníme údaji o případném průsečíku
	 * @return jestli má paprsek průsečík s tělesem
	 */
	bool Intersect(const Ray& ray, Intersection& inter) const;

	/**
	 * Optimalizovaná verze metody Intersect(). Opět deleguje problém.
	 * @param ray paprsek se kterým je počítán průsečík
	 * @return jestli má paprsek průsečík s tělesem
	 */
	bool IntersectP(const Ray& ray) const;

	/**
	 * Získá obalový kvádr scény. Ten je vypočítán jako sjendocení obalových kvádrů
	 * všech těles ve scéně, čili jako obalový kvádr akcelerační struktury.
	 * @return Obalový kvádr scény.
	 */
	BBox Bounds() const;

public:
	RGBColor background; ///< Barva pozadí.
	Light* ambient; ///< Okolní osvětlení.
	vector<Light*> lights; ///< Světla, kterými je osvětlena scéna.
	Film* film; ///< Film kamery.
	Camera* cam; ///< Kamera.
	Primitive* aggregator; ///< Akcelerační struktura.
};
