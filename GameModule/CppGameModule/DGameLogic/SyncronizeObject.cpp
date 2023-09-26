#include "SyncronizeObject.h"
#include "Framework/GameObject.h"
#include "Framework/Scene.h"

int DLogic::SyncronizeObject::getNetworkObjectId()
{
	return 0;
}

void DLogic::SyncronizeObject::OnAwake()
{
	GameObject* game_object = GetGameObject();
	Scene* scene = game_object->GetScene();
	GameCore* game_core = scene->GetGameCore();

}

void DLogic::SyncronizeObject::OnStart()
{
}

void DLogic::SyncronizeObject::OnUpdate()
{
}
