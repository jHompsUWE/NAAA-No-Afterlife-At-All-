#pragma once

#include <d3d11_1.h>
#include "SimpleMath.h"

#include "TileType.h"
#include "ZoneType.h"
#include "GameObject2D.h"


using namespace DirectX;
using namespace SimpleMath;

struct GridData
{
	// Placeholder for now until actual class is sorted
	GameObject2D* m_stored_building;

	TileType m_tile_type = TileType::None;
	ZoneType m_zone_type = ZoneType::None;
	Vector2 m_position = Vector2::Zero;

	bool m_connected = false;
	int plane = 0;
	int vibes = 0;
};