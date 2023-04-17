#pragma once
#include "Manager.h"
#include "SoulManager.h"

class ReincarnationManager : public Manager
{
public:
    void update(GameData& _game_data) override;
    void awake() override;

    EMBO TurnIntoEMBO(Soul* _soul); // return the EMBO with all the soul data
    Soul TurnIntoSoul(EMBO* _embo);  // Save the poor soul from the life on Earth
    
private:
    std::vector <std::shared_ptr<EMBO>> test_Earth_Souls;
    std::vector <std::shared_ptr<Soul>> test_Heven_wanderingSouls;
};
