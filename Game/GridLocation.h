#pragma once

#include "GridData.h"
#include "TileGO.h"

// Plan to inherit from a 2D/3D class at some point
class GridLocation
{
public:
	GridLocation();
	GridLocation(Microsoft::WRL::ComPtr<ID3D11Device1> _device, DirectX::IEffectFactory* _fxFactory, Vector2 pos);
	~GridLocation();

	GridData& getGridData();
	TileGO& getTile();

private:
	GridData m_grid_data;

	TileGO* m_tile;
};

