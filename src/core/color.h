#pragma once

#include <cmath>
#include <assert.h>

#include "core.h"

class RGBColor
{
public:
	RGBColor() {r = g = b = 0.f;}
	RGBColor(float _r, float _g, float _b)
		: r(_r), g(_g), b(_b) { }
	RGBColor(const RGBColor& c)
		: r(c.r), g(c.g), b(c.b) { }
	~RGBColor() { }

	const RGBColor& operator+() const { return *this; }
	RGBColor operator-() const { return RGBColor(-r, -g, -b); }

	bool operator ==(const RGBColor& v)
	{
		return r == v.r && g == v.g && b == v.b;
	}

	bool operator !=(const RGBColor& v)
	{
		return r != v.r || g != v.g || b != v.b;
	}

	RGBColor operator +(const RGBColor& v) const
	{
		return RGBColor(r + v.r, g + v.g, b + v.b);
	}

	RGBColor& operator +=(const RGBColor& v)
	{
		*this = *this + v;
		return *this;
	}

	RGBColor operator -(const RGBColor& v) const
	{
		return RGBColor(r - v.r, g - v.g, b - v.b);
	}

	RGBColor& operator -=(const RGBColor& v)
	{
		*this = *this - v;
		return *this;
	}

	RGBColor operator /(float k) const
	{
		assert(k != 0);
		float invK = 1.f / k;
		return RGBColor(r * invK, g * invK, b * invK);
	}

	RGBColor& operator /=(float k)
	{
		assert(k != 0);
		float invK = 1.f / k;

		r *= invK;
		g *= invK;
		b *= invK;

		return *this;
	}

	RGBColor operator *(float k) const
	{
		return RGBColor(r * k, g * k, b * k);
	}

	RGBColor operator *(const RGBColor& k) const
	{
		return RGBColor(r * k.r, g * k.g, b * k.b);
	}

	RGBColor& operator *=(float k)
	{
		r *= k;
		g *= k;
		b *= k;
		return *this;
	}

	friend RGBColor operator *(float k, const RGBColor& c)
	{
		return RGBColor(c.r * k, c.g * k, c.b * k);
	}

	RGBColor& operator =(const RGBColor& v)
	{
		r = v.r;
		g = v.g;
		b = v.b;
		return *this;
	}

	void Pow(float c)
	{
		r = powf(r, c);
		g = powf(g, c);
		b = powf(b, c);
	}

	RGBColor Clamp(float from = 0.f, float to = 1.0)
	{
		RGBColor out;

		out.r = ::Clamp(r, from, to);
		out.g = ::Clamp(g, from, to);
		out.b = ::Clamp(b, from, to);

		return out;
	}

	//data
	float r, g, b;
};

const RGBColor BLACK(0.f,0.f,0.f);