#pragma once
#include "dl_pch.h"
#include "Framework/Scene.h"
namespace DLogic
{
	class GameEvent
	{
		Scene* scene;
	public:
		virtual DGeneric::String GetEventType() = 0;
	};

	class TestEvent
	{
		Scene* scene;
	public:
		virtual DGeneric::String GetEventType() {

		}
	};
}
