#pragma once

#include "Framework.h"
#include "Component.h"
#include "IUpdatable.h"
#include "Transform.h"

namespace DLogic {
	class Scene;
	class GameObject : IUpdatable {

	public:
		GameObject() = default;
		//Transform transform;
		void AddComponent(Component* component);
		void RemoveChild(GameObject* _child);
		void RemoveParent();
		void AddChild(GameObject* _child);
		void SetParent(GameObject* _parent);
		GameObject* GetParent();
		Scene* GetScene() {
			return owner_scene;
		}
		virtual void OnUpdate() {}
	private:
		DGeneric::Vector<Component*> components;
		DGeneric::Vector<GameObject*> childs;
		GameObject* m_parent;
		Scene* owner_scene;
	};

}
