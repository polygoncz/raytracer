#pragma once

#include <cmath>
#include <assert.h>

#include "core.h"
#include "constants.h"

/**
 * Trida trojrozmerneho vektoru.
 * Umoznuje provadet s vektorem základní matematické operace.
 */
class Vector
{
public:

	/**
	 * Defaultní konstruktor.
	 * Všechny složky mají hodnotu 0.
	 */
	Vector()
	{
		x = y = z = 0.f;
	}

	/**
	 * Konstruktor
	 * @param _x hodnota slozky x
	 * @param _y hodnota slozky y
	 * @param _z hodnota slozky z
	 */
	Vector(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
	{
	}

	/**
	 * Kopirovaci konstruktor
	 * @param v vektor urceny ke kopirovani
	 */
	Vector(const Vector& v)
			: x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	 * Konstruktor pro vytvoreni vektoru z objektu Point.
	 * Prislusne souradnice objektu tridy Point se priradi novemu objektu tridy Vector.
	 * @param p objekt tridy Point.
	 */
	Vector(const Point& p)
		: x(p.x), y(p.y), z(p.z)
	{
	}

	/**
	 * Konstruktor pro vytvoreni vektoru z objektu Normal.
	 * Prislusne souradnice objektu tridy Normal se priradi novemu objektu tridy Vector.
	 * @param n objekt tridy Normal.
	 */
	Vector(const Normal& n)
		: x(n.x), y(n.y), z(n.z)
	{
	}

	/**
	 * Vypocet delky vektoru.
	 * @return delka vektoru.
	 */
	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	/**
	 * Vypocet druhe mocniny delky vektoru
	 * @return delka na druhou.
	 */
	float SquarredLenght() const
	{
		return x * x + y * y + z * z;
	}

	/**
	 * Normalizuje dany vektor. Vyuzito fluent interface.
	 * @return normalizovany vektor.
	 */
	Vector Normalize()
	{
		float lengthInv = 1.f / Length();

		x *= lengthInv;
		y *= lengthInv;
		z *= lengthInv;

		return *this;
	}

	/**
	 * Pretizeni unarniho operatoru +.
	 * @return hodnotu objektu (Vector).
	 */
	const Vector& operator+() const
	{
		return *this;
	}

	/**
	 * Pretizeni unarniho operatoru -.
	 * @return novy objekt tridy Vector
	 */
	Vector operator-() const
	{
		return Vector(-x, -y, -z);
	}

	/**
	 * Pretizeni operatoru rovnosti (==).
	 * Porovnavaji se jednotlive slozky.
	 * @param v objekt tridy vektor, se kterym porovnavame.
	 * @return true/false
	 */
	bool operator ==(const Vector& v)
	{
		return x == v.x && y == v.y && z == v.z;
	}

	/**
	 * Pretizeni operatoru nerovnosti (!=)
	 * Porovnavaji se jednotlive slozky.
	 * @param v objekt tridy vektor, se kterym porovnavame.
	 * @return true/false
	 */
	bool operator !=(const Vector& v)
	{
		return x != v.x || y != v.y || z != v.z;
	}

	/**
	 * Pretizeni operatoru scitani (+).
	 * Scitaji se jednotlive slozky.
	 * @param v objekt tridy Vector, ktery chceme pricist
	 * @return novy objekt typu Vector
	 */
	Vector operator +(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	/**
	 * Pretizeni operatoru +=
	 * Scitaji se jednotlive slozky.
	 * @return reference na this
	 */
	Vector& operator +=(const Vector& v)
	{
		*this = *this + v;
		return *this;
	}

	/**
	 * Pretizeni operatoru odcitani (-).
	 * Odcitaji se jednotlive slozky.
	 * @param v objekt tridy Vector, ktery chceme odecist
	 * @return novy objekt typu Vector
	 */
	Vector operator -(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	/**
	 * Pretizeni operatoru -=
	 * Odcitaji se jednotlive slozky.
	 * @return reference na this
	 */
	Vector& operator -=(const Vector& v)
	{
		*this = *this - v;
		return *this;
	}

	/**
	 * Pretizeni operatoru deleni (/).
	 * Osetreno deleni 0 pomoci makra assert z <assert.h>.
	 * @see assert()
	 * @param k hodnota kterou chceme delit vsechny slozky.
	 * @return novy objekt tridy Vector
	 */
	Vector operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return Vector(x * invK, y * invK, z * invK);
	}

	/**
	 * Pretizeni operatoru deleni (/=).
	 * Osetreno deleni 0 pomoci makra assert z <assert.h>.
	 * @see assert()
	 * @param k hodnota kterou chceme delit vsechny slozky.
	 * @return reference na this
	 */
	Vector& operator /=(float k)
	{
		assert(k != 0);
		float invK = 1.f / k;

		x *= invK;
		y *= invK;
		z *= invK;

		return *this;
	}

	/**
	 * Pretizeni operatoru nasobeni (*).
	 * Nasobime vsechny slozky konstantou.
	 * @param k konstanta pro nasobeni.
	 * @return novy objekt typu Vector
	 */
	Vector operator *(float k) const
	{
		return Vector(x * k, y * k, z * k);
	}

	/**
	 * Pretizeni operatoru nasobeni (*).
	 * Nasobime vsechny slozky konstantou zleva.
	 * @param k konstanta pro nasobeni.
	 * @param v vektor, ktery chceme nasobit.
	 * @return novy objekt typu Vector
	 */
	friend Vector operator *(float k, const Vector& v)
	{
		return Vector(v.x * k, v.y * k, v.z * k);
	}

	/**
	 * Pretizeni operatoru nasobeni (*).
	 * Nasobime vsechny slozky konstantou.
	 * @param k konstanta pro nasobeni.
	 * @return reference na this
	 */
	Vector& operator *=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	/**
	 * Pretizeni operatoru prirazeni (=).
	 * @param v vektor, jehoz hodnotu chceme priradit.
	 * @return reference na this
	 */
	Vector& operator =(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	/**
	 * Pretizeni operatoru pro pristup do pole ([]).
	 * Pomoci makra assert z <assert.h> osetren rozsah v intervalu (0; 2).
	 * Vyuzito vlastnosti, ze prekladace radi promenne "za sebe", takze lze k nim pristupovat jako k poli.
	 * @param i index v intervalu (0; 2).
	 * @return hodnotu x resp. y,z dle vstupniho parametru.
	 */
	float operator[](int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	/**
	 * Pretizeni operatoru pro pristup do pole ([]).
	 * Pomoci makra assert z <assert.h> osetren rozsah v intervalu (0; 2).
	 * Vyuzito vlastnosti, ze prekladace radi promenne "za sebe", takze lze k nim pristupovat jako k poli.
	 * @param i index v intervalu (0; 2).
	 * @return hodnotu x resp. y,z dle vstupniho parametru.
	 */
	float& operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	/** hodnota slozky x */
	float x;
	/** hodnota slozky y */
	float y;
	/** hodnota slozky z */
	float z;
};

class Point
{
public:
	Point()
			: x(0.f), y(0.f), z(0.f)
	{
	}

	Point(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
	{
	}

	Point(const Point& p)
			: x(p.x), y(p.y), z(p.z)
	{
	}

	~Point()
	{
	}

	const Point& operator+() const
	{
		return *this;
	}

	Point operator-() const
	{
		return Point(-x, -y, -z);
	}

	bool operator ==(const Vector& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator !=(const Vector& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	Point operator +(const Vector& v) const
	{
		return Point(x + v.x, y + v.y, z + v.z);
	}

	Point operator +(const Point& v) const
	{
		return Point(x + v.x, y + v.y, z + v.z);
	}

	Point& operator +=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector operator -(const Point& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Point operator -(const Vector& v) const
	{
		return Point(x - v.x, y - v.y, z - v.z);
	}

	Point operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return Point(x * invK, y * invK, z * invK);
	}

	Point& operator /=(float k)
	{
		assert(k != 0);
		float invK = 1.f / k;

		x *= invK;
		y *= invK;
		z *= invK;

		return *this;
	}

	Point operator *(float k) const
	{
		return Point(x * k, y * k, z * k);
	}

	friend Point operator *(float k, const Point& v)
	{
		return Point(v.x * k, v.y * k, v.z * k);
	}

	Point& operator *=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	float operator[](int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float& operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	/** hodnota slozky x */
	float x;
	/** hodnota slozky y */
	float y;
	/** hodnota slozky z */
	float z;
};

class Normal
{
public:
	Normal()
	{
		x = y = z = 0.f;
	}
	Normal(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
	{
	}
	Normal(const Normal& v)
			: x(v.x), y(v.y), z(v.z)
	{
	}
	Normal(const Point& p)
			: x(p.x), y(p.y), z(p.z)
	{
	}
	Normal(const Vector& p)
			: x(p.x), y(p.y), z(p.z)
	{
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float SquarredLenght() const
	{
		return x * x + y * y + z * z;
	}

	Normal Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	const Normal& operator+() const
	{
		return *this;
	}
	Normal operator-() const
	{
		return Normal(-x, -y, -z);
	}

	bool operator ==(const Normal& v)
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator !=(const Normal& v)
	{
		return x != v.x || y != v.y || z != v.z;
	}

	Normal operator +(const Normal& v) const
	{
		return Normal(x + v.x, y + v.y, z + v.z);
	}

	Normal& operator +=(const Normal& v)
	{
		*this = *this + v;
		return *this;
	}

	Normal operator -(const Normal& v) const
	{
		return Normal(x - v.x, y - v.y, z - v.z);
	}

	Normal& operator -=(const Normal& v)
	{
		*this = *this - v;
		return *this;
	}

	Normal operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return Normal(x * invK, y * invK, z * invK);
	}

	Normal& operator /=(float k)
	{
		assert(k != 0);
		float invK = 1.f / k;

		x *= invK;
		y *= invK;
		z *= invK;

		return *this;
	}

	Normal operator *(float k) const
	{
		return Normal(x * k, y * k, z * k);
	}

	friend Normal operator *(float k, const Normal& v)
	{
		return Normal(v.x * k, v.y * k, v.z * k);
	}

	Normal& operator *=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	Normal& operator =(const Normal& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	float operator[](int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float& operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float x;
	float y;
	float z;
};

class Ray
{
public:
	Ray()
			: mint(0.f), maxt(INFINITY), rayEpsilon(EPSILON), depth(0)
	{
	}
	Ray(const Point& _o, const Vector& _d, float start = 0.f, float end =
	INFINITY, float eps = EPSILON, int _depth = 0)
			: o(_o), d(_d), mint(start), maxt(end), rayEpsilon(eps), depth(
					_depth)
	{
	}

	Point operator()(float t) const
	{
		return o + d * t;
	}

	Point o;
	Vector d;
	mutable float mint, maxt;
	mutable float rayEpsilon;
	int depth;
};

class BBox
{
public:
	BBox()
	{
		pMin = Point(INFINITY, INFINITY, INFINITY);
		pMax = Point(-INFINITY, -INFINITY, -INFINITY);
	}

	BBox(const Point& p)
		: pMin(p), pMax(p)
	{}

	BBox(const Point& _pmin, const Point& _pmax)
		: pMin(_pmin), pMax(_pmax)
	{}

	BBox(const BBox& b)
		: pMin(b.pMin), pMax(b.pMax)
	{}

	bool IsInside(const Point& p)
	{
		return (p.x >= pMin.x && p.x <= pMax.x &&
				p.y >= pMin.y && p.y <= pMax.y &&
				p.z >= pMin.z && p.z <= pMax.z);
	}

	bool IsOverlaps(const BBox& b)
	{
		bool x = (pMax.x >= b.pMin.x && pMin.x <= b.pMax.x);
		bool y = (pMax.y >= b.pMin.y && pMin.y <= b.pMax.y);
		bool z = (pMax.z >= b.pMin.z && pMin.z <= b.pMax.z);
		return (x && y && z);
	}

	friend BBox Union(const BBox& b, const Point& p);
	friend BBox Union(const BBox& b, const BBox& b2);

	bool IntersectP(const Ray& ray, float* hitt0, float* hitt1) const;

	Point Lerp(float tx, float ty, float tz) const
	{
		return Point(::Lerp(tx, pMin.x, pMax.x),
				::Lerp(ty, pMin.y, pMax.y),
				::Lerp(tz, pMin.z, pMax.z));
	}

	Point pMin, pMax;
};

inline float Dot(const Vector& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline float Dot(const Vector& u, const Normal& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline float Dot(const Normal& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline float Dot(const Normal& u, const Normal& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline Vector Cross(const Vector& u, const Vector& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

inline Vector Cross(const Normal& u, const Vector& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

inline Vector Cross(const Normal& u, const Normal& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

inline Vector Cross(const Vector& u, const Normal& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

inline float Distance(const Point& p1, const Point& p2)
{
	Vector v(p1 - p2);
	return v.Length();
}
