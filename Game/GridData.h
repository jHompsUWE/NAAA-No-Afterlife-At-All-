#pragma once

#include <d3d11_1.h>
#include <Model.h>
#include <iostream>
#include <tuple>
#include "SimpleMath.h"

#include "TileType.h"
#include "ZoneType.h"
#include "PlaneType.h"
#include "GPGO.h"


struct GenericBuilding;


using namespace DirectX;
using namespace SimpleMath;

struct GridData
{
	~GridData()
	{
		delete m_building_data;
		m_building_data = nullptr;

		delete m_building;
		m_building = nullptr;
	}

	void createBuilding(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector3 _pos)
	{
		float* params = new float[3];
		params[0] = 15.0f;
		Vector3 new_pos(_pos.x, _pos.y + 5, _pos.z);
		m_building = new GPGO(_device.Get(), GPGO_CUBE, (float*)&Colors::Green, params, new_pos);

		std::cout << "Created building" << std::endl;
	}

	void nuke()
	{
		m_building_data = nullptr;
		delete m_building;
		m_building = nullptr;

		m_tile_type = TileType::None;
		m_zone_type = ZoneType::None;

	}

	void draw(DrawData* _DD)
	{
		if (m_building)
		{
			m_building->Draw(_DD);
		}
	}

	// Placeholder for now until actual class is sorted
	GenericBuilding* m_building_data = nullptr;
	GPGO* m_building = nullptr;

	TileType m_tile_type = TileType::None;
	ZoneType m_zone_type = ZoneType::None;
	std::tuple<int, int> m_position = { 0, 0 };

	bool m_connected = false;
	PlaneType m_plane = PlaneType::None;
	int m_vibe = 0;

	int m_efficiency = 0;

	int m_max_capacity = 10;
	int m_current_capacity = 0;
};