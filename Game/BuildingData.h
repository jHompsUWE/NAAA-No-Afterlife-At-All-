#pragma once

#include "BuildingSpecies.h"
#include "Capacity.h"

#include "GridData.h"
#include "SoulManager.h"
#include "Listener.h"
#include "GameManager.h"

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
	std::string m_type = "type";
	int				m_cost = 30;
	Capacity		m_capacity = { 10,0 };
	BuildingData 	m_data = {};

	std::vector<GridData*> housing_points;

	virtual void update()
	{
		// Update building
	}

	void delete_reference()
	{
		for (GridData* tile : housing_points)
		{
			tile->nuke();
		}

		delete this;
	}
};

struct TierBuiding : GenericBuilding
{
	std::string		m_tiername	= "basic";
	TierBuiding*	m_nextUpgrade = nullptr;
	int				m_upgradeCost = 40000;
};

struct GateBuilding : GenericBuilding
{
	GateBuilding(GenericBuilding gen_building) : GenericBuilding(gen_building) {};

	void update() override
	{
		//if (!housing_points.empty())
		{
			CONSOLE(DEBUG, "update gate");

			Event event{};
			event.type = EventType::ADD_SOUL;

			event.payload.add_soul.plane = housing_points[0]->m_plane;
			event.payload.add_soul.x = std::get<0>(housing_points[0]->m_position);
			event.payload.add_soul.y = std::get<1>(housing_points[0]->m_position);

			GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
		}

		
	}
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
				if (build["Tier"] == tier)
				{
					building.m_buildingname = build["Name"];
					building.m_buildingdesc = build["Desc"];
					building.m_placeable = _planetype;
					building.m_nextUpgrade;
					building.m_upgradeCost;
					building.m_tiername = build["Name"];

					building.m_type = _type;
						

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
	
