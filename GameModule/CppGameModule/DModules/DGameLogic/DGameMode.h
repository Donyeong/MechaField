#pragma once
namespace DLogic {
	class Scene;
	class DGameMode
	{
	public:
		DGameMode();
	public:
		virtual void OnLoad() {
			
		}

		void SetScene(Scene* _scene) {
			m_scene = _scene;
		}
	public:
		Scene& GetScene() {
			return *m_scene;
		}
	private:
		Scene* m_scene;
	};
}

