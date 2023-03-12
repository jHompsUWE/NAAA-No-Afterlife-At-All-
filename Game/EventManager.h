#pragma once

#include <vector>

#include "Manager.h"
#include "Event.h"
#include "Listener.h"
#include "StepTimer.h"

class EventManager : public Manager
{
public:
	EventManager() = default;
	~EventManager() = default;

	////////////////////////////////////////////////////////////
	/// \brief Needs to override to avoid being an abstract class or could not inherit from manager. \n Does nothing for EventManager.
	////////////////////////////////////////////////////////////
	void update(DX::StepTimer const& _timer) override {};

	////////////////////////////////////////////////////////////
	/// \brief Call to add a listener to the active listener vector.
	///	\param _listener The listener to be added. Will receive events.
	////////////////////////////////////////////////////////////
	void addListener(Listener* _listener);

	////////////////////////////////////////////////////////////
	/// \brief Call to remove a listener from the active listeners vector. 
	///	\param _listener The listener to be removed. It will no longer receive events.
	////////////////////////////////////////////////////////////
	void removeListener(Listener* _listener);

	////////////////////////////////////////////////////////////
	/// \brief Call to add an event to be distributed to the listeners. 
	///	\param _event A shared ptr to the event to be executed.
	////////////////////////////////////////////////////////////
	void triggerEvent(std::shared_ptr<Event> _event);

	////////////////////////////////////////////////////////////
	/// \brief Called every cycle of the game loop, but after update.
	///	\param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	void lateUpdate(DX::StepTimer const& _timer) override;

private:
	////////////////////////////////////////////////////////////
	/// \brief Cycles through all events and, if events are due to be dispatched, will send them to all registered listeners. \n
	/// A future development would be to filter events to only send to listeners that need them.
	/// \param _timer DeltaTime.
	////////////////////////////////////////////////////////////
	void dispatchEvents(DX::StepTimer const& _timer);

	////////////////////////////////////////////////////////////
	/// \brief Vector of events to be distributed to listeners.
	////////////////////////////////////////////////////////////
	std::vector<std::shared_ptr<Event>> events;

	////////////////////////////////////////////////////////////
	/// \brief Vector of listeners to distribute events to. 
	////////////////////////////////////////////////////////////
	std::vector<Listener*> listeners;
};
