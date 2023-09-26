#pragma once

namespace DLogic
{
	class ICommand
	{
	public:
		virtual void handle() = 0;
	};
}