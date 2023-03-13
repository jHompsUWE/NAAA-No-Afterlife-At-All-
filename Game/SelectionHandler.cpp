#include "pch.h"
#include "SelectionHandler.h"
#include "Mouse.h"

SelectionHandler::SelectionHandler(std::map<PlaneType, std::vector<std::unique_ptr<GridLocation>>>& _world, GameData* _GD) : m_world(_world), m_GD(_GD)
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
	/*if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		float mouse_x = m_GD->m_MS.x;
		float mouse_y = m_GD->m_MS.y;

		// Window is 800 x 600
		float window_x = 800;
		float window_y = 600;

		float x_pos = mouse_x - window_x / 2;
		float y_pos = mouse_y - window_y / 2;

		float zoom = tps_cam.getZoom();

		std::cout << x_pos << " " << y_pos << std::endl;
	}
	
	if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
	{
		float mouse_x = m_GD->m_MS.x;
		float mouse_y = m_GD->m_MS.y;

		// Window is 800 x 600
		float window_x = 800;
		float window_y = 600;

		float x_pos = mouse_x - window_x / 2;
		float y_pos = mouse_y - window_y / 2;

		float zoom = tps_cam.getZoom();

		std::cout << x_pos << " " << y_pos << std::endl;
	}*/
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
			std::cout << "brown\n";
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
