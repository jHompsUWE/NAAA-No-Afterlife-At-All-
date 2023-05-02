#pragma once
#include <memory>
#include <vector>
//#include <d3d11_1.h>
#include <SimpleMath.h>
#include "Manager.h"
//#include "ImageGO2D.h"
//#include "ZoneType.h"
//#include "PlaneType.h"

//#include "GameManager.h"
#include "WorldManager.h"

enum Fate
{
	// SUMA	ists is multiple afterlifes for each reward and/or reward
	// ALF	ists no reincarnation
	HANA_ALF__SUMA_ISTS = 1,//multiple punishments and multiple rewards
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
	int value;
	int earth_belief;
	int m_yearsleft ;
	int m_totalyears;
	bool m_reincarnate = true;
	int m_fate;
	Vector2 m_position;
	ZoneType m_zonetype;
	int m_total_cycles = 1;
};

struct Soul : EMBO
{
	int m_currentcycle = 0;
	int m_total_cycles = 1;
	bool m_both = false;
	string m_life;
	Vector2 m_position;
	ZoneType m_zonetype;
};

struct SoulComparator {
	const Soul* soulToFind;
	SoulComparator(const Soul* & soul) : soulToFind(soul) {}
	bool operator()(const Soul* & soulPtr) const {
		return soulPtr->value == soulToFind->value;
	}
};

class SoulManager : public Manager, public Listener
{
public:
	std::vector	<Soul*> m_Hell_ZonedSouls;
	std::vector <Soul*> m_Hell_wanderingSouls;

	std::vector	<Soul*> m_Heven_ZonedSouls;
	std::vector <Soul*> m_Heven_wanderingSouls;
	
	
	std::vector <EMBO*> m_Earth_Souls;

	explicit SoulManager(shared_ptr<WorldManager> world_manager);
	void AddSoul();			// add a soul at this location
	void AddEMBO();			// add a soul at this location
	void onEvent(const Event& event) override;
	void zone_checking(Soul* soul, PlaneType plane);
	void wandering(Soul* _soul,PlaneType _plane);
	void Wander();																					// run the soul road movement
	void ZoneCheck();																				//check if zone is attached
	int TotalSoulsAmmount(PlaneType _plane) const;													//get souls per plane NONE : get souls total overall
	
	virtual void awake(GameData& _game_data) override;
	virtual void update(GameData& _game_data) override;
	virtual void lateUpdate(GameData& _game_data) override;

private:
	float m_time = 0.f;
	shared_ptr<WorldManager> world_manager;
};



