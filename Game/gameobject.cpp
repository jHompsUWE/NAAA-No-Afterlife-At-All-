#include "pch.h"
#include "GameObject.h"






GameObject::GameObject(Transform transform = {})
{
	m_components.emplace_back(std::make_unique<Transform>(transform));
}

GameObject::GameObject(Vector3 pos, Vector3 rotation, Transform* parent)
{
	m_components.emplace_back(std::make_unique<Transform>());
	m_components.back->pos = pos;

}

GameObject::GameObject(Transform* parent, Vector3 offset)
{

}
