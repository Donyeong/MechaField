#pragma once
#include "../dl_pch.h"
#include "../GameObjectManager.h"
#include "../DGameMode.h"
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
		~Scene() {
			clear();
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

		void LoadScene() {
			DASSERT(nullptr != m_game_mode);
			m_game_mode->OnLoad();
		}

		void UnloadScene() {

		}

		void SetGameMode(DGameMode* game_mode) {
			m_game_mode = game_mode;
		}

		void Update(float _delta_time) {
			DGeneric::Stack<GameObject*> update_stack;
			if (nullptr != root) {
				update_stack.push(root);
			}

			while (!update_stack.empty()) {
				GameObject* obj = update_stack.top();
				obj->OnUpdate();
				const DGeneric::Vector<GameObject*>& childs = obj->GetChilds();
				for (auto i = childs.begin(); i != childs.end(); i++) {
					update_stack.push(*i);
				}
			}
		}

	private:
		void Init() {
			root = game_object_pool.AllocObject();
		}
		void clear() {
			
		}

	private:
		DGameMode* m_game_mode;
		GameObject* root;
		GameObjectManager* game_object_manager;
		GameObjectSyncronizer* syncronizer;
		GameCore* m_owner_game_core;
		DGeneric::CObjectPool<GameObject> game_object_pool;
	};
}