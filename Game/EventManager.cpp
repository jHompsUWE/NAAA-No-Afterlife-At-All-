
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
	if (_event->delay <= 0)
	{
		events.push(_event);
	}
	else
	{
		delayed_events.emplace_back(_event);
	}
}

void EventManager::lateUpdate(GameData& _game_data)
{
	dispatchEvents(_game_data);
}

void EventManager::dispatchEvents(GameData& _game_data)
{
	for (auto it = delayed_events.begin(); it != delayed_events.end();)
	{
		auto& event = *it;
		event->delay -= _game_data.m_dt;

		if (event->delay <= 0) {
			events.push(event);
			it = delayed_events.erase(it);
		}
		else
		{
			++it;
		}
	}

	while (!events.empty())
	{
		auto event = events.top();
		events.pop();

		for (auto listener : listeners)
		{
			listener->onEvent(*event);
		}
	}
}
