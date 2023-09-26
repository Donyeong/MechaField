module;
#include "pch.h"
#include "Math.h"
export module DGeneric:Vector3;

export class Vector3 {
public:
	Vector3() : Vector3(0, 0, 0) { ; }
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { ; }
	~Vector3() = default;

	inline void Set(float _x, float _y, float _z);

	inline void SetNormalizaion();
	inline Vector3 GetNormal();
	inline float GetMagnitude();
	inline float GetSqrtMagnitude();

	static Vector3 CrossProduct(Vector3 v1, Vector3 v2);
	inline Vector3 operator=(Vector3 vec);
	inline bool operator==(Vector3 vec);
	inline bool operator!=(Vector3 vec);
	inline Vector3 operator+(const Vector3 vec) const;
	inline Vector3 operator-(Vector3 vec);
	inline float operator*(Vector3 vec);
	inline Vector3 operator*(float n);
	//inline Vector3 operator*(float n);
	inline Vector3 operator/(float n);
	inline Vector3 operator+=(Vector3 vec);
	inline Vector3 operator-=(Vector3 vec);
	inline Vector3 operator*=(float n);
	inline Vector3 operator/=(float n);
	inline float& operator[](int i);
	//std::ostream& operator<<(std::ostream& os, const Vector3 vec);

public:
	float x, y, z;
};


inline void Vector3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}
void Vector3::SetNormalizaion()
{
	*this /= GetMagnitude();
}

Vector3 Vector3::GetNormal()
{
	return *this / GetMagnitude();
}

float Vector3::GetMagnitude()
{
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::GetSqrtMagnitude()
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::CrossProduct(Vector3 a, Vector3 b)
{
	return (Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}


Vector3 Vector3::operator=(Vector3 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}

bool Vector3::operator==(Vector3 vec)
{
	return (vec.x == x && vec.y == y && vec.z == z);
}

bool Vector3::operator!=(Vector3 vec)
{
	return (vec.x != x || vec.y != y || vec.z != z);
}

inline Vector3 Vector3::operator+(const Vector3 vec) const
{
	return Vector3(vec.x + x, vec.y + y, vec.z + z);
}
Vector3 Vector3::operator-(Vector3 vec)
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

float Vector3::operator*(Vector3 vec)
{
	return x * vec.x + y * vec.y + z * vec.z;
}


Vector3 Vector3::operator*(float n)
{
	return Vector3(x * n, y * n, z * n);
}

Vector3 Vector3::operator/(float n)
{
	return Vector3(x / n, y / n, z / n);
}

Vector3 Vector3::operator+=(Vector3 vec)
{
	(*this) = (*this) + vec;
	return *this;
}

Vector3 Vector3::operator-=(Vector3 vec)
{
	(*this) = (*this) - vec;
	return *this;
}

Vector3 Vector3::operator*=(float n)
{
	(*this) = (*this) * n;
	return *this;
}

Vector3 Vector3::operator/=(float n)
{
	(*this) = (*this) / n;
	return *this;
}

float& Vector3::operator[](int i)
{
	switch (i%3)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	DASSERT(false);
	return x;
}