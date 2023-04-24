#include "pch.h"
#include "SoulManager.h"

#include <iostream>

#include "GameManager.h"

/**
 * \brief add a EMBO to the souls
 * @details based on the @enum Fate setup the SOUL for afterlife and its route
 */
void SoulManager::AddSoul()
{
	
	int earth_belif = std::rand()% 15 + 0;
	std::cout << "num: " << earth_belif << std::endl;

	Soul* soul = new Soul;
	soul->m_position = Vector2{-100,-100};	// position the soul of the screen
	soul->m_totalyears = rand()%900 + 100;		//total years they have to spend on one tile

	
	if (earth_belif <= 4 or (earth_belif >= 9 and earth_belif <= 12))
		soul->m_reincarnate = false;			// do they reincaranate / temp or permenet?
	

	if (earth_belif >= 8) 
		soul->m_total_cycles = std::rand() % 15 + 10;	// there belife has more then one cycle of a plane;
	
	soul->m_fate = earth_belif;
	if ((earth_belif + 3) % 4 == 0)
	{
		soul->m_both = true;
		m_Hell_wanderingSouls.emplace_back(soul);
		return;
	}							// do they believe in going to both planes
	
	
	if ((earth_belif + 1) % 4  == 0)
	{
		m_Hell_wanderingSouls.emplace_back(soul);		//only Hell
		return;
	}
	if ((earth_belif) % 4 == 0)
	{
		m_Heven_wanderingSouls.emplace_back(soul);		//only Heven
		return;
	}


	int random = std::rand() % RAND_MAX;
	(random % 2 == 0 ? m_Hell_wanderingSouls : m_Heven_wanderingSouls).emplace_back(soul);
	//std::cout << "soul made";
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
	shared_ptr<Soul> soul_test;
	soul_test = make_shared<Soul>();
	m_Earth_Souls.push_back(soul_test);
	srand(std::time(nullptr));
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
	case EventType::ADD_SOUL:
		AddSoul(Vector2(event.payload.add_soul.x, event.payload.add_soul.y), event.payload.add_soul.plane);
	}
}
