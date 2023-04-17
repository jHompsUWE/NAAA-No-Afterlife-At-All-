#include "pch.h"
#include "SelectionHandler.h"
#include "Mouse.h"
#include <math.h>

#include "Pathfinding.h"
#include "BuildingData.h"

SelectionHandler::SelectionHandler(std::shared_ptr<WorldManager> _world_manager, GameData* _GD, 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _d3dContext) :
	m_world_manager(_world_manager), m_GD(_GD), m_d3dContext(_d3dContext),
	m_plane(PlaneType::Heaven), m_selection_type(SelectionType::None), currently_selecting(false),
	update_tile(false), m_tile_type(TileType::None), m_zone_type(ZoneType::None)
{
	
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

	switch (m_selection_type)
	{
	case SelectionType::Zone:
		updateTiles();
		break;
	case SelectionType::Building:
		updateBuilding();
		break;
	case SelectionType::Road:
		updateRoads();
		break;
	case SelectionType::Nuke:
		updateNuke();
		break;
	default:
		// Do nothing if there's no selection type
		break;
	}
}

void SelectionHandler::draw(DrawData* _DD)
{
	if (temp_building)
	{
		temp_building->Draw(_DD);
	}
}

void SelectionHandler::onEvent(const Event& event)
{
	switch (event.type)
	{
		case EventType::GREEN_ZONING:
		{
			m_zone_type = ZoneType::Green;
			m_tile_type = TileType::Zone;

			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::YELLOW_ZONING:
		{
			m_zone_type = ZoneType::Yellow;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::ORANGE_ZONING:
		{
			m_zone_type = ZoneType::Orange;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::BROWN_ZONING:
		{
			CONSOLE(INFO, "Brown");
			m_zone_type = ZoneType::Brown;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::PURPLE_ZONING:
		{
			m_zone_type = ZoneType::Purple;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::RED_ZONING:
		{
			m_zone_type = ZoneType::Red;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::BLUE_ZONING:
		{
			m_zone_type = ZoneType::Blue;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::GENERIC_ZONING:
		{
			m_zone_type = ZoneType::Generic;
			m_tile_type = TileType::Zone;
			m_selection_type = SelectionType::Zone;
			break;
		}
		case EventType::ROADS:
		{
			m_zone_type = ZoneType::None;
			m_tile_type = TileType::Road;

			m_selection_type = SelectionType::Road;
			break;
		}
		case EventType::GATES:
		{
			m_zone_type = ZoneType::None;
			m_tile_type = TileType::Building;

			m_selection_type = SelectionType::Building;

			createTempBuilding();
			break;
		}
		case EventType::NUKE_BUTTON:
		{
			m_selection_type = SelectionType::Nuke;
		}
		default:
		{
			break;
		}
	}

	if (m_selection_type != SelectionType::Building) {
		delete temp_building; temp_building = nullptr;
		delete temp_building_stats; temp_building_stats = nullptr;
	}
}

void SelectionHandler::calculateGridSpaces(Vector2& low_grid, Vector2& high_grid)
{
	std::tuple<int, int> start_grid;

	if (m_start_tile)
	{
		start_grid = m_start_tile->getGridData().m_position;
	}

	std::tuple<int, int> end_grid = m_end_tile->getGridData().m_position;

	bool x_increase = false;
	bool y_increase = false;

	if (std::get<0>(start_grid) < std::get<0>(end_grid))
	{
		low_grid.x = float(std::get<0>(start_grid));
		high_grid.x = float(std::get<0>(end_grid));
	}
	else
	{
		low_grid.x = float(std::get<0>(end_grid));
		high_grid.x = float(std::get<0>(start_grid));
	}

	if (std::get<1>(start_grid) < std::get<1>(end_grid))
	{
		low_grid.y = float(std::get<1>(start_grid));
		high_grid.y = float(std::get<1>(end_grid));
	}
	else
	{
		low_grid.y = float(std::get<1>(end_grid));
		high_grid.y = float(std::get<1>(start_grid));
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
	Vector2 low_grid;
	Vector2 high_grid;

	calculateGridSpaces(low_grid, high_grid);

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

				// Don't overwrite the tile/zone type if there's a building there already
				if (m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type == TileType::None)
				{
					m_world_manager->getWorld()[m_plane][index]->getGridData().m_zone_type = m_zone_type;
					m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type = m_tile_type;
				}
			}
		}
	}
}

/// <summary>
/// Update the selected tiles to be roads. Also setting connected in AoE around them
/// </summary>
void SelectionHandler::updateRoads()
{
	if (m_start_tile)
	{
		auto tiles = pathfinding(*m_start_tile, *m_end_tile, *m_world_manager);

		if (currently_selecting)
		{
			for (auto tile : tiles)
			{
				int index = m_world_manager->getIndex(tile);

				m_world_manager->getWorld()[m_plane][index]->setSelected(true);
			}
		}

		else if (update_tile)
		{
			for (auto tile : tiles)
			{
				int index = m_world_manager->getIndex(tile);

				// Stop placing roads if building is hit
				if (m_world_manager->getWorld()[m_plane][index]->getGridData().m_building)
				{
					break;
				}

				m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type = m_tile_type;

				m_world_manager->setConnected(*m_world_manager->getWorld()[m_plane][index]);
			}
		}
	}
}

/// <summary>
/// Update the tiles for the building that's being placed.
/// </summary>
void SelectionHandler::updateBuilding()
{
	if (update_tile)
	{
		// func(PlaneType m_plane, whatever tier);

		if (temp_building)
		{
			if (!checkBuildingPositioning()) { return; }

			//checkBuildingPositioning();

			int size = temp_building_stats->m_data.m_size;

			Vector2 pos(std::get<0>(m_end_tile->getGridData().m_position),
				std::get<1>(m_end_tile->getGridData().m_position));

			for (int i = pos.y; i > pos.y - size; i--)
			{
				for (int j = pos.x; j > pos.x - size; j--)
				{
					int index = m_world_manager->getIndex(Vector2(j, i));

					m_world_manager->getWorld()[m_plane][index]->getGridData().m_building_data =
						temp_building_stats;

					m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type = m_tile_type;

					//m_world_manager->getWorld()[m_plane][index]->getGridData().m_building = temp_building;

					temp_building_stats->housing_points.push_back(&m_world_manager->getWorld()[m_plane][index]->getGridData());

					std::cout << i << " " << j << std::endl;
				}
			}

			m_end_tile->getGridData().m_building = temp_building;

			m_end_tile->getGridData().m_building->GetColour().A(1.f);

			temp_building = nullptr;
			temp_building_stats = nullptr;
			createTempBuilding();
		}

		//m_end_tile->createBuilding(m_d3dContext);
	}
	else
	{
		updateTempPos();
		temp_building->SetPos(temp_building_pos);
		temp_building->UpdateWorldPos();
	}
}

/// <summary>
/// Check to ensure all parts of a building are free, so it can be placed
/// </summary>
/// <returns> bool for if it's free or not</returns>
bool SelectionHandler::checkBuildingPositioning()
{
	int size = temp_building_stats->m_data.m_size;

	Vector2 pos(std::get<0>(m_end_tile->getGridData().m_position),
		std::get<1>(m_end_tile->getGridData().m_position));

	for (int i = pos.y; i > pos.y - size; i--)
	{
		for (int j = pos.x; j > pos.x - size; j--)
		{
			int index = m_world_manager->getIndex(Vector2(j, i));

			if (!m_world_manager->withinRange(Vector2(j, i))) { return false; }

			if (m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type != TileType::None)
			{
				return false;
			}

			std::cout << i << " " << j << std::endl;
		}
	}

	return true;
}

void SelectionHandler::updateNuke()
{
	Vector2 low_grid;
	Vector2 high_grid;

	calculateGridSpaces(low_grid, high_grid);

	bool road_deleted = false;

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
				// NUKE EVERYTHING
				if (m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type == TileType::Road)
				{
					road_deleted = true;
				}

				if (m_world_manager->getWorld()[m_plane][index]->getGridData().m_tile_type == TileType::Building)
				{
					m_world_manager->getWorld()[m_plane][index]->getGridData().m_building_data->delete_reference();
				}
				else
				{
					m_world_manager->getWorld()[m_plane][index]->nuke();
				}
				
			}
		}
	}

	if (road_deleted)
	{
		m_world_manager->resetConnections();
	}
}

void SelectionHandler::createTempBuilding()
{
	temp_building_stats = new GateBuilding(building(m_plane, "GATES", 1));

	//temp_building_stats = 

	float* params = new float[3];

	params[0] = 15.0f;
	params[0] = 15.0f + 25.f * (temp_building_stats->m_data.m_size - 1);

	updateTempPos();

	temp_building = new GPGO(m_d3dContext.Get(), GPGO_CUBE, (float*)&Colors::DarkOrange, params, temp_building_pos);

	temp_building->GetColour().A(0.5f);
}

void SelectionHandler::updateTempPos()
{
	temp_building_pos = m_end_tile->getTile().GetPos();

	temp_building_pos.y += 10;
	temp_building_pos.x -= (float(temp_building_stats->m_data.m_size - 1)) * 12.5f;
	temp_building_pos.z -= (float(temp_building_stats->m_data.m_size - 1)) * 12.5f;
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
	
	m_world_manager->getWorld()[m_plane][m_world_manager->getIndex(pos)]->setSelected(true);

	return &*m_world_manager->getWorld()[m_plane][m_world_manager->getIndex(pos)];
}
