#pragma once
#include "../GameManager.h"

enum BadThingsTypes
{
    NONE,
    BIRDS_OF_PARADISE,
    BATS_OUT_OF_HELL,
    HEAVEN_GETS_THE_BLUES,
    DISCO_INFERNO,
    PARADISE_PAIR_O_DANCE,
    HELL_FREEZES_OVER,
    HEAEN_NOSE,
    HELL_IN_A_HANDBASKET,
};

class BadThingsParent
{
public:
    BadThingsParent() = default;
    virtual ~BadThingsParent() = default;
    virtual void TriggerBadThing(GameData& game_data);
    virtual void ResetBadThing();

    BadThingsTypes GetType() const{return badThingType;}

    bool hasFinished() const{return finished;}
    
protected:
    BadThingsTypes badThingType = NONE;
    bool doOnce = true;
    int year = 0;
    int duration;
    bool finished = false;
    
};
