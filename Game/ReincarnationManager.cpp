#include "pch.h"
#include "ReincarnationManager.h"

#include "GameManager.h"

void ReincarnationManager::update(GameData& _game_data)
{
    if (_game_data.m_KBS_tracker.pressed.T)
    {
        EMBO* test = GameManager::get()->getSoulManager()->m_Earth_Souls.begin()->get();
        TurnIntoSoul(test);
    }
    if (_game_data.m_KBS_tracker.pressed.U)
    {
        Soul* test = GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.begin()->get();
        TurnIntoEMBO(test);
    }
    if (_game_data.m_KBS_tracker.pressed.Y)
    {
        std::cout << "soul = " << GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.size() << endl;
        std::cout << "EMbo = " << GameManager::get()->getSoulManager()->m_Earth_Souls.size() << endl;
    }
}

void ReincarnationManager::awake()
{
    for (int i = 0; i < 10; ++i)
    {
        shared_ptr<EMBO> testEMBO = make_shared<EMBO>();
        shared_ptr<Soul> testSoul = make_shared<Soul>();
        test_Earth_Souls.push_back(testEMBO);
        test_Heven_wanderingSouls.push_back(testSoul);
    }
    Manager::awake();
}

EMBO ReincarnationManager::TurnIntoEMBO(Soul* _soul)
{
    //if(_soul->m_reincarnate
    //&& !_soul->m_both
    //&& _soul->m_currentcycle == _soul->m_total_cycles
    //&& _soul->m_yearsleft == 0)
    
    if(_soul->m_reincarnate
        && !_soul->m_both)
    {
        // Casting to a EMBO
        
        auto convertedSoul = (EMBO*)_soul;
        convertedSoul->earth_belief = std::rand()% 15 + 0;
        convertedSoul->m_totalyears = rand()%120 + 1;
        
        // Define if the soul can reincarnate
        if (convertedSoul->earth_belief <= 4 or (convertedSoul->earth_belief >= 9 and convertedSoul->earth_belief <= 12))
            convertedSoul->m_reincarnate = false;

        convertedSoul->m_fate = convertedSoul->earth_belief;
        // Add EMBO to the list
        GameManager::get()->getSoulManager()->m_Earth_Souls.push_back(shared_ptr<EMBO>(convertedSoul));
        return *convertedSoul;
    }
}

Soul ReincarnationManager::TurnIntoSoul(EMBO* _embo)
{
    // if (_embo->m_yearsleft == 0 && _embo->m_reincarnate)
    // {
        auto convertedEmbo = (Soul*)_embo;
        convertedEmbo->m_totalyears = rand()%900 + 100;

        if (convertedEmbo->earth_belief >= 8)
        {
            convertedEmbo->m_total_cycles = std::rand() % 15 + 10;
        }

        if ((convertedEmbo->earth_belief + 3) % 4 == 0)
        {
            convertedEmbo->m_both = true;
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            return *convertedEmbo;
        }

        if ((convertedEmbo->earth_belief + 1) % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            return *convertedEmbo;
        }
        if (convertedEmbo->earth_belief % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.emplace_back(convertedEmbo);
            return *convertedEmbo;
        }      
        int random = std::rand() % RAND_MAX;
        (random % 2 == 0 ? GameManager::get()->getSoulManager()->m_Hell_wanderingSouls : GameManager::get()->getSoulManager()->m_Heven_wanderingSouls).emplace_back(convertedEmbo);
        return *convertedEmbo;
//    }
}
