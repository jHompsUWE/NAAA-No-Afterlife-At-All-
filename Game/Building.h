#pragma once

#include "BuildingData.h"

class Building
{
public:
	BuildingData& getBuildingData();
private:
	BuildingData m_building_data;
};

