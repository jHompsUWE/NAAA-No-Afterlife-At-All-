#include "pch.h"
#include "EventManager.h"

void EventManager::addListener(Listener* _listener)
{
	listeners.push_back(_listener);
}

void EventManager::removeListener(Listener* _listener)
{
	listeners.erase(std::remove(listeners.begin(), listeners.end(), _listener), listeners.end());
}

void EventManager::triggerEvent(std::shared_ptr<Event> _event)
{
	events.emplace_back(_event);
	std::cout << "received event" << std::endl;
}

void EventManager::lateUpdate(DX::StepTimer const& _timer)
{
	dispatchEvents(_timer);
}

void EventManager::dispatchEvents(DX::StepTimer const& _timer)
{
	for (int i = events.size()-1; i >= 0; i--)
	{
		auto& event = events[i];

		if (event->delay > 0)
		{
			event->delay -= _timer.GetElapsedSeconds();
			continue;
		}

		for (auto listener : listeners)
		{
			listener->onEvent(*event);
			std::cout << "event dispatched" << std::endl;
		}
		
		events.erase(std::remove(events.begin(), events.end(), event), events.end());
	}
}
