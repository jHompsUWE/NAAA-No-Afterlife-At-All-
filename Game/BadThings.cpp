#include "pch.h"
#include "BadThings.h"

void BadThings::triggerBadThing(BadThingsTypes _badThingType)
{
    //BadThingsVector_.push_back(_badThingType);
}

void BadThings::removeBadThing(BadThingsTypes _badThingType)
{
}

void BadThings::update(GameData& _game_data)
{
    for (BadThingVector::const_iterator badThingIt = BadThingsVector_.begin(),
       end = BadThingsVector_.end();
        badThingIt != end;
       ++badThingIt)
    {
        (*badThingIt)->update();
    }
}
