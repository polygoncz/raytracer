#pragma once

#ifndef BXDF_H
#define BXDF_H


#include "color.h"
#include "geometry.h"
#include "core.h"
#include "intersection.h"

/**
 * V��tov� typ, kter� slou�� pro indentifikaci typu BRDF. Podle typu s n�m lze potom odli�n� pracovat.
 */
enum BxDFType
{
	BSDF_REFLECTION		= 1, ///< BRDF, kter� odr�� paprsek a dok�e ho vypo��tat
	BSDF_TRANSMISSION	= 2, ///< BRDF, kter� l�me paprsek a dok�e ho vypo��tat
	BSDF_DIFFUSE		= 4, ///< BRDF dif�zn� slo�ky
	BSDF_SPECULAR		= 8, ///< BRDF specular slo�ky
	BSDF_AMBIENT		= 16 ///< BRDF okoln�ho osv�tlen�
};

/**
 * B�zov� t��da, kter� p�edstavuje objekt obousm�rn� odrazov� distribu�n� funkce (BRDF).
 */
class BxDF
{
public:
	/**
	 * B�zov� konstruktor, kter� nastavuje typ funkce.
	 * @param t typ funkce typu v��tu BxDFType
	 * @see BxDFType
	 */
	BxDF(BxDFType t);

	/**
	 * Kop�rovac� kontruktor
	 * @param brdf kop�rovan� instance
	 */
	BxDF(const BxDF& brdf);

	/**
	 * Virtu�ln� destruktor
	 */
	virtual ~BxDF();

	/**
	 * Metoda slou�� k v�po�tu sv�teln�ho p��sp�vku, na z�klad� zadan�ch hodnot.
	 * @param wi vektoru sm�rem od sv�tla
	 * @parma wo vektoru sm�rem k pozorovateli
	 * @param n norm�la v bod� dopadu
	 * @return velikost sv�teln�ho p��sp�vku 
	 */
	virtual RGBColor F(const Vector& wi, const Vector& wo, const Normal& n) const;

	/**
	 * Metoda vypo��t�v� hodnotu hodnotu odra�en�ho resp. lomen�ho paprsku.
	 * N�vr�cen� hodnota typu RGBColor potom slou�� k ur�en�, jak� ��st
	 * barevn�ho spektra je odra�ena resp. propu�t�na.
	 * @param wi zpravidla vektor sm�ru od pozorovatele
	 * @param wo slou�� k n�vratu vypo�ten�ho vektoru
	 * @param n norm�la v bod� dopadu
	 * @return barevn� hodnota, slou��c� k filtrov�n� spektra
	 */
	virtual RGBColor SampleF(const Vector& wi, Vector& wo, const Normal& n) const;

	/**
	 * Slou�� pro v�po�ty s glob�ln�m osv�tlen�m. PREPARE FOR FUTURE :-)
	 */
	virtual RGBColor Rho(const Vector& wi, const Vector& wo, const Normal& n) const;

	/**
	 * Porovn�v�, jestli BRDF funkce odpov�d� zadan�mu typu BxDFType.
	 * @param flags porovn�van� typy
	 * @see BxDFType
	 * @return true/false
	 */
	bool MatchesType(BxDFType flags) const;
private:
	BxDFType type; ///< typ BRDF funkce
};

#endif // !BXDF_H