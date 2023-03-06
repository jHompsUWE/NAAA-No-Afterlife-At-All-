#pragma once

#include <d3d11_1.h>
#include "SimpleMath.h"

#include "TileType.h"
#include "ZoneType.h"
#include "PlaneType.h"
#include "Building.h"

using namespace DirectX;
using namespace SimpleMath;

struct GridData
{
	GridData()
	{
		m_stored_building = new Building;
	}

	~GridData()
	{
		delete m_stored_building;
		m_stored_building = nullptr;
	}

	// Placeholder for now until actual class is sorted
	Building* m_stored_building = nullptr;

	TileType m_tile_type = TileType::None;
	ZoneType m_zone_type = ZoneType::None;
	Vector2 m_position = Vector2::Zero;

	bool m_connected = false;
	PlaneType m_plane = PlaneType::None;
	int m_vibe = 0;

	int m_efficiency;
};