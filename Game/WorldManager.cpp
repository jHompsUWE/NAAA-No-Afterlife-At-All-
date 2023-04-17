#include "pch.h"
#include "WorldManager.h"
#include "BuildingData.h"

WorldManager::WorldManager(int size_x, int size_y) : m_grid_x(size_x), m_grid_y(size_y), m_soul_manager(nullptr)
{
	int total_size = m_grid_x * m_grid_y;
	
	m_world[PlaneType::Heaven].reserve(total_size);
	m_world[PlaneType::Earth].reserve(total_size);
	m_world[PlaneType::Hell].reserve(total_size);
}

WorldManager::~WorldManager()
{

}

void WorldManager::init(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, DirectX::IEffectFactory* _fxFactory,
	SoulManager* soul_manager)
{
	m_soul_manager = soul_manager;

	for (auto& plane : m_world)
	{
		for (int i = 0; i < m_grid_y; i++)
		{
			for (int j = 0; j < m_grid_x; j++)
			{ 
				Vector2 pos = { float(j) + float(plane.first) * (m_grid_x * 0.75f), float(i) + float(plane.first) * (m_grid_y * 0.75f) };
				plane.second.push_back(std::make_unique<GridLocation>(_device, pos, plane.first, Vector2(j, i)));
			}
		}

		CONSOLE(INFO, "Plane");
	}

	m_d3dContext = _device;
}

/// <summary>
/// Call this function when roads are placed. Updates the surrounding tiles to be connected.
/// </summary>
/// <param name="_grid_location">The grid location the road was placed in.</param>
/// <param name="_plane">The plane in which the road was placed.</param>
void WorldManager::setConnected(GridLocation& _grid_location)
{
	// Call when road is placed, set connection status of tiles affected

	PlaneType _plane = _grid_location.getGridData().m_plane;

	Vector2 start = { float(std::get<0>(_grid_location.getGridData().m_position)), float(std::get<1>(_grid_location.getGridData().m_position)) };

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

void WorldManager::resetConnections()
{
	for (auto& plane : m_world)
	{
		if (plane.first == PlaneType::Earth) { continue; }

		for (auto& tile : plane.second)
		{
			tile->getGridData().m_connected = false;
		}

		for (auto& tile : plane.second)
		{
			if (tile->getGridData().m_tile_type == TileType::Road)
			{
				setConnected(*tile);
			}
		}
	}
}

void WorldManager::updateVibes(GridLocation& _grid_location)
{
	// THIS WORKS FOR 1x1 BUILDINGS

	PlaneType _plane = _grid_location.getGridData().m_plane;

	int radius = 3;
		//_grid_location.getGridData().m_stored_building->getBuildingData().m_vibe_radius;
	
	int vibe = 0;
	if (_grid_location.getGridData().m_building_data)
	{
		vibe = _grid_location.getGridData().m_building_data->m_data.m_vibe;
	}

	Vector2 start_pos = { float(std::get<0>(_grid_location.getGridData().m_position)), float(std::get<1>(_grid_location.getGridData().m_position)) };

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
				CONSOLE(INFO, { std::to_string(pos.x) + " " + std::to_string(pos.y) });
				//m_world[_plane][getIndex(pos)].getGridData().m_vibe += vibe;
				//m_world[_plane][getIndex(pos)]->getTile().SetColour(Color(0, 1, 0));
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
	for (auto& plane : m_world)
	{
		if (plane.first != PlaneType::Earth)
		{
			for (auto& tile : plane.second)
			{
				tile->update(m_d3dContext, m_soul_manager);
			}
		}
	}
}

void WorldManager::lateUpdate(GameData& _game_data)
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

/// <summary>
/// Calculate the efficiency for a tile. This is used to determine if a fate structure should upgrade itself or not.
/// </summary>
/// <param name="_grid_location">The grid location to calculate efficiency for.</param>
void WorldManager::calculateEfficiency(GridLocation& _grid_location)
{
	PlaneType _plane = _grid_location.getGridData().m_plane;

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

/// <summary>
/// Calculate the adjacency score of a tile in Heaven.
/// </summary>
/// <param name="_grid_location">The grid location to check.</param>
/// <returns>The adjacency score used in efficiency calculations.</returns>
int WorldManager::adjacencyScoreHeaven(GridLocation& _grid_location)
{
	if (!_grid_location.getGridData().m_building_data) { return 0; }

	Vector2 start_pos = { float(std::get<0>(_grid_location.getGridData().m_position)), float(std::get<1>(_grid_location.getGridData().m_position)) };
	PlaneType plane = _grid_location.getGridData().m_plane;

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

		// Check the adjacent tile is a zone
		if (m_world[plane][index]->getGridData().m_tile_type == TileType::Zone)
		{
			// Check if zone types are different
			if (m_world[plane][index]->getGridData().m_zone_type != _grid_location.getGridData().m_zone_type)
			{
				adjacency += 3;
			}
			else
			{
				// Check that although zone is the same, building species is different
				if (m_world[plane][index]->getGridData().m_building_data->m_data.m_building_species !=
					_grid_location.getGridData().m_building_data->m_data.m_building_species)
				{
					adjacency += 1;
				}
			}
		}
	}

	return adjacency;
}

/// <summary>
/// Calculate the adjacency score of a tile in Hell.
/// </summary>
/// <param name="_grid_location">The grid location to check.</param>
/// <returns>The adjacency score used in efficiency calculations.</returns>
int WorldManager::adjacencyScoreHell(GridLocation& _grid_location)
{
	if (!_grid_location.getGridData().m_building_data) { return 0 ; }

	Vector2 start_pos = { float(std::get<0>(_grid_location.getGridData().m_position)), float(std::get<1>(_grid_location.getGridData().m_position)) };
	PlaneType plane = _grid_location.getGridData().m_plane;

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
			// Check if they're the same sin (zone type)
			if (m_world[plane][index]->getGridData().m_zone_type == _grid_location.getGridData().m_zone_type)
			{
				// Check if they're the same species of building
				if (m_world[plane][index]->getGridData().m_building_data->m_data.m_building_species ==
					_grid_location.getGridData().m_building_data->m_data.m_building_species)
				{
					adjacency += 3;
				}
				else
				{
					adjacency++;
				}
			}
		}
	}

	return adjacency;
}

/// <summary>
/// Get the tile index based on it's Vector2 position.
/// </summary>
/// <param name="position">The position of the grid location in relation to the grid.</param>
/// <returns>An integer index that can be used in m_world array.</returns>
int WorldManager::getIndex(Vector2 position)
{
	return position.x + position.y * m_grid_x;
}

/// <summary>
/// Check that a tile index is within range of the grid.
/// </summary>
/// <param name="position">The position of the grid location in relation to the grid.</param>
/// <returns>A boolean in relation to if the index is within range of the grid.
/// Used to unsure there are no out of index errors during runtime.</returns>
bool WorldManager::withinRange(Vector2 position)
{
	if (position.x > m_grid_x - 1 || position.x < 0 ||
		position.y > m_grid_y - 1 || position.y < 0) return false;
	return true;
}

