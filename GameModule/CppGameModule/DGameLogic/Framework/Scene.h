#pragma once
#include "../dl_pch.h"
#include "../GameObjectManager.h"
class GameObjectSyncronizer;
class GameCore;
namespace DLogic
{
	class Scene {
		OBJECT_POOLING(Scene)
	public:
		Scene() {
			Init();
		}
		GameCore* GetGameCore() {
			return m_owner_game_core;
		}

		GameObject* CreateGameObject() {
			return CreateGameObject(root);
		}

		GameObject* CreateGameObject(GameObject* _parent) {
			GameObject* new_obj = game_object_pool.AllocObject();
			new_obj->SetParent(_parent);
			return new_obj;
		}

	private:
		void Init() {
			root = game_object_pool.AllocObject();
		}

	private:
		GameObject* root;
		GameObjectManager* game_object_manager;
		GameObjectSyncronizer* syncronizer;
		GameCore* m_owner_game_core;
		DGeneric::CObjectPool<GameObject> game_object_pool;
	};
}