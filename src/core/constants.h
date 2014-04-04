#pragma once
#include <cfloat>

/**
 * @file
 *
 * Tento soubor slouží k definování některých často používaných hodnot jako konstant preprocesoru.
 *
 */

#define PI 3.14159265359f
#define INV_PI 0.314159265359f
#define EPSILON 0.0001f

#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY FLT_MAX
