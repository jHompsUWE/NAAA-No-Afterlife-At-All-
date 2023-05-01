#include "pch.h"
#include "BadThingsParent.h"


void BadThingsParent::TriggerBadThing(GameData& game_data)
{
}

void BadThingsParent::ResetBadThing()
{
    doOnce = true;
    year = 0;
    finished = false;
}
