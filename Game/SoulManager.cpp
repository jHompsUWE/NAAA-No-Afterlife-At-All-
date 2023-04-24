#include "pch.h"
#include "SoulManager.h"

#include "BuildingData.h"
#include "GameManager.h"
#include "Pathfinding.h"
//#include "WorldManager.h"

//#include "WorldManager.h"

SoulManager::SoulManager(shared_ptr<WorldManager> _world_manager) :world_manager(_world_manager)
{
	srand(time(nullptr));
}

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

	ZoneCheck();
	Wander();




	if (_game_data.Year%10 == 0)
	{
		if (m_Earth_Souls.size() >= 10)
		{
			int length = 10;
			for (size_t i = 0; i < length; i++)
			{
				//m_Heven_wanderingSouls.push_back(std::move(m_Earth_Souls.back().));
				//m_Earth_Souls.pop_back();
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
	//switch (event.type)
	//{
	//case EventType::ADD_SOUL:
		//AddSoul(Vector2(event.payload.add_soul.x, event.payload.add_soul.y), event.payload.add_soul.plane);
	//}
}


void SoulManager::zone_checking(shared_ptr<Soul> soul, PlaneType _plane)
{
	Vector2 radius_directions[20] =
		{
		{ 1, 1}, { 2, 0}, { 3, 0},
		{ 0,-2}, { 0,-3}, {-2, 0},
		{-3, 0}, { 0, 2}, { 0, 3},
		{ 1, 2}, { 2, 1}, { 1,-1},
		{ 1,-2}, { 2,-1}, {-1, 1},
		{-1, 2}, {-2, 1}, {-1,-1},
		{-1,-2}, {-2,-1}
		};
	Vector2 connected_radius[4] = { {1,0}, {0,-1}, {-1,0}, {0,1} };
	
	Vector2 pos = soul->position; 
	int soulindex = world_manager->getIndex(soul->position);


	std::vector<int> connected_index = {};
	std::vector<int> radius_indexs= {};
	connected_index.emplace_back(soulindex);
		
	for (auto direction : connected_radius)
	{
		connected_index.emplace_back(world_manager->getIndex(soul->position + direction));
	}
		
	for (auto direction : radius_directions)
	{
		radius_indexs.emplace_back(world_manager->getIndex(soul->position + direction));
	}
		
	auto& plane = world_manager->getWorld()[_plane];
	for (auto index : connected_index)
	{
		auto& grid_data = plane[index]->getGridData();
		if (grid_data.m_connected == true && grid_data.m_zone_type == soul->zonetype && grid_data.m_building_data != nullptr)
		{
			GenericBuilding* building = grid_data.m_building_data;
			if (building->m_capacity.MaximumCapacity > building->m_capacity.CurrentCapacity)
			{
				(soul->reincarnate
					 ?building->m_capacity.TemporaryCapacity
					 :building->m_capacity.PermanentCapacity).emplace_back(soul);
				m_Heven_ZonedSouls.emplace_back(move(soul));
				building->m_capacity.CurrentCapacity++;
			}
		}
	}
	for (auto index : radius_indexs)
	{
		auto& grid_data = plane[index]->getGridData();
		if (grid_data.m_connected != true && grid_data.m_zone_type == soul->Soul::zonetype && grid_data.m_building_data != nullptr)
		{
			auto& building = grid_data.m_building_data;
			if (building->m_capacity.MaximumCapacity > building->m_capacity.CurrentCapacity)
			{
				(soul->Soul::reincarnate
					 ?building->m_capacity.TemporaryCapacity
					 :building->m_capacity.PermanentCapacity).emplace_back(soul);
				m_Heven_ZonedSouls.emplace_back(move(soul));
				building->m_capacity.CurrentCapacity++;
			}
		}
	}
}

void SoulManager::ZoneCheck()
{
	for (auto soul : m_Heven_wanderingSouls)
	{
		zone_checking(soul,PlaneType::Heaven);
	}
}




void SoulManager::wandering(shared_ptr<Soul> soul,PlaneType plane)
{
	Vector2 pos = soul->position; 
	int soulindex = world_manager->getIndex(soul->Soul::position);
	int north = world_manager->getIndex(Vector2{pos.x,pos.y + 1});
	int east =	world_manager->getIndex(Vector2{pos.x + 1,pos.y});
	int south = world_manager->getIndex(Vector2{pos.x,pos.y - 1});
	int west =	world_manager->getIndex(Vector2{pos.x - 1,pos.y});
	bool failedn = false;
	bool failede = false;
	bool faileds = false;
	bool failedw = false;
	if (world_manager->getWorld()[PlaneType::Heaven][soulindex]->getGridData().m_tile_type == TileType::Building ||
		world_manager->getWorld()[PlaneType::Heaven][soulindex]->getGridData().m_tile_type == TileType::Road)
	{
		bool wandering = true;
		while (wandering)
		{
			int rand = std::rand() % 4 + 1;
			switch (rand)
			{
			case 1:
			{
				if (failedn)
				{
					break;
				}
				if (world_manager->getWorld()[plane][north]->getGridData().m_tile_type == TileType::Road)
				{
					soul->position = Vector2{ pos.x,pos.y + 1 };
					wandering = false;
				}
				else
				{
					failedn = true;
				}
				break;
			}
			case 2:
			{
				if (failede)
				{
					break;
				}
				if (world_manager->getWorld()[plane][east]->getGridData().m_tile_type == TileType::Road)
				{
					soul->position = Vector2{ pos.x + 1,pos.y };
					wandering = false;
				}
				else
				{
					failede = true;
				}
				break;
			}
			case 3:
			{
				if (faileds)
				{
					break;
				}
				if (world_manager->getWorld()[plane][south]->getGridData().m_tile_type == TileType::Road)
				{
					soul->position = Vector2{ pos.x,pos.y - 1 };
					wandering = false;
				}
				else
				{
					faileds = true;
				}
				break;
			}
			case 4:
			{
				if (failedw)
				{
					break;
				}
				if (world_manager->getWorld()[plane][west]->getGridData().m_tile_type == TileType::Road)
				{
					soul->position = Vector2{ pos.x - 1,pos.y };
					wandering = false;
				}
				else
				{
					failedw = true;
				}
				break;
			}
			default:
				{
					CONSOLE(ERROR,"THIS SHOULD NOT PRINT: " + std::to_string(rand));
					break;
				};
			}
			if (failedn && failede && faileds && failedw)
			{
				wandering = false;
				// event soul cannot move?
			}
		}
	}
}

void SoulManager::Wander()
{
	for (auto wandering_soul : m_Heven_wanderingSouls)
	{
		wandering(wandering_soul,PlaneType::Heaven);
	}
	for (auto m_hell_wandering_soul : m_Hell_wanderingSouls)
	{
		wandering(m_hell_wandering_soul,PlaneType::Hell);
	}
}
