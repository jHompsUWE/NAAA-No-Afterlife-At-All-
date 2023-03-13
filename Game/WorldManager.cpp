#include "pch.h"
#include "WorldManager.h"

WorldManager::WorldManager()
{
	m_num_of_planes = 2;

	m_grid_x = 10;
	m_grid_y = 10;

	int total_size = m_grid_x * m_grid_y;
	
	m_world[PlaneType::Heaven].reserve(total_size);
	m_world[PlaneType::Earth].reserve(total_size);
	m_world[PlaneType::Hell].reserve(total_size);
}

WorldManager::~WorldManager()
{

}

void WorldManager::init(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, DirectX::IEffectFactory* _fxFactory)
{
	for (auto& plane : m_world)
	{
		for (int i = 0; i < m_grid_y; i++)
		{
			for (int j = 0; j < m_grid_x; j++)
			{ 
				Vector2 pos = { float(j), float(i) };
				plane.second.push_back(std::make_unique<GridLocation>(_device, pos, int(plane.first)));
				std::cout << "Created location " << j << " " << i << std::endl;
			}
		}

		std::cout << "Plane" << std::endl;
	}
}

void WorldManager::setConnected(GridLocation& _grid_location, PlaneType _plane)
{
	// Call when road is placed, set connection status of tiles affected

	Vector2 start = _grid_location.getGridData().m_position;

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

	for (Vector2 dir : directions)
	{
		Vector2 current = { start.x + dir.x, start.y + dir.y };

		if (!withinRange(current)) continue;

		m_world[_plane][getIndex(current)]->getGridData().m_connected = true;
	}
}

void WorldManager::updateVibes(GridLocation& _grid_location, PlaneType _plane)
{
	// THIS WORKS FOR 1x1 BUILDINGS

	int radius = 3;
		//_grid_location.getGridData().m_stored_building->getBuildingData().m_vibe_radius;
	
	int vibe = _grid_location.getGridData().m_building_data.m_vibe;

	Vector2 start_pos = _grid_location.getGridData().m_position;

	std::vector<Vector2> range;
	range.reserve(25);

	Vector2 pos;

	int pos_radius_x = m_grid_x - start_pos.x;
	int pos_radius_y = m_grid_y - start_pos.y;

	int min_x = start_pos.x;
	if (min_x > radius) { min_x = radius; }

	int max_x = start_pos.x + radius;
	if (max_x > m_grid_x) { max_x = m_grid_x - start_pos.x; }

	int min_y = start_pos.y;
	if (min_y > radius) { min_y = radius; }

	int max_y = start_pos.y + radius;
	if (max_y > m_grid_y) { max_y = m_grid_y - start_pos.y; }

	for (int i = -min_y; i <= max_y; i++)
	{
		for (int j = -min_x; j <= max_x; j++)
		{
			if (abs(i) + abs(j) <= radius)
			{
				// This is within the radius of the object so update vibe
				pos = { start_pos.x + j, start_pos.y + i };
				std::cout << pos.x << " " << pos.y << std::endl;
				//m_world[_plane][getIndex(pos)].getGridData().m_vibe += vibe;
				m_world[_plane][getIndex(pos)]->getTile().SetColour(Color(0, 1, 0));
			}
			else
			{
				// If it isn't then do nothing
			}
		}
	}
}

void WorldManager::update(GameData& _game_data)
{

}

void WorldManager::render(DrawData* _DD)
{
	for (auto& plane : m_world)
	{
		if (plane.first != PlaneType::Earth)
		{
			for (auto& tile : plane.second)
			{
				tile->getTile().Draw(_DD);
				tile->getGridData().draw(_DD);
			}
		}
	}
}

std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& WorldManager::getWorld()
{
	return m_world;
}

void WorldManager::calculateEfficiency(GridLocation& _grid_location, PlaneType _plane)
{
	int distance = 0;
	int vibe = _grid_location.getGridData().m_vibe;
	int production = 0;
	int adjacency = 0;

	switch (_plane)
	{
	case PlaneType::Heaven:
		adjacency += adjacencyScoreHeaven(_grid_location);
		break;
	case PlaneType::Hell:
		adjacency += adjacencyScoreHell(_grid_location);
		break;
	default:
		break;
	}

	_grid_location.getGridData().m_efficiency = (distance + vibe + production + adjacency);
}

int WorldManager::adjacencyScoreHeaven(GridLocation& _grid_location)
{
	Vector2 start_pos = _grid_location.getGridData().m_position;
	PlaneType plane = PlaneType::Heaven;

	int adjacency = 0;

	Vector2 directions[8] =
	{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, // Cardinals
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Corners
	};

	for (Vector2 pos : directions)
	{
		Vector2 new_pos = { start_pos.x + pos.x, start_pos.y + pos.y };

		if (!withinRange(new_pos)) continue;

		int index = getIndex(new_pos);

		if (m_world[plane][index]->getGridData().m_tile_type == TileType::Zone)
		{
			if (m_world[plane][index]->getGridData().m_zone_type != _grid_location.getGridData().m_zone_type)
			{
				adjacency += 3;
			}
			else
			{
				// TODO
				// Check that although it's the same virtue / zone, it's a different species
				// This will be for adding 1
				adjacency += 1;
			}
		}
	}

	return adjacency;
}

int WorldManager::adjacencyScoreHell(GridLocation& _grid_location)
{
	Vector2 start_pos = _grid_location.getGridData().m_position;
	PlaneType plane = PlaneType::Hell;

	int adjacency = 0;

	Vector2 directions[8] =
	{
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, // Cardinals
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Corners
	};

	for (Vector2 pos : directions)
	{
		Vector2 new_pos = { start_pos.x + pos.x, start_pos.y + pos.y };

		if (!withinRange(new_pos)) continue;

		int index = getIndex(new_pos);

		// If they're the same zone type then less efficient
		if (m_world[plane][index]->getGridData().m_tile_type == TileType::Zone)
		{
			if (m_world[plane][index]->getGridData().m_zone_type == _grid_location.getGridData().m_zone_type)
			{
				adjacency += 3;

				// TODO
				// Add if statements to check species of building when implemented
			}
		}
	}

	return adjacency;
}

int WorldManager::getIndex(Vector2 position)
{
	return position.x + position.y * m_grid_x;
}

bool WorldManager::withinRange(Vector2 position)
{
	if (position.x > m_grid_x - 1 || position.x < 0 ||
		position.y > m_grid_y - 1 || position.y < 0) return false;
	return true;
}

