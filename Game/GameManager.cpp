#include "pch.h"
#include "GameManager.h"

void GameManager::awake(GameData& _game_data)
{
	for (auto manager : managers)
	{
		manager->awake(_game_data);
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

void GameManager::render(DrawData* _draw_data)
{
	for (auto manager : managers)
	{
		manager->render(_draw_data);
	}
}

void GameManager::render2D(DrawData2D* _draw_data)
{
	for (auto manager : managers)
	{
		manager->render2D(_draw_data);
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
