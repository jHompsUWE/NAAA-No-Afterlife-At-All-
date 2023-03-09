#include "pch.h"
#include "GameManager.h"

void GameManager::awake()
{
	for (auto manager : managers)
	{
		manager->awake();
	}
}

void GameManager::update(DX::StepTimer const& _timer)
{
	for (auto manager : managers)
	{
		manager->update(_timer);
	}
}

void GameManager::lateUpdate(DX::StepTimer const& _timer)
{
	for (auto manager : managers)
	{
		manager->lateUpdate(_timer);
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
