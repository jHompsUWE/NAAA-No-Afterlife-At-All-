#include "pch.h"
#include "GridLocation.h"

GridLocation::GridLocation()
{

}

GridLocation::GridLocation(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector2 _pos, int plane)
{
    float* params = new float[3];
    params[0] = 25.0f; params[1] = 5.0f; params[2] = 25.0f;
    m_tile = new GPGO(_device.Get(), GPGO_BOX, (float*)&Colors::Red, params, 
        Vector3(_pos.x * 25.0f + plane * 130.0f, 0.0f, _pos.y * 25.0f + plane * 130.0f));

    m_grid_data.m_position = _pos;
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
    
}