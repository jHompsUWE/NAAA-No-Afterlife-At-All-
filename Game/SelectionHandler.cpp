#include "pch.h"
#include "SelectionHandler.h"
#include "Mouse.h"
#include <math.h>

#include "Pathfinding.h"

SelectionHandler::SelectionHandler(std::shared_ptr<WorldManager> _world_manager, GameData* _GD) :
	m_world_manager(_world_manager), m_GD(_GD)
{
	m_plane = PlaneType::Hell;
}

void SelectionHandler::setStartPos(Vector3 _start_pos)
{
	m_start_pos = _start_pos;
}

void SelectionHandler::setEndPos(Vector3 _end_pos)
{
	m_end_pos = _end_pos;
}


void SelectionHandler::update(TPSCamera& tps_cam)
{
	update_tile = false;
	// Convert mouse pos to world pos every update
	Vector3 v = XMVector3Unproject(XMVectorSet(m_GD->m_MS.x, m_GD->m_MS.y, 0.0f, 0.0f), 0, 0, 800, 600, -10000, 10000, tps_cam.GetProj(), tps_cam.GetView(), XMMatrixIdentity());
	Vector3 m_pos = convertPosition(v, tps_cam);

	GridLocation* current_nearest = findNearestTile(m_pos);

	m_end_tile = current_nearest;

	if (m_GD->m_mouseButtons.leftButton)
	{
		if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			m_start_pos = m_pos;

			m_start_tile = current_nearest;

			currently_selecting = true;
		}
		if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			m_end_pos = m_pos;

			currently_selecting = false;
			update_tile = true;
		}
	}

	updateTiles();

}


void SelectionHandler::onEvent(const Event& event)
{
	switch (event.type)
	{
		case EventType::GREEN_ZONING:
		{
			m_zone_type = ZoneType::Green;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::YELLOW_ZONING:
		{
			m_zone_type = ZoneType::Yellow;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::ORANGE_ZONING:
		{
			m_zone_type = ZoneType::Orange;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::BROWN_ZONING:
		{
			CONSOLE(INFO, "Brown");
			m_zone_type = ZoneType::Brown;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::PURPLE_ZONING:
		{
			m_zone_type = ZoneType::Purple;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::RED_ZONING:
		{
			m_zone_type = ZoneType::Red;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::BLUE_ZONING:
		{
			m_zone_type = ZoneType::Blue;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::GENERIC_ZONING:
		{
			m_zone_type = ZoneType::Generic;
			m_tile_type = TileType::Zone;
			break;
		}
		case EventType::ROADS:
		{
			m_zone_type = ZoneType::None;
			m_tile_type = TileType::Road;
			break;
		}
		default:;
	}
}

/// <summary>
/// Function to convert mouse positions into world positions
/// </summary>
/// <param name="_pos_to_convert">The vector3 position to convert</param>
/// <param name="tps_cam">The camera currently being used so the convertion is accurate</param>
/// <returns>The converted position that will now be in world space</returns>
Vector3 SelectionHandler::convertPosition(Vector3 _pos_to_convert, TPSCamera& tps_cam)
{
	Vector3 _out_vector;
	Vector3 camera_direction = tps_cam.GetDirection();
	float distance = -_pos_to_convert.y / camera_direction.y;
	_out_vector.x = _pos_to_convert.x + distance * camera_direction.x;
	_out_vector.y = 0;
	_out_vector.z = _pos_to_convert.z + distance * camera_direction.z;

	return _out_vector;
}

/// <summary>
/// Update the tiles with in selection. Setting their zones.
/// </summary>
void SelectionHandler::updateTiles()
{
	std::tuple<int, int> start_grid;

	if (m_start_tile)
	{
		start_grid = m_start_tile->getGridData().m_position;
	}
	
	std::tuple<int, int> end_grid = m_end_tile->getGridData().m_position;

	bool x_increase = false;
	bool y_increase = false;

	Vector2 low_grid;
	Vector2 high_grid;

	if (std::get<0>(start_grid) < std::get<0>(end_grid))
	{
		low_grid.x = std::get<0>(start_grid);
		high_grid.x = std::get<0>(end_grid);
	}
	else
	{
		low_grid.x = std::get<0>(end_grid);
		high_grid.x = std::get<0>(start_grid);
	}
	
	if (std::get<1>(start_grid) < std::get<1>(end_grid))
	{
		low_grid.y = std::get<1>(start_grid);
		high_grid.y = std::get<1>(end_grid);
	}
	else
	{
		low_grid.y = std::get<1>(end_grid);
		high_grid.y = std::get<1>(start_grid);
	}

	if (m_start_tile)
	{
		if (update_tile)
		{
			if (m_tile_type == TileType::Road)
			{
				for (auto tile : pathfinding(*m_start_tile, *m_end_tile, *m_world_manager))
				{
					int index = m_world_manager->getIndex(tile);

					m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type = m_tile_type;
				}
				return;
			}
		}
	}

	for (int i = low_grid.x; i <= high_grid.x; i++)
	{
		for (int j = low_grid.y; j <= high_grid.y; j++)
		{
			int index = m_world_manager->getIndex(Vector2(i, j));

			if (currently_selecting)
			{
				m_world_manager->getWorld()[m_plane][index]->setSelected(true);
			}
			else if (update_tile)
			{
				m_world_manager->getWorld()[m_plane][index]->getGridData().m_zone_type = m_zone_type;
				m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type = m_tile_type;
			}
		}
	}
}

/// <summary>
/// Pathfinding algorithm for placing roads
/// </summary>
void SelectionHandler::pathfindRoads()
{
	CONSOLE(DEBUG,"TODO");
}

/// <summary>
/// Find the nearest tile in relation to the converted mouse position
/// </summary>
/// <param name="mouse_pos">The mouse position in world space</param>
/// <returns>The nearest tile</returns>
GridLocation* SelectionHandler::findNearestTile(Vector3 mouse_pos)
{
	float shortest_distance = 100000;
	Vector2 pos;

	for (auto& plane : m_world_manager->getWorld())
	{
		if (plane.first == PlaneType::Earth) continue;

		for (auto& tile : plane.second)
		{
			Vector3 world_pos = tile->getTile().GetPos();
			Vector2 radius_pos(world_pos.x, world_pos.z);

			float x_dis = (radius_pos.x - mouse_pos.x);
			float y_dis = (radius_pos.y - mouse_pos.z);

			float length = std::pow(x_dis, 2) + std::pow(y_dis, 2);
			float rad = std::pow(radius, 2);

			if (length < rad)
			{
				if (length < shortest_distance)
				{
					shortest_distance = length;
					pos.x = std::get<0>(tile->getGridData().m_position);
					pos.y = std::get<1>(tile->getGridData().m_position);
					m_plane = plane.first;
				}
			}

			tile->setSelected(false);
		}
	}

	CONSOLE(INFO, { to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(int(m_plane)) });
	
	m_world_manager->getWorld()[m_plane][m_world_manager->getIndex(pos)]->setSelected(true);

	return &*m_world_manager->getWorld()[m_plane][m_world_manager->getIndex(pos)];
}
