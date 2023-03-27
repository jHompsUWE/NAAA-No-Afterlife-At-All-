#include "pch.h"
#include "GridLocation.h"

GridLocation::GridLocation() : m_tile(nullptr)
{

}

/// <summary>
/// Constructor allowing for the creation of a grid location.
/// </summary>
/// <param name="_device">Takes the DirectX3D11 device context.</param>
/// <param name="_pos">Grid coordinate for world positioning.</param>
/// <param name="plane">The world plane used for positioning during world creation.</param>
GridLocation::GridLocation(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector2 _world_pos, PlaneType plane,
	Vector2 grid_pos)
{
    float* params = new float[3];
    params[0] = 25.0f; params[1] = 5.0f; params[2] = 25.0f;
    m_tile = new GPGO(_device.Get(), GPGO_BOX, (float*)&Colors::White, params, 
        Vector3(_world_pos.x * 25.5f, 0.0f, _world_pos.y * 25.5f));

    m_grid_data.m_position = std::make_tuple<int, int>(int(grid_pos.x), int(grid_pos.y));

	m_grid_data.m_plane = plane;
}

GridLocation::~GridLocation()
{
    delete m_tile;
    m_tile = nullptr;
}

void GridLocation::createBuilding(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device)
{
    m_grid_data.createBuilding(_device, m_tile->GetPos());
}

GridData& GridLocation::getGridData()
{
    return m_grid_data;
}

GPGO& GridLocation::getTile()
{
    return *m_tile;
}

bool GridLocation::getSelected() { return m_selected; }
void GridLocation::setSelected(bool _selected) { m_selected = _selected; }

void GridLocation::nuke()
{
	m_grid_data.nuke();
}

void GridLocation::update()
{
	switch (m_grid_data.m_zone_type)
	{
	case ZoneType::None:	m_tile->SetColour(Colors::White.v);	break;
	case ZoneType::Generic:	m_tile->SetColour(Colors::Ivory.v);	break;
	case ZoneType::Green:	m_tile->SetColour(Colors::Green.v);	break;
	case ZoneType::Yellow:	m_tile->SetColour(Colors::Yellow.v);	break;
	case ZoneType::Orange:	m_tile->SetColour(Colors::Orange.v);	break;
	case ZoneType::Brown:	m_tile->SetColour(Colors::SaddleBrown.v);	break;
	case ZoneType::Purple:	m_tile->SetColour(Colors::Magenta.v);	break;
	case ZoneType::Red:		m_tile->SetColour(Colors::Red.v);	break;
	case ZoneType::Blue:	m_tile->SetColour(Colors::MediumPurple.v);	break;
	default:;
	}

	if (m_grid_data.m_tile_type == TileType::Road)
	{
		m_tile->SetColour(Colors::Black.v);
	}

	if (m_grid_data.m_tile_type == TileType::Gate)
	{
		m_tile->SetColour(Colors::Aquamarine.v);
	}

	// Make zone grayer if it's not connected
	if (m_grid_data.m_tile_type == TileType::Zone)
	{
		if (!m_grid_data.m_connected)
		{
			m_tile->SetColour(Color(m_tile->GetColour().x * 0.35f, m_tile->GetColour().y * 0.35f, m_tile->GetColour().z * 0.35f));
		}
	}

	if (m_selected)
	{
		m_tile->SetColour(Color(m_tile->GetColour().x * 0.75f, m_tile->GetColour().y * 0.75f, m_tile->GetColour().z * 0.75f));
	}
}