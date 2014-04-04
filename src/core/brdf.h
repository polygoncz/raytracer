#pragma once

/**
 * @file
 */

#ifndef BXDF_H
#define BXDF_H


#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

/**
 * Výčtový typ, který slouží pro indentifikaci typu BRDF. Podle typu s ním lze potom odlišně pracovat.
 */
enum BxDFType
{
	BSDF_REFLECTION		= 1, ///< BRDF, která odráží paprsek a dokáže ho vypočítat
	BSDF_TRANSMISSION	= 2, ///< BRDF, která láme paprsek a dokáže ho vypočítat
	BSDF_DIFFUSE		= 4, ///< BRDF difúzní složky
	BSDF_SPECULAR		= 8, ///< BRDF specular složky
	BSDF_AMBIENT		= 16 ///< BRDF okolního osvětlení
};

/**
 * Bázová třída, která představuje objekt obousměrné odrazové distribuční funkce (BRDF).
 */
class BxDF
{
public:
	/**
	 * Bázový konstruktor, který nastavuje typ funkce.
	 * @param t typ funkce typu výčtu BxDFType
	 * @see BxDFType
	 */
	BxDF(BxDFType t);

	/**
	 * Kopírovací kontruktor
	 * @param brdf kopírovaná instance
	 */
	BxDF(const BxDF& brdf);

	/**
	 * Virtuální destruktor
	 */
	virtual ~BxDF();

	/**
	 * Metoda slouží k výpočtu světelného příspěvku, na základě zadaných hodnot.
	 * @param wi vektoru směrem od světla
	 * @parma wo vektoru směrem k pozorovateli
	 * @param n normála v bodě dopadu
	 * @return velikost světelného příspěvku 
	 */
	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;

	/**
	 * Metoda vypočítává hodnotu hodnotu odraženého resp. lomeného paprsku.
	 * Návrácená hodnota typu RGBColor potom slouží k určení, jaká část
	 * barevného spektra je odražena resp. propuštěna.
	 * @param wi zpravidla vektor směru od pozorovatele
	 * @param wo slouží k návratu vypočteného vektoru
	 * @param n normála v bodě dopadu
	 * @return barevná hodnota, sloužící k filtrování spektra
	 */
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;

	/**
	 * Slouží pro výpočty s globálním osvětlením. PREPARE FOR FUTURE :-)
	 */
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

	/**
	 * Porovnává, jestli BRDF funkce odpovídá zadanému typu BxDFType.
	 * @param flags porovnávané typy
	 * @see BxDFType
	 * @return true/false
	 */
	bool MatchesType(BxDFType flags) const;
private:
	BxDFType type; ///< typ BRDF funkce
};

#endif // !BXDF_H