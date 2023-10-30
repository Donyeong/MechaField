#pragma once
#include "../../DGenericLib/Vector3.h"
#include "../../DGenericLib/Quaternion.h"
class Transform { 
public:	
	Transform() = default;
	DGeneric::Vector3 position;
	DGeneric::Vector3 scale;
	DGeneric::Quaternion rotation;
};