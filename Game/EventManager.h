#pragma once

#include "Manager.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "Listener.h"
#include <queue>
#include "StepTimer.h"

class EventManager : public Manager
{
public:
	EventManager() = default;
	~EventManager() = default;

	void update() override {}; // Needs to override to avoid being an abstract class or could not inherit from manager.

	void addListener(Listener& _listener);
	void removeListener(Listener& _listener);

	void triggerEvent(std::shared_ptr<Event> _event);
	void lateUpdate(DX::StepTimer const& _timer);

private:
	void dispatchEvents();

	std::queue<std::shared_ptr<Event>> events;
	std::vector<Listener> listeners;
};
