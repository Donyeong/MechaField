#pragma once


namespace DLogic {
	class GameObject;
	class Component {
	public:
		GameObject* GetGameObject()
		{
			return m_game_object;
		}
		virtual void OnAwake() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
	private:
		GameObject* m_game_object;
	};
}