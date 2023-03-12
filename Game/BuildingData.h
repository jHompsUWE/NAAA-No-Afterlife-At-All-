#pragma once

#include "BuildingSpecies.h"
#include "Capacity.h"

struct BuildingData
{
	BuildingSpecies m_building_species = BuildingSpecies::None;
	int				m_vibe_radius = 1;
	int				m_vibe = 0;
	int				m_size = 1;

	// Used for rocks when implemented
	bool			m_energised = false;

	// Used for production when implemented
	bool			m_locked = false;
	int				m_lock_cost = 30;
};

struct GenericBuilding
{
	PlaneType		m_placeable;
	std::string		m_buildingname = "buildingname";
	std::string		m_buildingdesc = "building decription";
	int				m_cost = 30;
	Capacity		m_capacity = { 10,0 };
	BuildingData	m_data = {};
};

struct TierBuiding : GenericBuilding
{
	std::string		m_tiername	= "basic";
	TierBuiding*	m_nextUpgrade = nullptr;
	int				m_upgradeCost = 40000;
};