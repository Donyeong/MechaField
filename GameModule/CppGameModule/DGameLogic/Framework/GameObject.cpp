#include "GameObject.h"

void DLogic::GameObject::AddComponent(Component* component)
{
}

void DLogic::GameObject::RemoveChild(GameObject* _child)
{
	childs.RemoveElement(_child);
	_child->m_parent = nullptr;
}

void DLogic::GameObject::RemoveParent()
{
	GameObject* parent = GetParent();
	parent->RemoveChild(this);
	m_parent = nullptr;
}

void DLogic::GameObject::AddChild(GameObject* _child)
{
	_child->RemoveParent();
	
}

void DLogic::GameObject::SetParent(GameObject* _parent)
{
	this->RemoveParent();

}

DLogic::GameObject* DLogic::GameObject::GetParent()
{
	return m_parent;
}
