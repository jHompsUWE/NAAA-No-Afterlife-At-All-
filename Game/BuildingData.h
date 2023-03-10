#pragma once

#include "BuildingSpecies.h"

struct BuildingData
{
	BuildingSpecies m_building_species = BuildingSpecies::None;
	int m_vibe_radius = 1;
	int m_vibe = 0;
	int size = 1;

	// Used for rocks when implemented
	bool m_energised = false;

	// Used for production when implemented
	bool m_locked;
	int m_lock_cost;
};