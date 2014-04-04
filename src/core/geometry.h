/**
 * @file
 */

#pragma once

#include <cmath>
#include <assert.h>

#include "core.h"
#include "constants.h"

/**
 * Trida trojrozmerneho vektoru.\n
 * Umoznuje provadet s vektorem základní matematické operace jako scitani,
 * odcitani, nasobeni konstantou, deleni konstantou, zjistovat jeho delku
 * a provadet jeho normalizaci.
 * @author Pavel Lokvenc
 */
class Vector
{
public:

	/**
	 * Defaultni konstruktor. \n
	 * Vsechny slozky maji hodnotu 0.
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
	Vector(const Point& p);

	/**
	 * Konstruktor pro vytvoreni vektoru z objektu Normal.
	 * Prislusne souradnice objektu tridy Normal se priradi novemu objektu tridy Vector.
	 * @param n objekt tridy Normal.
	 */
	Vector(const Normal& n);

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

	/** hodnota slozky vektoru x */
	float x;
	/** hodnota slozky vektoru y */
	float y;
	/** hodnota slozky vektoru z */
	float z;
};

/**
 * Trida predstavujici bod ve trojrozmernem prostoru.\n
 * Prestoze by se dala pouzit trida Vector, je zde pouzito specialni tridy pro
 * prehlednost a pro dodrzeni zazitych konvenci znamych z matematiky a
 * lin. algebry (bod - bod = vektor, bod + vektor = bod).
 * @author Pavel Lokvenc
 */
class Point
{
public:
	/**
	 * Defaultni konstruktor. \n
	 * Vsechny slozky maji hodnotu 0.
	 */
	Point()
			: x(0.f), y(0.f), z(0.f)
	{
	}

	/**
	 * Konstruktor
	 * @param _x hodnota slozky x
	 * @param _y hodnota slozky y
	 * @param _z hodnota slozky z
	 */
	Point(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
	{
	}

	/**
	 * Kopirovaci konstruktor
	 * @param p Point urceny ke kopirovani
	 */
	Point(const Point& p)
			: x(p.x), y(p.y), z(p.z)
	{
	}

	~Point()
	{
	}

	/**
	 * Pretizeni unarniho operatoru +.
	 * @return referenci na this.
	 */
	const Point& operator+() const
	{
		return *this;
	}

	/**
	 * Pretizeni unarniho operatoru -. Vraci bod se zapornymi slozkami.
	 * @return novy objekt tridy Point
	 */
	Point operator-() const
	{
		return Point(-x, -y, -z);
	}

	/**
	 * Pretizeni operatoru rovnosti (==).
	 * Porovnavaji se jednotlive slozky.
	 * @param v objekt tridy Point, se kterym porovnavame.
	 * @return true/false
	 */
	bool operator ==(const Vector& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	/**
	 * Pretizeni operatoru nerovnosti (!=)
	 * Porovnavaji se jednotlive slozky.
	 * @param v objekt tridy Point, se kterym porovnavame.
	 * @return true/false
	 */
	bool operator !=(const Vector& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	/**
	 * Pretizeni operatoru scitani (+).
	 * Posun bodu o vektor v. Scitaji se jednotlive slozky.
	 * @param v objekt tridy Vector, ktery chceme pricist
	 * @return novy objekt typu Point
	 */
	Point operator +(const Vector& v) const
	{
		return Point(x + v.x, y + v.y, z + v.z);
	}

	/**
	 * Pretizeni operatoru scitani (+).
	 * Scitaji se jednotlive slozky.
	 * @param v objekt tridy Vector, ktery chceme pricist
	 * @return novy objekt typu Vector
	 */
	Point operator +(const Point& v) const
	{
		return Point(x + v.x, y + v.y, z + v.z);
	}

	/**
	 * @see operator +(const Vector& v)
	 */
	Point& operator +=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	/**
	 * @see operator +(const Point& v)
	 */
	Point& operator +=(const Point& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}

	/**
	 * Operace odcitani dvou objektu Point. Abychom dostali spravne smerovany
	 * vektor je treba odecitat KONCOVY bod od POCATECNIHO.
	 * @param p pocateni bod
	 * @return vektor mezi dvema zadanymi body
	 */
	Vector operator -(const Point& p) const
	{
		return Vector(x - p.x, y - p.y, z - p.z);
	}

	/**
	 * Operace posun bodu v zapornem smeru vektoru. Neni diky tomu nutne psat
	 * komplikovane \f$ p + (-v) \f$.
	 * @param v vektor o ktery chceme presunout bod
	 * @return Point posunuty v zapornem smeru vektoru
	 */
	Point operator -(const Vector& v) const
	{
		return Point(x - v.x, y - v.y, z - v.z);
	}

	/**
	 * Pretizeni operatoru deleni (/).
	 * Osetreno deleni 0 pomoci makra assert z <assert.h>.
	 * @see assert()
	 * @param k hodnota kterou chceme delit vsechny slozky.
	 * @return novy objekt tridy Point
	 */
	Point operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return Point(x * invK, y * invK, z * invK);
	}

	/**
	 * Pretizeni operatoru deleni (/).
	 * Osetreno deleni 0 pomoci makra assert z <assert.h>.
	 * @see assert()
	 * @param k hodnota kterou chceme delit vsechny slozky.
	 * @return reference na this
	 */
	Point& operator /=(float k)
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
	Point operator *(float k) const
	{
		return Point(x * k, y * k, z * k);
	}

	/**
	 * Pretizeni operatoru nasobeni (*).
	 * Nasobime vsechny slozky konstantou.
	 * @param k konstanta pro nasobeni.
	 * @return novy objekt typu Point
	 */
	friend Point operator *(float k, const Point& v)
	{
		return Point(v.x * k, v.y * k, v.z * k);
	}

	/**
	 * Pretizeni operatoru nasobeni (*).
	 * Nasobime vsechny slozky konstantou.
	 * @param k konstanta pro nasobeni.
	 * @return novy objekt typu Vector
	 */
	Point& operator *=(float k)
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
	Point& operator =(const Point& v)
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

/**
 * Třída reprezentuje normálu v prostoru.\n
 * Vlastnosti jsou stejné jako u třídy Vector, je dokonce možné mezi nimi převádět.
 * Třída je zde pouze ze sémantických důvodu.
 * @see Vector
 */
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
	Normal(const Normal& n)
			: x(n.x), y(n.y), z(n.z)
	{
	}
	Normal(const Point& p)
			: x(p.x), y(p.y), z(p.z)
	{
	}
	Normal(const Vector& v)
			: x(v.x), y(v.y), z(v.z)
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

	bool operator ==(const Normal& n)
	{
		return x == n.x && y == n.y && z == n.z;
	}

	bool operator !=(const Normal& n)
	{
		return x != n.x || y != n.y || z != n.z;
	}

	Normal operator +(const Normal& n) const
	{
		return Normal(x + n.x, y + n.y, z + n.z);
	}

	Normal& operator +=(const Normal& n)
	{
		*this = *this + n;
		return *this;
	}

	Normal operator -(const Normal& n) const
	{
		return Normal(x - n.x, y - n.y, z - n.z);
	}

	Normal& operator -=(const Normal& n)
	{
		*this = *this - n;
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

	friend Normal operator *(float k, const Normal& n)
	{
		return Normal(n.x * k, n.y * k, n.z * k);
	}

	Normal& operator *=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	Normal& operator =(const Normal& n)
	{
		x = n.x;
		y = n.y;
		z = n.z;
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

/**
 * Třída reprezentuje parpsek(polopřímku) v prostoru.\n
 * Vychází z parametrické rovnice přímky.
 */
class Ray
{
public:
	/**
	 * Bezparametrický konstruktor.
	 */
	Ray()
			: mint(0.f), maxt(INFINITY), rayEpsilon(EPSILON), depth(0)
	{}

	/**
	 * Konstruktor
	 * @param _o počátek paprsku
	 * @param _d směr paprsku
	 * @param start minimální hodnota parametru t
	 * @param end maximální hodnota parametru t
	 * @param eps hodnota epsilon pro eliminaci chyb při výpočtech s desetinnou čárkou
	 * @param _depth hloubka rekurze
	 */
	Ray(const Point& _o, const Vector& _d, float start = 0.f, float end =
	INFINITY, float eps = EPSILON, int _depth = 0)
			: o(_o), d(_d), mint(start), maxt(end), rayEpsilon(eps), depth(_depth)
	{}

	/**
	 * Pro zadaný parametr t vypočítá bod na polopřímce.
	 * Použití: Ray r; r(0.568);
	 * @param t hodnota parametru
	 */
	Point operator()(float t) const
	{
		return o + d * t;
	}

	Point o; ///< pocatek paprsku
	Vector d; ///< smer paprsku
	mutable float mint; ///< minimalni hodnota parametru t
	mutable float maxt; ///< maximalni hodnota parametru t
	mutable float rayEpsilon; ///< vypocitane epsilon (zamezuje vzniku artefaktu)
	mutable int depth; ///< hloubka rekurze
};

/**
 * Třída reprezentuje obalový kvádr, jehož stěny jsou rovnoběžné s osami světových souřadnic.
 */
class BBox
{
public:
	/**
	 * Bezparametrický konstruktor.\n
	 * pMin má všechny složky definované na INFINITY a pmax na -INFINITY
	 * z důvodu snadnějšího slučování s jinými BBox.
	 */
	BBox()
	{
		pMin = Point(INFINITY, INFINITY, INFINITY);
		pMax = Point(-INFINITY, -INFINITY, -INFINITY);
	}

	/**
	 * Konstruktor definovaný pomocí jednoho bodu. Vloží jeho hodnotu do pMin a pMax.
	 * @param p bod
	 */
	BBox(const Point& p)
		: pMin(p), pMax(p)
	{}

	/**
	 * Konstruktor definující BBox pomocí dvou bodů.
	 * Do pMin se vloží minimální složky a do pMax maximální složky z obou bodů.
	 * @param p1 reference na první bod
	 * @param p2 reference na druhý bod
	 */
	BBox(const Point& p1, const Point& p2)
	{
		pMin = Point(Min(p1.x, p2.x), Min(p1.y, p2.y), Min(p1.z, p2.z));
		pMax = Point(Max(p1.x, p2.x), Max(p1.y, p2.y), Max(p1.z, p2.z));
	}

	/**
	 * Kopírovací konstruktor.
	 */
	BBox(const BBox& b)
		: pMin(b.pMin), pMax(b.pMax)
	{}

	/**
	 * Kontroluje, jestli bod leží uvnitř BBox.
	 * @param p kontrolovaný bod
	 * @return jestli bod leží uvnitř obalové BBox
	 */
	bool IsInside(const Point& p) const
	{
		return (p.x >= pMin.x && p.x <= pMax.x &&
				p.y >= pMin.y && p.y <= pMax.y &&
				p.z >= pMin.z && p.z <= pMax.z);
	}

	/**
	 * Kontrolu, jestli dochází k překrytí dvou BBox.
	 * @param b kontrolovaný BBox
	 * @return jestli se dvě BBox překrývají
	 */
	bool IsOverlaps(const BBox& b) const
	{
		bool x = (pMax.x >= b.pMin.x && pMin.x <= b.pMax.x);
		bool y = (pMax.y >= b.pMin.y && pMin.y <= b.pMax.y);
		bool z = (pMax.z >= b.pMin.z && pMin.z <= b.pMax.z);
		return (x && y && z);
	}

	/**
	 * Vypočítá diagonálu BBox.
	 ** @return Vector představující diagonálu
	 */
	Vector Diagonal() const
	{
		return pMax - pMin;
	}

	/**
	 * Zjišťuje, ve které ose je BBox nejrozměrnější.
	 * @return číslo osy (0 - x, 1 - y, 2 - z)
	 */
	int MaxDimensionIndex() const
	{
		Vector diag = Diagonal();
		if (diag.x > diag.y && diag.x > diag.z)
			return 0;
		else if (diag.y > diag.z)
			return 1;
		else
			return 2;
	}

	/**
	 * Metoda vypočítá střed (centroid) BBox.
	 * @return Point reprezentující střed BBox
	 */
	Point Centroid() const
	{
		return (pMin + pMax) / 2.f;
	}

	/**
	 * Provede sjednocení BBox a bodu.
	 * @param b instance třídy BBox
	 * @param p instance třídy Point
	 * @return BBox vzniknutý sjednocením
	 */
	friend BBox Union(const BBox& b, const Point& p);
	
	/**
	 * Provede sjednocení BBox a bodu.
	 * @param b instance třídy BBox
	 * @param b2 instance třídy BBox
	 * @return BBox vzniknutý sjednocením
	 */
	friend BBox Union(const BBox& b, const BBox& b2);

	/**
	 * Zjistí, jestli existuje průsečík přímky a BBox.
	 * Je také možné získat hodnoty parametrů t.
	 * @param ray paprsek
	 * @param hitt0 slouží k uložení hodnoty prvního parametru průsečíku t
	 * @param hitt1 slouží k uložení hodnoty druhého parametru průsečíku t
	 * @return zdali průsečík protnul BBox
	 */
	bool IntersectP(const Ray& ray, float* hitt0, float* hitt1) const;

	/**
	 * Lineární interpolace uvnitř BBox mezi body pMin a pMax.
	 */
	Point Lerp(float tx, float ty, float tz) const
	{
		return Point(::Lerp(tx, pMin.x, pMax.x),
				::Lerp(ty, pMin.y, pMax.y),
				::Lerp(tz, pMin.z, pMax.z));
	}

	Point operator[](int i) const
	{
		assert(i >= 0 && i <= 1);
		return (&pMin)[i];
	}

	Point& operator[](int i)
	{
		assert(i >= 0 && i <= 2);
		return (&pMin)[i];
	}

	Point pMin; ///< bod s nejmenšími složkami
	Point pMax; ///< bod s největšími složkami
};

inline Vector::Vector(const Point& p)
	: x(p.x), y(p.y), z(p.z)
{
}

inline Vector::Vector(const Normal& n)
	: x(n.x), y(n.y), z(n.z)
{
}

/**
 * Skalárni součin dvou vektorů.
 */
inline float Dot(const Vector& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

/**
 * Skalárni součin dvou vektorů.
 */
inline float Dot(const Vector& u, const Normal& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

/**
 * Skalárni součin dvou vektorů.
 */
inline float Dot(const Normal& u, const Vector& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

/**
 * Skalárni součin dvou vektorů.
 */
inline float Dot(const Normal& u, const Normal& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

/**
 * Vektorový součin dvou vektorů.
 */
inline Vector Cross(const Vector& u, const Vector& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

/**
 * Vektorový součin dvou vektorů.
 */
inline Vector Cross(const Normal& u, const Vector& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

/**
 * Vektorový součin dvou vektorů.
 */
inline Vector Cross(const Normal& u, const Normal& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

/**
 * Vektorový součin dvou vektorů.
 */
inline Vector Cross(const Vector& u, const Normal& v)
{
	return Vector(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
}

/**
 * Vzdálenost dvou bodů.
 */
inline float Distance(const Point& p1, const Point& p2)
{
	Vector v(p1 - p2);
	return v.Length();
}