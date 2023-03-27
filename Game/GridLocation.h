#pragma once

#include "GridData.h"
#include "TileGO.h"
#include "GPGO.h"

/////////////////////////////////////////////////
/// This Class houses the in-world tile object and an instance of the struct
/// For all the behind the scenes data used in grid locations
/// There is currently 
/////////////////////////////////////////////////
class GridLocation
{
public:
	GridLocation();
	GridLocation(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector2 _world_pos, PlaneType plane, 
		Vector2 grid_pos);
	~GridLocation();

	void createBuilding(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device);

	GridData& getGridData();
	GPGO& getTile();

	bool getSelected();
	void setSelected(bool _selected);

	void nuke();

	void update();

private:
	GridData m_grid_data;

	GPGO* m_tile;

	bool m_selected;
};

