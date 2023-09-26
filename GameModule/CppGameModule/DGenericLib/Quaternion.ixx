module;
#include "pch.h"
#include "Math.h"
export module DGeneric:Quaternion;
import :Vector3;

export class Quaternion {
public:
	Quaternion() = default;
	~Quaternion() = default;
public:
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};

		struct {
			Vector3 u;
		};
	};
};