#include "pch.h"
#include "SoulManager.h"

#include <iostream>

void SoulManager::AddSoul(DirectX::SimpleMath::Vector2 location, PlaneType plane)
{
	switch (plane)
	{
	case PlaneType::Earth:
		m_Earth_Souls.emplace_back(new Soul);
		break;
	case PlaneType::Heaven:
		m_Heven_wanderingSouls.emplace_back(new Soul);
		break;
	case PlaneType::Hell:
		m_Heven_wanderingSouls.emplace_back(new Soul);
		break;
	case PlaneType::None:
	default:
		CONSOLE(WARNING,"Plane not picked / None:" + to_string(int(plane)) + ", " + to_string(location.x) + ", " + to_string(location.y));
	};
	//CONSOLE(INFO, "soul made");
}

int SoulManager::TotalSoulsAmmount(PlaneType plane) const
{
	switch (plane)
	{
	case PlaneType::Earth:
		return m_Earth_Souls.size();
	case PlaneType::Heaven:
		return m_Heven_wanderingSouls.size() + m_Heven_ZonedSouls.size();
	case PlaneType::Hell:
		return m_Hell_wanderingSouls.size() + m_Hell_ZonedSouls.size();
	case PlaneType::None:
		return
			m_Heven_wanderingSouls.size() + m_Heven_ZonedSouls.size() +
			m_Hell_wanderingSouls.size() + m_Hell_ZonedSouls.size()
			;
	default:
		break;
	}
	CONSOLE(WARNING,"total souls plane not right");
	return 0;
}

void SoulManager::awake()
{

}

void SoulManager::update(GameData& _game_data)
{
	if (_game_data.Year%5 == 0)
	{
		//AddSoul(DirectX::SimpleMath::Vector2{ 1,1 });
		int length = 10;
		for (size_t i = 0; i < length; i++)
		{
			//AddSoul(DirectX::SimpleMath::Vector2{ 1,1 });
		}
	}
	if (_game_data.Year%10 == 0)
	{
		if (m_Earth_Souls.size() >= 10)
		{
			int length = 10;
			for (size_t i = 0; i < length; i++)
			{
				m_Heven_wanderingSouls.push_back(m_Earth_Souls.back());
				m_Earth_Souls.pop_back();
			}
		}
		

		Event event{};
		event.type = EventType::SOUL_UPDATE;
		event.payload.soul_update.count = m_Heven_wanderingSouls.size() + m_Heven_ZonedSouls.size() +
			m_Hell_wanderingSouls.size() + m_Hell_ZonedSouls.size();

		GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
	}
}

void SoulManager::lateUpdate(GameData& _game_data)
{
}

void SoulManager::onEvent(const Event& event)
{
	switch (event.type)
	{
	case EventType::GATE_POSITION:
		AddSoul(Vector2(event.payload.gate_position.x, event.payload.gate_position.y), event.payload.gate_position.plane);
	}
}
