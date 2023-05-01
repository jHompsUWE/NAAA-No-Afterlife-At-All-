#pragma once
#include "Manager.h"
#include "SoulManager.h"

class ReincarnationManager : public Manager
{
public:
    bool operator == (const EMBO* _embo) const
    {
        return true;
    }
    
    void update(GameData& _game_data) override;
    void awake(GameData& _game_data) override;

    EMBO TurnIntoEMBO(Soul* _soul); // return the EMBO with all the soul data
    Soul TurnIntoSoul(EMBO* _embo);  // Save the poor soul from the life on Earth

    EMBO SoulToEMBO(Soul& _soul);
    bool EMBOToSoul(EMBO& _embo);    
    
private:    
    std::vector <EMBO*> earthEMBOs;

    std::vector	<Soul*> hellZonedSouls_;
    std::vector <Soul*> hellWanderingSouls_;

    std::vector	<Soul*> heavenZonedSouls_;
    std::vector <Soul*> heavenWanderingSouls_;

    std::vector<std::vector<Soul*>> allContainers;

    void RemoveFromList(EMBO* _embo); 
    void RemoveFromList(Soul* _soul);

    bool compareEMBOs(const EMBO* a, const EMBO* b);
    bool compareSOULs(const Soul* a, const Soul* b);
    void removeMatchingEMBOs(std::vector<EMBO*>& earthEMBOs, const EMBO& target);
    void removeMatchingSOULs(const Soul& target);


    void RemoveEntity(Soul& _soul);
    void RemoveEntity(EMBO& _embo);

    bool doOnce = true;

};
