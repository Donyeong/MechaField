#pragma once
#include "LogicMain.h"

//#pragma comment(lib,"DPhysics/DPhysics.lib")
//#include "../../DPhysics/DPhysics.h"
#include "../DConfig.h"
namespace DLogic {
	void LogicMain::Init()
	{
	}

	void LogicMain::Start()
	{
		DLOG_INFO("Start LogicMain");
		game_core.Start();
	}
	void LogicMain::Update(float _delta_time)
	{
		//DLOG_INFO("Update LogicMain");
		game_core.Update(_delta_time);
	}
}