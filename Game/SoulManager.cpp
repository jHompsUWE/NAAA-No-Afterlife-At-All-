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
		std::cout << "[Soulmanager.cpp][21] [warn] Plane not picked/None: " << int(plane) << ", " << location.x << " , " << location.y;
	};
	std::cout << "soul made";
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
	}
	std::cout << "[Soulmanager.cpp][42] [WARN] total souls";
	return 0;
}

void SoulManager::awake()
{

}

void SoulManager::update(GameData& _game_data)
{
	if (_game_data.Year%5 == 0)
	{
		int length = 10;
		for (size_t i = 0; i < length; i++)
		{
			AddSoul(DirectX::SimpleMath::Vector2{ 1,1 });
		}
	}
	if (_game_data.Year%10 == 0)
	{
		int length = 10;
		for (size_t i = 0; i < length; i++)
		{
			m_Heven_wanderingSouls.push_back(m_Earth_Souls.back());
			m_Earth_Souls.pop_back();
		}
	}
}

void SoulManager::lateUpdate(GameData& _game_data)
{
}
