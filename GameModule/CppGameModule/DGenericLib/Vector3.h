#pragma once
#include "pch.h"
#include "String.h"


namespace DGeneric
{
	class Vector3 {
	public:
		Vector3() : Vector3(0, 0, 0) {;}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {;}
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

		String ToString();

	public:
		float x, y, z;
	};
}