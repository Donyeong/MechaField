#include "DGameMode_Lobby.h"
#include "Framework/Scene.h"
namespace DLogic {
	void DGameMode_Lobby::OnLoad()
	{
		DGameMode::OnLoad();

		Scene& scene = GetScene();
		scene.CreateGameObject();
	}
}