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
GridLocation::GridLocation(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector2 _pos, PlaneType plane)
{
    float* params = new float[3];
    params[0] = 25.0f; params[1] = 5.0f; params[2] = 25.0f;
    m_tile = new GPGO(_device.Get(), GPGO_BOX, (float*)&Colors::White, params, 
        Vector3(_pos.x * 25.0f, 0.0f, _pos.y * 25.0f));

    m_grid_data.m_position = _pos;

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
}