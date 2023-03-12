#include "pch.h"
#include "GameManager.h"

void GameManager::awake()
{
	for (auto manager : managers)
	{
		manager->awake();
	}
}

void GameManager::update(GameData& _game_data)
{
	for (auto manager : managers)
	{
		manager->update(_game_data);
	}
}

void GameManager::lateUpdate(GameData& _game_data)
{
	for (auto manager : managers)
	{
		manager->lateUpdate(_game_data);
	}
}

void GameManager::render(DrawData* m_DD)
{
	for (auto manager : managers)
	{
		manager->render(m_DD);
	}
}

bool GameManager::addManager(std::shared_ptr<Manager> _manager, ManagerType _type)
{
	managers.emplace_back(_manager);

	switch (_type)
	{
	case ManagerType::EVENT:
		{
			event_manager = reinterpret_cast<EventManager*>(&*_manager);
			return true;
		}
	}
	return false;
}

bool GameManager::removeManager(std::shared_ptr<Manager> _manager, ManagerType _type)
{
	managers.erase(std::remove(managers.begin(), managers.end(), _manager), managers.end());

	switch (_type)
	{
	case ManagerType::EVENT:
		{
			event_manager = nullptr;
			return true;
		}
	}
	return false;
}
