#pragma once
#include <memory>
#include <vector>

struct Soul
{

};

class SoulManager
{
	std::vector	<std::shared_ptr<Soul>> m_Hell_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Hell_wanderingSouls;

	std::vector	<std::shared_ptr<Soul>> m_Heven_ZonedSouls;
	std::vector <std::shared_ptr<Soul>> m_Heven_wanderingSouls;
	
	
	std::vector <std::shared_ptr<Soul>> m_Earth_Souls;



public:
	void AddSoul(int x, int y ,int plane);			// add a soul at this location
	void Wander();						// run the soul road movement
	void ZoneCheck();					//check if zone is attached
	int TotalSoulsAmmount(int plane);	//get souls per plane
	int TotalSoulsAmmount();			//get souls total overall


};



