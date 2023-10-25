#include "GameCore.h"
#include "../DGameMode_Lobby.h"
namespace DLogic {
	void GameCore::Start()
	{
		DLOG_INFO("Start GameCore");
		BuildScene();
	}
	void GameCore::Update(float _delta_time)
	{
		//DLOG_INFO("Update GameCore");
		for (auto i = m_map_scene.begin(); i != m_map_scene.end(); i++) {
			Scene* scene = (*i).second;
			scene->Update(_delta_time);
		}
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
		//TODO : 월드파일 파싱해서 씬 생성되도록 작업 필요
		DLOG_INFO("Build Scenes..");
		Scene* default_scene = Scene::AllocObject();
		default_scene->SetGameMode(DGameMode_Lobby::AllocObject());
		PutScene(0, default_scene);
		default_scene->LoadScene();

		//GameObject* game_object = default_scene->CreateGameObject();
	
		//game_object.


		//default_scene->
	}
}