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
    std::vector <std::shared_ptr<EMBO>> earthEMBOs;

    std::vector	<std::shared_ptr<Soul>> hellZonedSouls_;
    std::vector <std::shared_ptr<Soul>> hellWanderingSouls_;

    std::vector	<std::shared_ptr<Soul>> heavenZonedSouls_;
    std::vector <std::shared_ptr<Soul>> heavenWanderingSouls_;

    std::vector<std::vector<std::shared_ptr<Soul>>> allContainers;

    void RemoveFromList(EMBO* _embo); 
    void RemoveFromList(Soul* _soul); 
	
};
