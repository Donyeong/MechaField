#pragma once
#include "../dl_pch.h"
#include "CommandManager.h"
#include "Scene.h"
namespace DLogic {
	class GameCore {
		
	public:
		void Start();
		void Update();
		void PutScene(int _hash_key, Scene* _scene);
		Scene* GetScene(int _hash_key);
		void LoadScene(Scene* _scene);
	private:
		void BuildScene();
	private:
		CommandManager m_command_manager;
		DGeneric::HashMap<int, Scene*> m_map_scene;
		int m_current_scene;
	};
}