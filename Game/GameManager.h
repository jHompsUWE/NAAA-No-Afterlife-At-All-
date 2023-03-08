#pragma once

#include <vector>
#include <memory>

#include "Manager.h"
#include "EventManager.h"

////////////////////////////////////////////////////////////
/// \brief Enum for specifying derived Manager classes.
///////////////////////////////////////////////////////////////
enum class ManagerType : int
{
	INPUT,
	CAMERA,
	EVENT

};

class GameManager
{
public:

	~GameManager()
	{
		auto* instance = get();
		delete(instance);
		instance = nullptr;
	};

	////////////////////////////////////////////////////////////
	/// \brief Returns the GameManager singleton.
	///////////////////////////////////////////////////////////////
	static GameManager* get(); // Meyers Singleton

	GameManager(GameManager const&) = delete; // disables copy constructor.
	GameManager& operator=(GameManager const&) = delete; // disables move assignment operator.

	////////////////////////////////////////////////////////////
	/// \brief Is called when the program initializes.
	////////////////////////////////////////////////////////////
	void awake();

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	void update(DX::StepTimer const& _timer);

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop, but after update.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	void lateUpdate(DX::StepTimer const& _timer);


	////////////////////////////////////////////////////////////
	/// \brief Attempts to add a manager to the vector of managers to updated each tick.
	/// \param _manager The manager to add to the manager vector.
	///	\param _type Type is used to identify what kind of Manager _manager is so that it can be stored within the correct variable.
	////////////////////////////////////////////////////////////
	bool addManager(std::shared_ptr<Manager>, ManagerType _type);

	////////////////////////////////////////////////////////////
	/// \brief Attempts to remove a manager from the vector of managers to be updated each tick.
	/// \param _manager The manager to removed from the manager vector.
	///	\param _type Type is used to identify what kind of Manager _manager is so that it can be removed from the correct variable. 
	////////////////////////////////////////////////////////////
	bool removeManager(std::shared_ptr<Manager> _manager, ManagerType _type);

private:
	GameManager() {};

	////////////////////////////////////////////////////////////
	/// \brief Vector of managers to iterate over & update.
	////////////////////////////////////////////////////////////
	std::vector<std::shared_ptr<Manager>> managers;

	////////////////////////////////////////////////////////////
	/// \brief Pointer to EventManager for accessing derived class members.
	////////////////////////////////////////////////////////////
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