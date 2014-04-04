#pragma once

/**
 * @file
 */

#include "core.h"

#include "geometry.h"
#include "film.h"

/**
 * Struktura která, určuje polohu vzorku na filmu kamery.
 * Počítáno dle zvyklostí od levého horního rohu.
 */
struct CameraSample
{
	float x, y;
};

typedef CameraSample Pixel; ///< sémantika

/**
 * Bázová třída kamery. Hlavní schopností je generování paprsku
 * na základě polohy vzorku na filmu.
 */
class Camera
{
public:
	/**
	 * Bezparametrický konstruktor (co tu dělá bych rád věděl).
	 */
	Camera(void);

	/**
	 * Konstruktor.
	 * @param eye bod pozorovatele
	 * @param target cíl pozorování
	 * @param up vektor natočení
	 * @param exposure expozice (FUTURE)
	 */
	Camera(const Point& eye, const Point& target, const Vector& up,
		float exposure = 1.f);

	/**
	 * Virtuální destruktor.
	 */
	virtual ~Camera();

	/**
	 * Na základě zadaných parametrů v podobě vzorku na filmu kamery vypočítá
	 * odpovídající transformovaný paprsek. Implementace je potom provedena
	 * v potomcích třídy.
	 * @param sample vzorek na filmu kamery
	 * @param ray ukazatel na instanci třídy Ray, slouží jako návratová hodnota
	 * @see Ray
	 */
	virtual void GenerateRay(const CameraSample& sample, Ray* ray) const = 0;

protected:
	/**
	 * Výpočet ortonormální báze pohledu.
	 */
	void ComputeUVW();

protected:
	Film* film; ///< ukazatel na film
	Point eye, target; ///< body pozorovatele a cíle pozorování
	Vector up; ///< vektor natočení kamery
	Vector u, v, w; ///< ortonormální báze pohledu
	float exposure; ///< expozice (FUTURE)
};
