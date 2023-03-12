#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "Manager.h"
#include "ImageGO2D.h"
#include "ZoneType.h"
#include "PlaneType.h"


struct Soul
{
	int m_currentcycle;
	int cycles = 10;
	bool reincarnate = true;
	string life;
	Vector2 position;
	ZoneType zonetype;
};

class SoulManager : public Manager
{
	std::vector	<std::shared_ptr<Soul>> m_Hell_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Hell_wanderingSouls;

	std::vector	<std::shared_ptr<Soul>> m_Heven_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Heven_wanderingSouls;
	
	
	std::vector <std::shared_ptr<Soul>> m_Earth_Souls;

public:
	
	void AddSoul(DirectX::SimpleMath::Vector2 location,PlaneType plane = PlaneType::Earth);			// add a soul at this location
	void Wander();																					// run the soul road movement
	void ZoneCheck();																				//check if zone is attached
	int TotalSoulsAmmount(PlaneType plane) const;													//get souls per plane NONE : get souls total overall

																									// Inherited via Manager
	
	virtual void awake() override;
	virtual void update(DX::StepTimer const& _timer) override;
	virtual void lateUpdate(DX::StepTimer const& _timer) override;
};



