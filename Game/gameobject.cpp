#include "pch.h"
#include "GameObject.h"






GameObject::GameObject(std::shared_ptr<Transform> transform)
{
	m_components[TRANSFORM] = transform;
}

GameObject::GameObject(Vector3 pos, Vector3 rotation,Vector3 scale, std::shared_ptr<Transform> parent)
{
	m_components[TRANSFORM] = std::make_shared<Transform>();
	Transform* transform = reinterpret_cast<Transform*>(m_components[TRANSFORM].get());
	transform->position = pos;
	transform->rotation = rotation;
	transform->scale = scale;
	transform->parent = parent;
}

GameObject::GameObject(std::shared_ptr<Transform> parent, Vector3 offset)
{
	m_components[TRANSFORM] = std::make_shared<Transform>();
	Transform* transform = reinterpret_cast<Transform*>(m_components[TRANSFORM].get());
	transform->position = parent->position + offset;
	transform->rotation = parent->rotation;
	transform->scale = parent->scale;
	transform->parent = parent;
	transform->parent->children.emplace_back(m_components[TRANSFORM].get());
}
