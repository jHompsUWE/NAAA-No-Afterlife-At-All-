#pragma once
#include "GameManager.h"

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

class BadThing
{
public:
    virtual ~BadThing() = default;
    virtual void update();    
};

class BadThings : public Manager
{    
public:
    void triggerBadThing(BadThingsTypes _badThingType);
    void removeBadThing(BadThingsTypes _badThingType);
    void update(GameData& _game_data) override;

private:
    typedef std::vector<BadThing*> BadThingVector;
    BadThingVector BadThingsVector_;
    
    BadThingsTypes current_type_ = NONE;
    
};
