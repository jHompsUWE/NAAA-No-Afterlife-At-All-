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

static GenericBuilding building(PlaneType _planetype,string _type,int tier)
{
	auto buildings = GameManager::get()->getFileManagerV2()->GetJson("buildings_table");
	TierBuiding building;
	std:: string splane;
	if (_planetype == PlaneType::Heaven)
	{
		splane = "Heaven";
	}
	else if (_planetype == PlaneType::Hell)
	{
		splane = "Hell";
	}


	for (auto build : (*buildings))
	{
		if (build["TYPE"] == _type)
		{
			std::cout << "Type\n";
			if (build["Zone"] == splane)
			{
				std::cout << "Zone\n";
				if (build["tier"] == tier)
				{
					building.m_buildingname = build["Name"];
					building.m_buildingdesc = build["Desc"];
					building.m_placeable = _planetype;
					building.m_nextUpgrade;
					building.m_upgradeCost;
					building.m_tiername = build["Name"];
						

					std::cout << "Desc " << building.m_buildingdesc << " " << build["Desc"] << "\n";
					int size = build["Size"];
					switch (size)
					{
					case 1:
						{
							building.m_data.m_building_species = BuildingSpecies::One;
							break;
						}
					case 2:
						{
							building.m_data.m_building_species = BuildingSpecies::Two;
							break;
						}
					case 3:
						{
							building.m_data.m_building_species = BuildingSpecies::Three;
							break;
						}
					case 4:
						{
							building.m_data.m_building_species = BuildingSpecies::Four;
							break;
						}
					default:
						{
							building.m_data.m_building_species = BuildingSpecies::None;
						}
					}
					building.m_data.m_size			= build["Size"];
					building.m_data.m_vibe			= build["Vibe"];
					building.m_data.m_vibe_radius	= build["radi"];
					return building;
				}
			}
		}
	}
}
	
