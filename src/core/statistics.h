/*
 * statistics.h
 *
 *  Created on: 5. 8. 2013
 *      Author: pavel
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics
{
public:
	static void Reset()
	{
		numPrimaryRays = 0L;
		numShadowRays = 0L;
		numReflectedRays = 0L;
		numTranssmitedRays = 0L;
		numTriangles = 0L;
		numRayTriangleInters = 0L;
	}

	static void AddPrimaryRay()
	{
		numPrimaryRays++;
	}

	static void AddShadowRay()
	{
		numShadowRays++;
	}

	static void AddReflectedRay()
	{
		numReflectedRays++;
	}

	static void AddTranssmitedRay()
	{
		numTranssmitedRays++;
	}

	static void AddTriangle()
	{
		numTriangles++;
	}

	static void AddRayTriangleInter()
	{
		numRayTriangleInters++;
	}

	//rays stats
	static long numPrimaryRays;
	static long numShadowRays;
	static long numReflectedRays;
	static long numTranssmitedRays;

	//shapes stats
	static long numTriangles;

	//intersection stats
	static long numRayTriangleInters;
};

#define STATS_RESET() Statistics::Reset()

#define STATS_ADD_PRIMARY_RAY() Statistics::AddPrimaryRay()
#define STATS_ADD_SHADOW_RAY() Statistics::AddShadowRay()
#define STATS_ADD_REFLECTED_RAY() Statistics::AddReflectedRay()
#define STATS_ADD_TRANS_RAY() Statistics::AddTranssmitedRay()

#define STATS_ADD_TRIANGLE() Statistics::AddTriangle()

#define STATS_ADD_RAY_TRIANGLE() Statistics::AddRayTriangleInter()

#endif /* STATISTICS_H_ */
