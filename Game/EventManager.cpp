
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
}

void EventManager::lateUpdate(GameData& _game_data)
{
	dispatchEvents(_game_data);
}

void EventManager::dispatchEvents(GameData& _game_data)
{
	for (int i = events.size()-1; i >= 0; i--)
	{
		auto& event = events[i];

		if (event->delay > 0)
		{
			event->delay -= _game_data.m_dt;
			continue;
		}

		for (auto listener : listeners)
		{
			
			listener->onEvent(*event);
		}
		
		events.erase(std::remove(events.begin(), events.end(), event), events.end());
	}
}
