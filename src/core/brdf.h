#pragma once

#ifndef BXDF_H
#define BXDF_H


#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

/**
 * Výètový typ, který slouží pro indentifikaci typu BRDF. Podle typu s ním lze potom odlišnì pracovat.
 */
enum BxDFType
{
	BSDF_REFLECTION		= 1, ///< BRDF, která odráží paprsek a dokáže ho vypoèítat
	BSDF_TRANSMISSION	= 2, ///< BRDF, která láme paprsek a dokáže ho vypoèítat
	BSDF_DIFFUSE		= 4, ///< BRDF difúzní složky
	BSDF_SPECULAR		= 8, ///< BRDF specular složky
	BSDF_AMBIENT		= 16 ///< BRDF okolního osvìtlení
};

/**
 * Bázová tøída, která pøedstavuje objekt obousmìrné odrazové distribuèní funkce (BRDF).
 */
class BxDF
{
public:
	/**
	 * Bázový konstruktor, který nastavuje typ funkce.
	 * @param t typ funkce typu výètu BxDFType
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
	 * Metoda slouží k výpoètu svìtelného pøíspìvku, na základì zadaných hodnot.
	 * @param wi vektoru smìrem od svìtla
	 * @parma wo vektoru smìrem k pozorovateli
	 * @param n normála v bodì dopadu
	 * @return velikost svìtelného pøíspìvku 
	 */
	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;

	/**
	 * Metoda vypoèítává hodnotu hodnotu odraženého resp. lomeného paprsku.
	 * Návrácená hodnota typu RGBColor potom slouží k urèení, jaká èást
	 * barevného spektra je odražena resp. propuštìna.
	 * @param wi zpravidla vektor smìru od pozorovatele
	 * @param wo slouží k návratu vypoèteného vektoru
	 * @param n normála v bodì dopadu
	 * @return barevná hodnota, sloužící k filtrování spektra
	 */
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;

	/**
	 * Slouží pro výpoèty s globálním osvìtlením. PREPARE FOR FUTURE :-)
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