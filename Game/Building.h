#pragma once

#include "BuildingData.h"
#include "GPGO.h"

class Building
{
public:
	Building();
	Building(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _device, Vector3 _pos);
	~Building();

	BuildingData& getBuildingData();
	GPGO& getShape();

	void Draw(DrawData* _DD);

private:
	BuildingData m_building_data;

	GPGO* m_shape;
};

