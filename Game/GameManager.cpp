#include "pch.h"
#include "GameManager.h"

void GameManager::update()
{
	for (auto manager : managers)
	{
		manager->update();
	}
}

bool GameManager::addManager(Manager* _manager, ManagerType _type)
{
	managers.emplace_back(_manager);

	switch (_type)
	{
	case ManagerType::EVENT:
	{
		event_manager = reinterpret_cast<EventManager*>(_manager);
		break;
	}

	case ManagerType::CAMERA:
	{
		break;
	}
	}
	return false;
}

bool GameManager::removeManager(Manager* _manager, ManagerType _type)
{
	return false;
}
