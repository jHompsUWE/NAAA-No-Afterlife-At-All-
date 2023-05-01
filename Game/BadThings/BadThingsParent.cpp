#include "pch.h"
#include "BadThingsParent.h"


BadThingsParent::BadThingsParent()
= default;

void BadThingsParent::TriggerBadThing(GameData& game_data)
{
}

void BadThingsParent::ResetBadThing()
{
    doOnce = true;
    year = 0;
    finished = false;
}
