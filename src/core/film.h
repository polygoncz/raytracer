#pragma once

/**
 * @file
 */

/**
 * Třída Film reprezentuje film v kameře. Narozdíl od klasického filmu v reálném světě,
 * tento uchovává takové atributy, které jsou potom využitelné pro práci s počítačovou grafikou.
 */
class Film
{
public:
	/**
	 * Bezparametrický konstruktor (co ten tu dělá?)
	 */
	Film();

	/**
	 * Kopírovací konstruktor.
	 * @param plane kopírovaná instance
	 */
	Film(const Film& plane);

	/**
	 * Parametrický konstruktor.
	 * @param width výška v pixelech
	 * @param height šířka v pixelech
	 * @param size velikost pixelu ve scéně
	 * @param gamma gamma obrázku
	 * @param invGamma inverzní gamma pro zjednodušení operace dělení
	 */
	Film(int width, int height, float size, float gamma = 1.0, float invGamma =	1.0);

	/**
	 * Destruktor
	 */
	~Film();
public:
	int width; ///< výška v pixelech
	int height; ///< šířka v pixelech
	float size; ///< velikost pixelu ve scéně
	float gamma; ///< gamma obrázku
	float invGamma; ///< inverzní gamma pro zjednodušení operace dělení
};
