#pragma once

/**
 * @file 
 * Soubor obsahuje třídu a makra preprocesoru pro vedení jednoduchých statistik.
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics
{
public:
	/** Restart statistik. */
	static void Reset()
	{
		numPrimaryRays = 0L;
		numShadowRays = 0L;
		numReflectedRays = 0L;
		numTranssmitedRays = 0L;
		numTriangles = 0L;
		numRayTriangleInters = 0L;
	}

	/** Přidání primárního paprsku. */
	static void AddPrimaryRay()
	{
		numPrimaryRays++;
	}

	/** Přidání stínového paprsku. */
	static void AddShadowRay()
	{
		numShadowRays++;
	}

	/** Přidání odraženého paprsku. */
	static void AddReflectedRay()
	{
		numReflectedRays++;
	}

	/** Přidání lomeného paprsku. */
	static void AddTranssmitedRay()
	{
		numTranssmitedRays++;
	}

	/** Přidání trojúhelníku. */
	static void AddTriangle()
	{
		numTriangles++;
	}

	/** Přidání provedení výpočtu průsečíku paprsek-trojúhelník. */
	static void AddRayTriangleInter()
	{
		numRayTriangleInters++;
	}

	//rays stats
	static long numPrimaryRays; ///< Počet primárních paprsků.
	static long numShadowRays; ///< Počet stínových paprsků.
	static long numReflectedRays; ///< Počet odražených paprsků.
	static long numTranssmitedRays; ///< Počet lomených paprsků.

	//shapes stats
	static long numTriangles; ///< Počet trojúhelníků ve scéně.

	//intersection stats
	static long numRayTriangleInters; ///< Počet průsečíků paprsek-trojúhelník.
};

/** Makro pro pro resetování statistik */
#define STATS_RESET() Statistics::Reset()

/** Makro pro přidání primárního paprsku. */
#define STATS_ADD_PRIMARY_RAY() Statistics::AddPrimaryRay()
/** Makro pro přidání stínového paprsku. */
#define STATS_ADD_SHADOW_RAY() Statistics::AddShadowRay()
/** Makro pro přidání odraženého paprsku. */
#define STATS_ADD_REFLECTED_RAY() Statistics::AddReflectedRay()
/** Makro pro přidání lomeného paprsku. */
#define STATS_ADD_TRANS_RAY() Statistics::AddTranssmitedRay()

/** Makro pro přidání trojúhelníku. */
#define STATS_ADD_TRIANGLE() Statistics::AddTriangle()

/** Makro pro přidání zvýšení počtu vypočtených trojúhelníků paprsek-trojúhelník. */
#define STATS_ADD_RAY_TRIANGLE() Statistics::AddRayTriangleInter()

#endif /* STATISTICS_H_ */
