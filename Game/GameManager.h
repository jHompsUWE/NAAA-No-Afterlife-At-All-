#pragma once

#include "Manager.h"
#include "EventManager.h"
#include <vector>
#include <memory>

enum class ManagerType : int
{
	INPUT,
	CAMERA,
	EVENT,
	WORLD
};

class GameManager
{
public:

	~GameManager()
	{
		delete(get());
	};

	////////////////////////////////////////////////////////////
	/// \brief Returns the GameManager singleton.
	///////////////////////////////////////////////////////////////
	static GameManager* get(); // Meyers Singleton

	GameManager(GameManager const&) = delete; // disables copy constructor.
	GameManager& operator=(GameManager const&) = delete; // disables move assignment operator.

	void update();

	////////////////////////////////////////////////////////////
	/// \brief Attempts to add a manager to the vector of managers to updated each tick.
	///
	/// \param _manager The manager to add to the manager vector.
	///	\param _type Type is used to identify what kind of Manager _manager is so that it can be stored within the correct variable. 
	///
	////////////////////////////////////////////////////////////
	bool addManager(Manager*_manager, ManagerType _type);

	////////////////////////////////////////////////////////////
	/// \brief Attempts to remove a manager from the vector of managers to be updated each tick.
	///
	/// \param _manager The manager to removed from the manager vector.
	///	\param _type Type is used to identify what kind of Manager _manager is so that it can be removed from the correct variable. 
	///
	////////////////////////////////////////////////////////////
	bool removeManager(Manager* _manager, ManagerType _type);

private:
	GameManager() {};

	std::vector<std::shared_ptr<Manager>> managers;
	EventManager* event_manager;
};

inline GameManager* GameManager::get()
{
	static GameManager* instance;

	 if (instance == nullptr)
	 {
		 instance = new GameManager;
	 }

	return instance;
}