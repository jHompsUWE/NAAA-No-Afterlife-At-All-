#include "pch.h"
#include "ReincarnationManager.h"

#include "GameManager.h"

void ReincarnationManager::update(GameData& _game_data)
{
    if (!GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.empty())
    {
        for (auto & soul : GameManager::get()->getSoulManager()->m_Hell_wanderingSouls)
        {
            SoulToEMBO(*soul);
        }
    }
    if (!GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.empty())
    {
        for (auto & soul : GameManager::get()->getSoulManager()->m_Heven_wanderingSouls)
        {
            SoulToEMBO(*soul);
        }
    }
    // Check if there are any EMBO and convert it to Soul if it is time
    if (!GameManager::get()->getSoulManager()->m_Earth_Souls.empty())
    {
        for (auto & soul : GameManager::get()->getSoulManager()->m_Earth_Souls)
        {
            EMBOToSoul(*soul);
        } 
    }    
}

void ReincarnationManager::awake(GameData& _game_data)
{
    allContainers.push_back(hellZonedSouls_);
    allContainers.push_back(hellWanderingSouls_);
    allContainers.push_back(heavenWanderingSouls_);
    allContainers.push_back(heavenZonedSouls_);
}


EMBO ReincarnationManager::SoulToEMBO(Soul& _soul)
{
     if(_soul.m_reincarnate && !_soul.m_both
         && _soul.m_currentcycle == _soul.m_total_cycles
         && _soul.m_yearsleft == 0)
    //if(_soul.m_reincarnate && !_soul.m_both)
    {
        // Casting to a EMBO        
        auto convertedSoul = static_cast<EMBO&>(_soul);
        convertedSoul.earth_belief = std::rand()% 15 + 0;
        convertedSoul.m_totalyears = rand()%120 + 1;

        // Define if the soul can reincarnate
        if (convertedSoul.earth_belief <= 4 or (convertedSoul.earth_belief >= 9 and convertedSoul.earth_belief <= 12))
            convertedSoul.m_reincarnate = false;

        convertedSoul.m_fate = convertedSoul.earth_belief;
        // Add EMBO to the list
        // Here we should move the EMBO to the EMBOs list
        // and remove it from the souls list
        // Temporary one below...
        GameManager::get()->getSoulManager()->m_Earth_Souls.push_back(&convertedSoul);
        CONSOLE(Serverity::DEBUG, "one soul was converted to EMBO");
        //RemoveFromList(&_soul);
        RemoveEntity(_soul);
        return convertedSoul;
    }
}

bool ReincarnationManager::EMBOToSoul(EMBO& _embo)
{
    // The converted SOUL should be removed from the souls list
    // then add to the EMBO to the list on earth
    if (_embo.m_yearsleft == 0 && _embo.m_reincarnate)
    {
        CONSOLE(Serverity::DEBUG,  "one EMBO became a SOUL");
        Soul* convertedEmbo = new Soul; // Allocate memory for Soul object
        //auto convertedEmbo = (Soul*)_embo;
        convertedEmbo->m_totalyears = rand()%900 + 100;
        
        if (convertedEmbo->earth_belief >= 8)
        {
            convertedEmbo->m_total_cycles = std::rand() % 15 + 10;
        }
        
        if ((convertedEmbo->earth_belief + 3) % 4 == 0)
        {
            convertedEmbo->m_both = true;
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            RemoveEntity(_embo);
            return true;
        }
        if ((convertedEmbo->earth_belief + 1) % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            RemoveEntity(_embo);
            return true;
        }
        if (convertedEmbo->earth_belief % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.emplace_back(convertedEmbo);
            RemoveEntity(_embo);
            return true;
        }      
        int random = std::rand() % RAND_MAX;
        (random % 2 == 0 ? GameManager::get()->getSoulManager()->m_Hell_wanderingSouls : GameManager::get()->getSoulManager()->m_Heven_wanderingSouls).emplace_back(convertedEmbo);
        RemoveEntity(_embo);
        return false;
    }
    return false;
}

bool ReincarnationManager::compareEMBOs(const EMBO* a, const EMBO* b)
{
    if (a == b)
    {
        return true;
    }
    return false;
}

bool compareSOULs(const Soul* a, const Soul* b) {
    if (a == b)
    {
        return true;
    }
    return false;
}   

void ReincarnationManager::removeMatchingEMBOs(std::vector<EMBO*>& earthEMBOs, const EMBO& target)
{
    earthEMBOs.erase(std::remove_if(earthEMBOs.begin(), earthEMBOs.end(),
                                    [&target, this](const EMBO* emboPtr) {
                                        return compareEMBOs(emboPtr, &target);
                                    }),
                     earthEMBOs.end());
}

void ReincarnationManager::removeMatchingSOULs(const Soul& target)
{
    auto & hellZoned = GameManager::get()->getSoulManager()->m_Hell_ZonedSouls;
    
    hellZoned.erase(std::remove_if(hellZoned.begin(), hellZoned.end(),
                                    [&target, this](const Soul* emboPtr) {
                                        return compareEMBOs(emboPtr, &target);
                                    }),
                     hellZoned.end());

    auto & hellWandering = GameManager::get()->getSoulManager()->m_Hell_wanderingSouls;

    hellWandering.erase(std::remove_if(hellWandering.begin(), hellWandering.end(),
                                [&target, this](const Soul* emboPtr) {
                                    return compareEMBOs(emboPtr, &target);
                                }),
                 hellWandering.end());

    auto & heavenZoned = GameManager::get()->getSoulManager()->m_Heven_ZonedSouls;

    heavenZoned.erase(std::remove_if(heavenZoned.begin(), heavenZoned.end(),
                            [&target, this](const Soul* emboPtr) {
                                return compareEMBOs(emboPtr, &target);
                            }),
             heavenZoned.end());

    auto & heavenWandering = GameManager::get()->getSoulManager()->m_Heven_wanderingSouls;

    heavenWandering.erase(std::remove_if(heavenWandering.begin(), heavenWandering.end(),
                            [&target, this](const Soul* emboPtr) {
                                return compareEMBOs(emboPtr, &target);
                            }),
             heavenWandering.end());
    
}

void ReincarnationManager::RemoveEntity(EMBO& _embo)
{
    removeMatchingEMBOs(GameManager::get()->getSoulManager()->m_Earth_Souls, _embo);
}

void ReincarnationManager::RemoveEntity(Soul& _soul)
{
    removeMatchingSOULs(_soul);
}


void ReincarnationManager::RemoveFromList(Soul* _soul)
{
        // std::shared_ptr<Soul> soulToRemove = make_unique<Soul>(*_soul);
        // // Get references to the containers
        // auto& hellZonedSouls = GameManager::get()->getSoulManager()->m_Hell_ZonedSouls;
        // auto& hellWanderingSouls = GameManager::get()->getSoulManager()->m_Hell_wanderingSouls;
        // auto& hevenZonedSouls = GameManager::get()->getSoulManager()->m_Heven_ZonedSouls;
        // auto& hevenWanderingSouls = GameManager::get()->getSoulManager()->m_Heven_wanderingSouls;
}
