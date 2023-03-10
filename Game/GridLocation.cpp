#include "pch.h"
#include "GridLocation.h"

GridLocation::GridLocation()
{

}

GridLocation::GridLocation(Microsoft::WRL::ComPtr<ID3D11Device1> _device, DirectX::IEffectFactory* _fxFactory, Vector2 _pos)
{
    m_tile = new TileGO("TileOBJ2", _device.Get(), _fxFactory, Vector3(_pos.x * 40.0f, 0.0f, _pos.y * 40.0f), 0, 0, 0);

    m_grid_data.m_position = _pos;
}

GridLocation::~GridLocation()
{
    delete m_tile;
    m_tile = nullptr;
}

GridData& GridLocation::getGridData()
{
    return m_grid_data;
}

TileGO& GridLocation::getTile()
{
    return *m_tile;
}
