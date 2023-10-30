#pragma once

namespace DLogic
{
	class IUpdatable
	{
		virtual void OnUpdate(float _delta_time) = 0;
	};
}