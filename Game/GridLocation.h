#pragma once

#include "GridData.h"
#include "TileGO.h"
#include "GPGO.h"

// This object houses grid data and the object for it
class GridLocation
{
public:
	GridLocation();
	GridLocation(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector2 pos, int plane);
	~GridLocation();

	void createBuilding(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device);

	GridData& getGridData();
	GPGO& getTile();

	void update();

private:
	GridData m_grid_data;

	GPGO* m_tile;
};

