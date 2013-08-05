#pragma once

#include <cmath>
#include <assert.h>

#include "core.h"
#include "constants.h"

class Vector
{
public:
	//ctors
	Vector()
	{
		x = y = z = 0.f;
	}
	Vector(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z)
	{
	}
	Vector(const Vector& v)
			: x(v.x), y(v.y), z(v.z)
	{
	}
	Vector(const Point& p);
	Vector(const Normal& p);

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float SquarredLenght() const
	{
		return x * x + y * y + z * z;
	}

	Vector Normalize()
	{
		float lengthInv = 1.f / Length();

		x *= lengthInv;
		y *= lengthInv;
		z *= lengthInv;

		return *this;
	}

	const Vector& operator+() const
	{
		return *this;
	}
	Vector operator-() const
	{
		return Vector(-x, -y, -z);
	}

	bool operator ==(const Vector& v)
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator !=(const Vector& v)
	{
		return x != v.x || y != v.y || z != v.z;
	}

	Vector operator +(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector& operator +=(const Vector& v)
	{
		*this = *this + v;
		return *this;
	}

	Vector operator -(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	Vector& operator -=(const Vector& v)
	{
		*this = *this - v;
		return *this;
	}

	Vector operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return Vector(x * invK, y * invK, z * invK);
	}

	Vector& operator /=(float k)
	{
		assert(k != 0);
		float invK = 1.f / k;

		x *= invK;
		y *= invK;
		z *= invK;

		return *this;
	}

	Vector operator *(float k) const
	{
		return Vector(x * k, y * k, z * k);
	}

	friend Vector operator *(float k, const Vector& v)
	{
		return Vector(v.x * k, v.y * k, v.z * k);
	}

	Vector& operator *=(float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	Vector& operator =(const Vector& v)
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

	float x;
	float y;
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

inline Vector::Vector(const Point& p)
		: x(p.x), y(p.y), z(p.z)
{
}
inline Vector::Vector(const Normal& p)
		: x(p.x), y(p.y), z(p.z)
{
}

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
