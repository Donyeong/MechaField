#include "GameCore.h"
namespace DLogic {
	void GameCore::Start()
	{
		BuildScene();
	}
	void GameCore::Update()
	{
		m_command_manager.Update();

	}
	void GameCore::PutScene(int _hash_key, Scene* _scene)
	{
		DASSERT(!m_map_scene.contain(_hash_key));
		m_map_scene.insert({ _hash_key, _scene});
	}
	Scene* GameCore::GetScene(int _hash_key)
	{
		DASSERT(m_map_scene.contain(_hash_key));
		return m_map_scene.at(_hash_key);
	}
	void GameCore::LoadScene(Scene* _scene)
	{
	}

	void GameCore::BuildScene()
	{
		Scene* default_scene = Scene::AllocObject();
		PutScene(0, default_scene);

		GameObject* game_object = default_scene->CreateGameObject();
		//game_object.


		//default_scene->
	}
}