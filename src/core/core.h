#pragma once

/**
 * @file
 * V souboru jsou definovány některé pomocné funkce.
 * Dále slouží jako pomůcka pro překladač.
 */

#include <cmath>
#include <stdlib.h>

//Pomocné deklarace pro překladač.
class BxDF;
class Light;
class Material;
class Point;
class Vector;
class Ray;
class Normal;
class Scene;
class Intersection;
class RGBColor;
class Integrator;
class Primitive;
class Agreggate;
class GeometricPrimitive;
class Film;
class Camera;
class Statistics;

/**
 * Ořezání hodnoty pomocí intervalu <from; to> pro hodnoty zadaného typu pomocí šablony.
 * @tparam T Musí mít přetíženy operátory menší a větší (<, >)
 * @param val vstupní hodnota
 * @param from spodní hranice intervalu
 * @param to horní hranice intervalu
 * @return ořezaná hodnota zadaného typu
 */
template <class T>
inline T Clamp(T val, T from, T to)
{
	if (val < from) return from;
	if (val > to) return to;

	return val;
}

/**
 * Ořezání hodnoty pomocí intervalu <from; to> pro hodnoty typu float.
 * Z důvodu čitelnosti při použití.
 * @param val vstupní hodnota
 * @param from spodní hranice intervalu
 * @param to horní hranice intervalu
 * @return ořezaná hodnota typu float
 */
inline float Clamp(float val, float from, float to)
{
	return ::Clamp<float>(val, from, to);
}

/**
 * Ořezání hodnoty pomocí intervalu <from; to> pro hodnoty typu int.
 * Z důvodu čitelnosti při použití.
 * @param val vstupní hodnota
 * @param from spodní hranice intervalu
 * @param to horní hranice intervalu
 * @return ořezaná hodnota typu int
 */
inline int Clamp(int val, int from, int to)
{
	return ::Clamp<int>(val, from, to);
}

/**
 * Hledá minimum z nabízených hodnot typu float.
 * @param t1 první hodnota
 * @param t2 druhá hodnota
 * @return menší ze dvou hodnot
 */
inline float Min(float t1, float t2)
{
	return t1 < t2 ? t1 : t2;
}

/**
 * Hledá maximum z nabízených hodnot typu float.
 * @param t1 první hodnota
 * @param t2 druhá hodnota
 * @return větší ze dvou hodnot
 */
inline float Max(float t1, float t2)
{
	return t1 > t2 ? t1 : t2;
}

/**
 * Prohodí dvě zadané hodnoty. Protože jsou parametry zadané jako reference, změna se projeví i vně funkce.
 * @param a reference na první hodnotu
 * @param b reference na druhou hodnotu
 */
inline void Swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

/**
 * Funkce pro výpočet lineární interpolace mezi dvěma float hodnotami.
 * @param t parametr váhy mezi dvěma hodnotami, zadaný v intervalu <0; 1>
 * @param a první hodnota pro interpolaci
 * @param b první hodnota pro interpolaci
 * @return interpolovaná hodnota
 */
inline float Lerp(float t, float a, float b)
{
	return (1.f - t) * a + t * b;
}

/**
 * Funkce pro výpočet kořenů kvadratické funkce.
 * @param a první koeficient kvadratické funkce
 * @param b druhý koeficient kvadratické funkce
 * @param c třetí koeficient kvadratické funkce
 * @param t0 ukazatel na float, kam má být uložena hodnota prvního kořenu
 * @param t1 ukazatel na float, kam má být uložena hodnota druhého kořenu
 * @return vrací, zdali má rovnice řešení v oboru reálných čísel
 */
inline bool Quadratic(float a, float b, float c, float* t0, float* t1)
{
	float disc = b * b - 4 * a * c;

	if (disc < 0.f) return false;

	float e = sqrt(disc);
	float invLowerPart = 1.f / (2.f * a);

	if (t0 != NULL) *t0 = (-b + e) * invLowerPart;
	if (t1 != NULL) *t1 = (-b - e) * invLowerPart;

	return true;
}

/**
 * Převed číslo float na int spolu se zaokrouhlením.
 * @param f hodnota float, kterou chceme zaokrouhlit
 * @return zaokrouhlená hodnota typu int
 */
inline int Round2Int(float f)
{
	return (int) (f + 0.5f);
}

/**
 * Funkce pro získání náhodného čísla desetinného čísla.
 * @return náhodné číslo typu float
 */
inline float RandomFloat()
{
	return (float)rand()/(float)RAND_MAX;
}