#pragma once
#include "../../DGenericLib/Vector3.h"
#include "../../DGenericLib/Quaternion.h"
class Transform { 
public:	
	DGeneric::Vector3 position;
	DGeneric::Vector3 scale;
	DGeneric::Quaternion rotation;
};