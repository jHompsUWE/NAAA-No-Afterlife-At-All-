#pragma once
#include "BadThingsParent.h"


class BadThingsBOP : public BadThingsParent
{
public:
    BadThingsBOP();
    void TriggerBadThing(GameData& game_data) override;
    void ResetBadThing() override;

private:
    int randomPosition = 0;    
};
