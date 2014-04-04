#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include "core/reference.h"
#include "core/primitive.h"
#include <stdint.h>


#define MAX_VOXELS 128 ///< Maximální počet voxelů v každém rozměru.

using namespace std;

/**
 * Struktura, která představuje voxel v prostoru.
 * Uchovává pouze objekty a zprostředkovává výpočty průsečíků stejně jako
 * BruteForce struktura. Poloha voxelu je určena z jeho polohy v mřížce.
 */
struct Voxel
{
	/** Vytvoří prázdný voxel. */
	Voxel(void) { }

	/**
	 * Vytvoří voxel s jedním tělesem.
	 * @param p reference na těleso.
	 */
	Voxel(Reference<Primitive> &p)
	{
		primitives.push_back(p);
	}

	/**
	 * Přidá těleso do voxelu.
	 * @param p reference na těleso.
	 */
	void AddPrimitive(Reference<Primitive> &p)
	{
		primitives.push_back(p);
	}

	/** @copydoc Primitive::Intersect() */
	bool Intersect(const Ray &ray, Intersection &inter) const;
	/** @copydoc Primitive::IntersectP() */
	bool IntersectP(const Ray &ray) const;

private:
	vector<Reference<Primitive> > primitives; ///< Tělesa, která zasahují do voxelu.
};

class Grid: public Agreggate
{
public:
	/**
	 * Vytvoření akcelerační struktury mřížky ze zadaných těles.
	 * Nad každým tělesem se zkusí provést Primitive::Refine().
	 */
	Grid(vector<Reference<Primitive> > &p);
	virtual ~Grid();

	/** @copydoc Primitive::Intersect() Využívá 3D DDA algoritmu. */
	virtual bool Intersect(const Ray& ray, Intersection& sr);
	/** @copydoc Primitive::Intersect() Využívá 3D DDA algoritmu. */
	virtual bool IntersectP(const Ray& ray);
	virtual BBox Bounds() const;

private:
	/**
	 * Dokáže určit ve kterém voxelu zadané osy se bod nachází.
	 * @param p bod pro který je hledá voxel.
	 * @param axis osa ve které se má hledat.
	 * @return číslo hledaného voxelu.
	 */
	inline int PosToVoxel(const Point &p, int axis) const
	{
		int v = (int) ((p[axis] - bounds.pMin[axis]) * invWidth[axis]);
		return Clamp(v, 0, nVoxels[axis] - 1);
	}

	/**
	 * Obrácený postup než je ve funkci PosToVoxel.
	 * @param p číslo voxelu
	 * @param axis osa
	 * @return nejnižší hodnota pozice voxelu v hledané ose.
	 */
	float VoxelToPos(int p, int axis) const
	{
		return bounds.pMin[axis] + p * width[axis];
	}

	/**
	 * Vypočítá index v poli na základě zadaných poloh pro každý rozměr.
	 * @param x poloha voxelu podél osy X
	 * @param y poloha voxelu podél osy Y
	 * @param z poloha voxelu podél osy Z
	 */
	inline int offset(int x, int y, int z) const
	{
		return x + y*nVoxels[0] + z*nVoxels[0]*nVoxels[1];
	}

private:
	int nv; ///< Počet voxelů.
	int nVoxels[3]; /// Počet voxelů v každém rozměru.
	Vector width; ///< Rozměr voxelů (může být různý pro každý směr).
	Vector invWidth; ///< Inverzni hodnoty k width.

	/**
	 * Pole ukazatelů na voxely. Pro příjemnější práci se používá jednorozměrné
	 * pole a pomocí metody offset() se zajišťuje správný posun.
	 */
	Voxel** voxels;
	BBox bounds; ///< Obalová krychle struktury.
	vector<Reference<Primitive> > primitives; ///< Seznam všech těles ve struktuře.
};

#endif /* GRID_H_ */