#include "pch.h"
#include "BadThingsBOP.h"


BadThingsBOP::BadThingsBOP(): BadThingsParent()
{
    srand(time(NULL));
    badThingType = BIRDS_OF_PARADISE;
    duration = 75;
    randomPosition = rand() % GameManager::get()->getWorldManager()->getWorld()[PlaneType::Heaven].size() - 1;
}

void BadThingsBOP::TriggerBadThing(GameData& game_data)
{
    if (!finished)
    {
        auto& plane = GameManager::get()->getWorldManager()->getWorld()[PlaneType::Heaven];
        if (randomPosition < 0) {randomPosition = 0;}

        /// This will look for a random building, if it doesn't find then it will keep looking until find one
        if(plane.at(randomPosition)->getGridData().m_tile_type != TileType::Building)
        {
            randomPosition = rand()%GameManager::get()->getWorldManager()->getWorld()[PlaneType::Heaven].size()-1;
            //CONSOLE(WARNING, to_string(randomPosition));
        }
        else
        {
            /// Set the year the Bad Thing will stop.
            if (doOnce)
            {
                year = game_data.Year + duration;
                doOnce = false;
                CONSOLE(INFO, "Bad Thing happening!! Type: Birds of Paradise");
            }
            /// While the current year is not the final year it changes the efficiency of the building
            if (game_data.Year < year)
            {
                plane.at(randomPosition)->getGridData().m_efficiency = plane.at(randomPosition)->getGridData().m_efficiency * 0.5f;             
            }
            else
            {
                plane.at(randomPosition)->getGridData().m_efficiency = plane.at(randomPosition)->getGridData().m_efficiency * 2.0f;
                CONSOLE(INFO, "Bad Thing happening ended");
                finished = true;
            }
        }
    }   
}

void BadThingsBOP::ResetBadThing()
{
    randomPosition = rand() % GameManager::get()->getWorldManager()->getWorld()[PlaneType::Heaven].size() - 1;
    BadThingsParent::ResetBadThing();
}
