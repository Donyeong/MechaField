#pragma once
#include <math.h>
namespace DMath {
	const float PI = 3.14159265359;

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
	static float Clamp(float a, float min, float max)
	{
		return Min(Max(a, min), max);
	}

	static float reciprocal(float n)
	{
		return 1/ n;
	}
	static float reciprocal_squareroot(float n) {

		const float threehalfs = 1.5F;
		float y = n;

		long i = *(long*)&y;

		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;

		y = y * (threehalfs - ((n * 0.5F) * y * y));

		return y;
	}
}