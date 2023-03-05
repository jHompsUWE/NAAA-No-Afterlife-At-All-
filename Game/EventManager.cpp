#include "pch.h"
#include "EventManager.h"

void EventManager::addListener(Listener& _listener)
{
	listeners.push_back(_listener);
}

void EventManager::removeListener(Listener& _listener)
{
	std::shared_ptr<KeyPressedEvent> key_event = std::shared_ptr<KeyPressedEvent>();
	triggerEvent(key_event);
}

void EventManager::triggerEvent(std::shared_ptr<Event> _event)
{
	events.emplace(_event);
}

void EventManager::lateUpdate(DX::StepTimer const& _timer)
{
	dispatchEvents();
}

void EventManager::dispatchEvents()
{

	for (int i = events.size(); i > 0; --i)
	{
		for (auto listener : listeners)
		{
			listener.OnEvent(&*events.front());
		}

		events.pop();
	}
}
