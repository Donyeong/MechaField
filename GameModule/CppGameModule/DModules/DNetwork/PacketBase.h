#pragma once
#include "Serializer.h"
class PacketBase
{
public:
	PacketBase()
	{

	}
	virtual Serializer Serialize() = 0;
	virtual void Deserialize(Serializer _serializer) = 0;
};

