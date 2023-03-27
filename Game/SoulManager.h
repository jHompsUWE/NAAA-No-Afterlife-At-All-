#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "Manager.h"
#include "ImageGO2D.h"
#include "ZoneType.h"
#include "PlaneType.h"

#include "GameManager.h"

enum Fate
{
	// SUMA	ists is multiple afterlifes for each reward and/or reward
	// ALF	ists no reincarnation
	HANA_ALF__SUMA_ISTS,	//multiple punishments and multiple rewards
	HOHO_ALF__SUMA_ISTS,	//multiple punishments  or multiple rewards
	OPRA_ALF__SUMA_ISTS,	//multiple punishments
	OCRA_ALF__SUMA_ISTS,	//multiple rewards

	// RALF	ists no reincarnation
	HAHA_RALF_SUMA_ISTS,	//multiple punishments and multiple rewards
	HOHO_RALF_SUMA_ISTS,	//multiple punishments  or multiple rewards
	OPRA_RALF_SUMA_ISTS,	//multiple punishments
	OCRA_RALF_SUMA_ISTS,	//multiple rewards
	

	// SUSA	ists is one punishement and/or one reward singular 
	// AlF	ists  no reincarnation
	HANA_ALF__SUSA_ISTS,	//one punishment and one reward
	HOHO_ALF__SUSA_ISTS,	//one punishment or  one reward
	OPRA_ALF__SUSA_ISTS,	//one punishement
	OCRA_ALF__SUSA_ISTS,	//one reward

	// Ralf	ists do reincarnate
	HAHA_RALF_SUSA_ISTS,	//one punishment and one reward
	HOHO_RALF_SUSA_ISTS,	//one punishment or  one reward
	OPRA_RALF_SUSA_ISTS,	//one punishement
	OCRA_RALF_SUSA_ISTS,	//one reward
};


struct EMBO
{
	Fate fate;
};

struct Soul
{
	int m_currentcycle;
	int total_cycles = 1;
	int current_cycles = 1;
	bool reincarnate = true;
	int fate;
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
	virtual void update(GameData& _game_data) override;
	virtual void lateUpdate(GameData& _game_data) override;

private:
	float m_time;
};



