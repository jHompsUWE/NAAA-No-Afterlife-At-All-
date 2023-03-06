#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "Manager.h"


struct Soul
{

};

class SoulManager : public Manager
{
	std::vector	<std::shared_ptr<Soul>> m_Hell_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Hell_wanderingSouls;

	std::vector	<std::shared_ptr<Soul>> m_Heven_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Heven_wanderingSouls;
	
	
	std::vector <std::shared_ptr<Soul>> m_Earth_Souls;



public:
	
	void AddSoul(DirectX::SimpleMath::Vector2 location,int plane);			// add a soul at this location
	void Wander();						// run the soul road movement
	void ZoneCheck();					//check if zone is attached
	int TotalSoulsAmmount(int plane);	//get souls per plane
	int TotalSoulsAmmount();			//get souls total overall


										// Inherited via Manager
	virtual void update() override;
	virtual void awake() override;
};



