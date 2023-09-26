#include "LogicMain.h"

#pragma comment(lib,"DPhysics/DPhysics.lib")
#include "../../DPhysics/DPhysics.h"
#include "../DConfig.h"
#include "GameCore.h"
namespace DLogic {
	void LogicMain::Init()
	{
	}

	void LogicMain::Start()
	{
		GameCore game_core;

		//DPhysics phys;
		//phys.Init();
		//phys.Init();
		while (true) {
			//phys.Update(1.0f / 60.0f);
		}
	}
}