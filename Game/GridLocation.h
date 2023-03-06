#pragma once

#include "GridData.h"

// Plan to inherit from a 2D/3D class at some point
class GridLocation
{
public:
	GridLocation();


	GridData& getGridData();


private:
	GridData m_grid_data;
};

