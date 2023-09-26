#pragma once
#include "dl_pch.h"
#include "Framework/GameObject.h"
namespace DLogic {
	class GameObjectManager
	{
	public:
		void AddGameObject(GameObject* _game_object);
		void RemoveGameObject(GameObject* _game_object);
	private:
		DGeneric::Vector<GameObject*> m_game_objects;

	};
}
