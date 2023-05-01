#pragma once
#include "Manager.h"
#include "BadThings/BadThingsBOP.h"
#include "BadThings/BadThingsParent.h"

class BadThingsManager : public Manager
{
public:
    BadThingsManager();
    ~BadThingsManager();

    void update(GameData& _game_data) override;
    
private:
    std::vector<BadThingsParent> badThingsVector;

    std::unique_ptr<BadThingsBOP> badThingsBOP;
};
