class Vector
{
public:
    //ctors
    Vector() { x = y = z = 0.f; }
    Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
    Vector(const Vector& v)
		: x(v.x), y(v.y), z(v.z) { }
	Vector(const Point& p)
		: x(p.x), y(p.y), z(p.z) { }
	Vector(const Normal& p)
		: x(p.x), y(p.y), z(p.z) { }

	float Length() const { return sqrt(x*x + y*y + z*z); }

    float SquarredLenght() const { return x*x + y*y + z*z;}

    Vector Normalize()
    {
        float lengthInv = 1.f / Length();

        x *= lengthInv;
        y *= lengthInv;
        z *= lengthInv;

        return *this;
    }

	const Vector& operator+() const { return *this; }
    Vector operator-() const { return Vector(-x, -y, -z); }

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

	float operator[] (int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float& operator[] (int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}
    
	float x;
	float y;
	float z;
};