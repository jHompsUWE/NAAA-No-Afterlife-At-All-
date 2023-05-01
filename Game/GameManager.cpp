#include "pch.h"
#include "GameManager.h"

#include "FileManagerV2.h"

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
	case ManagerType::FILE:
		{
			file_manager = reinterpret_cast<FileManagerV2*>(&*_manager);
			return true;
		}
	case ManagerType::SOUL:
		{
			soulManager = reinterpret_cast<SoulManager*>(&*_manager);
			return true;
		}

	case ManagerType::UI:
	{
		ui_manager = reinterpret_cast<UIManager*>(&*_manager);
		return true;
	}

	case ManagerType::WORLD:
		{
			world_manager = reinterpret_cast<WorldManager*>(&*_manager);
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
	case ManagerType::FILE:
		{
			file_manager = nullptr;
			return true;
		}
	case ManagerType::UI:
		{
			ui_manager = nullptr;
			return true;
		}
	}
	return false;
}

void GameManager::SaveGame()
{
	auto saveFile = file_manager->GetJson("SaveFile");
	if (!saveFile->empty())
	{
		ofstream output("../Data/SaveFile.json");
		cout << file_manager->GetFile("SaveFile") << endl;
		// Stuff that needs to be saved
		(*saveFile)["economy_manager"]["money"] = 120;
		output << *saveFile;
		output.close();
		cout << "File saved" << endl;
	}
}

void GameManager::LoadGame()
{
	auto saveFile = file_manager->GetJson("SaveFile");
	if (!saveFile->empty())
	{
		auto money = (*saveFile)["economy_manager"]["money"];
		cout << money << endl;
	}
}

void GameManager::PauseGame()
{
	game_paused = !game_paused;
}


bool GameManager::isGamePaused() const
{
	return game_paused;
}