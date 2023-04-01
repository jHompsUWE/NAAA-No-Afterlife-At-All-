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
#include "BuildingData.h"


using namespace DirectX;
using namespace SimpleMath;

struct GridData
{
	~GridData()
	{
		delete m_building;
		m_building = nullptr;
	}

	void createBuilding(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector3 _pos)
	{
		float* params = new float[3];
		params[0] = 15.0f;
		Vector3 new_pos(_pos.x, _pos.y + 5, _pos.z);
		m_building = new GPGO(_device.Get(), GPGO_CUBE, (float*)&Colors::Green, params, new_pos);

		CONSOLE(INFO, "Created building");
	}

	void Tick(GameData* _GD)
	{
		switch (m_zone_type)
		{
		case ZoneType::None:	m_building->SetColour	(Colors::White.v)		;	break;
		case ZoneType::Generic:	m_building->SetColour	(Colors::Ivory.v)	;	break;
		case ZoneType::Green:	m_building->SetColour	(Colors::Green.v)		;	break;
		case ZoneType::Yellow:	m_building->SetColour	(Colors::Yellow.v)	;	break;
		case ZoneType::Orange:	m_building->SetColour	(Colors::Orange.v)	;	break;
		case ZoneType::Brown:	m_building->SetColour	(Colors::SaddleBrown.v)		;	break;
		case ZoneType::Purple:	m_building->SetColour	(Colors::Magenta.v)	;	break;
		case ZoneType::Red:		m_building->SetColour	(Colors::Red.v)		;	break;
		case ZoneType::Blue:	m_building->SetColour	(Colors::MediumPurple.v)		;	break;
		default: ;
		}
		
		// connected
	}


	void draw(DrawData* _DD)
	{
		if (m_building)
		{
			m_building->Draw(_DD);
		}
	}

	// Placeholder for now until actual class is sorted
	BuildingData m_building_data;
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