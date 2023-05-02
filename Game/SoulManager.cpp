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

	for (size_t i = 0; i < 1000; i++)
	{
		AddSoul();
	}
	for (size_t i = 0; i < 1000; i++)
	{
		AddEMBO();
	}
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
	soul->m_position = Vector2{0,0};			// position the soul on the grid
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
	}
	std::cout << "[Soulmanager.cpp][42] [WARN] total souls";
	return 0;
}

void SoulManager::awake(GameData& _game_data)
{
	EMBO* soul_test = new EMBO();
	soul_test->earth_belief = 2;
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

	for (auto& EMBO : m_Earth_Souls)
	{
		EMBO->m_yearsleft--;
		if (EMBO->m_totalyears <= 0)
		{

		}
	}



	//if (_game_data.Year%10 == 0)
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


void SoulManager::zone_checking(Soul* soul, PlaneType _plane)
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
	
	Vector2 pos = soul->m_position; 
	int soulindex = world_manager->getIndex(soul->m_position);


	std::vector<int> connected_index = {};
	std::vector<int> radius_indexs= {};
	if (world_manager->withinRange(soul->m_position))
	{
		connected_index.emplace_back(world_manager->getIndex(soul->m_position));
	}
	//connected_index.emplace_back(soulindex);
		
	for (auto direction : connected_radius)
	{
		if (!world_manager.get()->withinRange(soul->m_position + direction))
		{
			continue;
		}
		connected_index.emplace_back(world_manager->getIndex(soul->m_position + direction));
	}
		
	for (auto direction : radius_directions)
	{
		if (!world_manager.get()->withinRange(soul->m_position + direction))
		{
			continue;
		}
		radius_indexs.emplace_back(world_manager->getIndex(soul->m_position + direction));
	}
		
	auto& plane = world_manager->getWorld()[_plane];
	for (auto index : connected_index)
	{
	
		auto& grid_data = plane[index]->getGridData();
		if (grid_data.m_connected == true && (grid_data.m_zone_type == soul->m_zonetype || grid_data.m_zone_type == ZoneType::Generic) && grid_data.m_building_data != nullptr)
		{
			GenericBuilding* building = grid_data.m_building_data;
			if (building->m_capacity.MaximumCapacity > building->m_capacity.CurrentCapacity)
			{
				(soul->m_reincarnate
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
		if (grid_data.m_connected != true && (grid_data.m_zone_type == soul->m_zonetype || grid_data.m_zone_type == ZoneType::Generic) && grid_data.m_building_data != nullptr)
		{
			auto& building = grid_data.m_building_data;
			if (building->m_capacity.MaximumCapacity > building->m_capacity.CurrentCapacity)
			{
				(soul->m_reincarnate
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




void SoulManager::wandering(Soul* soul,PlaneType plane)
{
	Vector2 directons[4] = {{0,1},{1,0},{-1,0},{0,-1}};
	int cardinal[4] = {-1000,-1000,-1000,-1000};
	Vector2 pos = soul->m_position;
	int soulindex = world_manager->getIndex(soul->m_position);
	for (int i = 0; i < 4; ++i)
	{
		if (world_manager->withinRange(pos + directons[i]))
		{
			cardinal[i] = world_manager->getIndex(pos + directons[i]);
		}
	}
	
	bool failedn = false;
	bool failede = false;
	bool faileds = false;
	bool failedw = false;
	
	if (soulindex <= 0 || (world_manager->getWorld()[plane][soulindex]->getGridData().m_tile_type != TileType::Building ||
		world_manager->getWorld()[plane][soulindex]->getGridData().m_tile_type != TileType::Road))
	{
		return;
	}
	
	bool wandering = true;
	while (wandering)
	{
		int rand = std::rand() % 4 + 1;
		switch (rand)
		{
		case 1:
			{
				if (failedn or cardinal[0] <= -1)
				{
					failedn = true;
					break;
				}
				if (world_manager->getWorld()[plane][cardinal[0]]->getGridData().m_tile_type == TileType::Road)
				{
					soul->m_position = Vector2{ pos.x,pos.y + 1 };
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
				if (failede or cardinal[1] <= -1)
				{
					failede = true;
					break;
				}
				if (world_manager->getWorld()[plane][cardinal[1]]->getGridData().m_tile_type == TileType::Road)
				{
					soul->m_position = Vector2{ pos.x + 1,pos.y };
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
				if (faileds or cardinal[2] <= -1)
				{
					faileds = true;
					break;
				}
				if (world_manager->getWorld()[plane][cardinal[2]]->getGridData().m_tile_type == TileType::Road)
				{
					soul->m_position = Vector2{ pos.x,pos.y - 1 };
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
				if (failedw or cardinal[3] <= -1)
				{
					failedw = true;
					break;
				}
				if (world_manager->getWorld()[plane][cardinal[3]]->getGridData().m_tile_type == TileType::Road)
				{
					soul->m_position = Vector2{ pos.x - 1,pos.y };
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

void SoulManager::AddEMBO()
{
	EMBO* embo = new EMBO;
	embo->earth_belief = std::rand()% 15 + 0;
	embo->m_totalyears = rand()%120 + 1;

	// Define if the soul can reincarnate
	if (embo->earth_belief <= 4 or (embo->earth_belief >= 9 and embo->earth_belief <= 12))
		embo->m_reincarnate = false;


	int random = std::rand() % RAND_MAX;
	(random % 2 == 0 ? m_Earth_Souls : m_Earth_Souls).emplace_back(embo);
	//std::cout << "soul made";
}