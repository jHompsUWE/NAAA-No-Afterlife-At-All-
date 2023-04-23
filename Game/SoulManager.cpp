#include "pch.h"
#include "SoulManager.h"

#include "BuildingData.h"
#include "Pathfinding.h"
#include "WorldManager.h"

//#include "WorldManager.h"

SoulManager::SoulManager(map<PlaneType, vector<unique_ptr<GridLocation>>>& world): game_world(world)
{
	srand(time(nullptr));
}

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

	ZoneCheck();
	Wander();




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


void SoulManager::ZoneCheck()
{
	Vector2 directions[24] =
{
		{1, 0}, {2, 0}, {3, 0}, // right
		{0, -1}, {0, -2}, {0, -3}, // back
		{-1, 0}, {-2, 0}, {-3, 0}, // left
		{0, 1}, {0, 2}, {0, 3}, // front
		{1, 1}, {1, 2}, {2, 1}, // top right
		{1, -1}, {1, -2}, {2, -1}, // bottom right
		{-1, 1}, {-1, 2}, {-2, 1}, // top left
		{-1, -1}, {-1, -2}, {-2, -1} // bottom left
};
	for (auto soul : m_Heven_wanderingSouls)
	{
		Vector2 pos = soul->position; 
		int soulindex = WorldManager::getIndex(soul->Soul::position);
		int north = WorldManager::getIndex(Vector2{pos.x,pos.y + 1});
		int east =	WorldManager::getIndex(Vector2{pos.x + 1,pos.y});
		int south = WorldManager::getIndex(Vector2{pos.x,pos.y - 1});
		int west =	WorldManager::getIndex(Vector2{pos.x - 1,pos.y});

		if (game_world[PlaneType::Heaven][soulindex]->getGridData().)
		{
			
		}
	}
}




void SoulManager::wandering(shared_ptr<Soul> soul,PlaneType plane)
{
	Vector2 pos = soul->position; 
	int soulindex = WorldManager::getIndex(soul->Soul::position);
	int north = WorldManager::getIndex(Vector2{pos.x,pos.y + 1});
	int east =	WorldManager::getIndex(Vector2{pos.x + 1,pos.y});
	int south = WorldManager::getIndex(Vector2{pos.x,pos.y - 1});
	int west =	WorldManager::getIndex(Vector2{pos.x - 1,pos.y});
	bool failedn,failede,faileds,failedw = false;
	if (game_world[PlaneType::Heaven][soulindex]->getGridData().m_tile_type == TileType::Building ||
		game_world[PlaneType::Heaven][soulindex]->getGridData().m_tile_type == TileType::Road)
	{
		bool wandering = true;
		while (wandering)
		{
			int rand = rand() % 4 + 1;
			switch (rand)
			{
			case 1 and !failedn:
				{
					if (game_world[plane][north]->getGridData().m_tile_type == TileType::Road)
					{
						soul->position = Vector2{pos.x,pos.y + 1};
						wandering = false;
					}
					else
					{
						failedn = true;
					}
					break;
				}
			case 2 and (!failede):
				{
					if (game_world[plane][east]->getGridData().m_tile_type == TileType::Road)
					{
						soul->position = Vector2{pos.x + 1,pos.y};
						wandering = false;
					}
					else
					{
						failede = true;
					}
					break;
				}
			case 3 and !faileds:
				{
					if (game_world[plane][south]->getGridData().m_tile_type == TileType::Road)
					{
						soul->position = Vector2{pos.x,pos.y - 1};
						wandering = false;
					}
					else
					{
						faileds = true;
					}
					break;
				}
			case 4 and !failedw:
				if (game_world[plane][west]->getGridData().m_tile_type == TileType::Road)
				{
					soul->position = Vector2{pos.x - 1,pos.y};
					wandering = false;
				}
				else
				{
					failedw = true;
				}
				break;
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
