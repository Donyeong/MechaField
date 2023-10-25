#pragma once
#include "GameCore.h"
namespace DLogic {
	class LogicMain
	{
	public:
		void Init();
		void Start();
		void Update(float _delta_time);
		const GameCore& getGameCore() {
			return game_core;
		}
	private:
		GameCore game_core;
	};
}