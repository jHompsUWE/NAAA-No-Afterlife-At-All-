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
	if (m_GD->m_mouseButtons.leftButton)
	{
		if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			Vector3 v = XMVector3Unproject(XMVectorSet(m_GD->m_MS.x, m_GD->m_MS.y, 0.0f, 0.0f), 0, 0, 800, 600, -10000, 10000, tps_cam.GetProj(), tps_cam.GetView(), XMMatrixIdentity());

			m_start_pos = convertPosition(v, tps_cam);	
		}
		if (m_GD->m_mouseButtons.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			Vector3 v = XMVector3Unproject(XMVectorSet(m_GD->m_MS.x, m_GD->m_MS.y, 0.0f, 0.0f), 0, 0, 800, 600, -10000, 10000, tps_cam.GetProj(), tps_cam.GetView(), XMMatrixIdentity());

			m_end_pos = convertPosition(v, tps_cam);

			float x_diff = m_end_pos.x - m_start_pos.x;
			float z_diff = m_end_pos.z - m_start_pos.z;

			cout << "start: " << m_start_pos.x << " , " << m_start_pos.y << " , " << m_start_pos.z << " End: " << m_end_pos.x << " , " << m_end_pos.y << " , " << m_end_pos.z << endl;

			for (auto& tile : m_world[m_plane])
			{
				bool in_x = false;
				bool in_z = false;

				if ((m_start_pos.x < tile->getTile().GetPos().x && tile->getTile().GetPos().x < m_end_pos.x)
					|| (m_end_pos.x < tile->getTile().GetPos().x && tile->getTile().GetPos().x < m_start_pos.x))
				{
					in_x = true;
				}
				if ((m_start_pos.z < tile->getTile().GetPos().z && tile->getTile().GetPos().z < m_end_pos.z)
					|| (m_end_pos.z < tile->getTile().GetPos().z && tile->getTile().GetPos().z < m_start_pos.z))
				{
					in_z = true;
				}

				if (in_x && in_z)
				{
					tile->getGridData().m_zone_type = m_zone_type;
					tile->getGridData().m_tile_type = m_tile_type;
				}
			}
		}
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
