#include "pch.h"
#include "ReincarnationManager.h"

#include "GameManager.h"

void ReincarnationManager::update(GameData& _game_data)
{
    if (doOnce)
    {
        if (!GameManager::get()->getSoulManager()->m_Earth_Souls.empty())
        {
            EMBOToSoul(*GameManager::get()->getSoulManager()->m_Earth_Souls.at(0));
            doOnce = false;
        }
    }
    // auto soulManager = GameManager::get()->getSoulManager();
    //
    // // for (auto& embo : soulManager->m_Earth_Souls)
    // // {
    // //     if (embo != nullptr)
    // //     {
    // //         if (embo->m_yearsleft == 0 && embo->m_reincarnate)
    // //         {
    // //             TurnIntoSoul(embo.get());
    // //         }
    // //     }
    // // }
    // if (!soulManager->m_Earth_Souls.empty())
    // {
    //     for (auto soulIter = soulManager->m_Earth_Souls.begin(); soulIter != soulManager->m_Earth_Souls.end();)
    //     {
    //         if (*soulIter != nullptr)
    //         {
    //             TurnIntoSoul((*soulIter).get());
    //             //soulIter = soulManager->m_Earth_Souls.erase(soulIter);
    //         }
    //     }
    // }
    // // hellZonedSouls_ = soulManager->m_Hell_ZonedSouls;
    // // hellWanderingSouls_ = soulManager->m_Hell_wanderingSouls;
    // // for (auto soul :  soulManager->m_Hell_wanderingSouls)
    // // {
    // //     if (soul != nullptr)
    // //     {
    // //         TurnIntoEMBO(soul.get());
    // //     }
    // // }
    // if (!soulManager->m_Hell_wanderingSouls.empty())
    // {
    //     for (auto soulIter = soulManager->m_Hell_wanderingSouls.begin(); soulIter != soulManager->m_Hell_wanderingSouls.end();)
    //     {
    //         if (*soulIter != nullptr)
    //         {
    //             TurnIntoEMBO((*soulIter).get());              
    //             //soulIter = soulManager->m_Hell_wanderingSouls.erase(soulIter);
    //         }
    //     }
    // }
    //
    // if (!soulManager->m_Heven_wanderingSouls.empty())
    // {
    //     for (auto soulIter = soulManager->m_Heven_wanderingSouls.begin(); soulIter != soulManager->m_Heven_wanderingSouls.end();)
    //     {
    //         if (*soulIter != nullptr)
    //         {
    //             TurnIntoEMBO((*soulIter).get());               
    //             //soulIter = soulManager->m_Heven_wanderingSouls.erase(soulIter);
    //         }
    //     }
    // }
    
    if (_game_data.m_KBS_tracker.pressed.Y)
    {
        std::cout << "soul = " << GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.size() << endl;
        std::cout << "EMbo = " << earthEMBOs.size() << endl;
    }
}

void ReincarnationManager::awake()
{
    allContainers.push_back(hellZonedSouls_);
    allContainers.push_back(hellWanderingSouls_);
    allContainers.push_back(heavenWanderingSouls_);
    allContainers.push_back(heavenZonedSouls_);
    Manager::awake();
}


EMBO ReincarnationManager::TurnIntoEMBO(Soul* _soul)
{
    if(_soul->m_reincarnate
    && !_soul->m_both
    && _soul->m_currentcycle == _soul->m_total_cycles
    && _soul->m_yearsleft == 0)    
    // if(_soul->m_reincarnate
    //     && !_soul->m_both)
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
        // Here we should move the EMBO to the EMBOs list
        // and remove it from the souls list
        // Temporary one below...
        GameManager::get()->getSoulManager()->m_Earth_Souls.push_back(shared_ptr<EMBO>(convertedSoul));
        std::cout << "one soul was converted to EMBO" << endl;
        //RemoveFromList(_soul);
        return *convertedSoul;
   }
}

Soul ReincarnationManager::TurnIntoSoul(EMBO* _embo)
{
    // The converted SOUL should be removed from the souls list
    // then add to the EMBO to the list on earth
    if (_embo->m_yearsleft == 0 && _embo->m_reincarnate)
    {
        std::cout << "one EMBO became a SOUL" << endl;
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
            //RemoveFromList(_embo);
            return *convertedEmbo;
        }

        if ((convertedEmbo->earth_belief + 1) % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            //RemoveFromList(_embo);
            return *convertedEmbo;
        }
        if (convertedEmbo->earth_belief % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.emplace_back(convertedEmbo);
            //RemoveFromList(_embo);
            return *convertedEmbo;
        }      
        int random = std::rand() % RAND_MAX;
        (random % 2 == 0 ? GameManager::get()->getSoulManager()->m_Hell_wanderingSouls : GameManager::get()->getSoulManager()->m_Heven_wanderingSouls).emplace_back(convertedEmbo);
        //RemoveFromList(_embo);
        return *convertedEmbo;
   }
}

EMBO ReincarnationManager::SoulToEMBO(Soul& _soul)
{
    if(_soul.m_reincarnate && !_soul.m_both
        && _soul.m_currentcycle == _soul.m_total_cycles
        && _soul.m_yearsleft == 0)
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
        GameManager::get()->getSoulManager()->m_Earth_Souls.push_back(shared_ptr<EMBO>(&convertedSoul));
        std::cout << "one soul was converted to EMBO" << endl;
        //RemoveFromList(&_soul);
        RemoveEntity(_soul);
        return convertedSoul;
    }
}

Soul ReincarnationManager::EMBOToSoul(EMBO& _embo)
{
    // The converted SOUL should be removed from the souls list
    // then add to the EMBO to the list on earth
    if (_embo.m_yearsleft == 0 && _embo.m_reincarnate)
    {
        std::cout << "one EMBO became a SOUL" << endl;
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
            return *convertedEmbo;
        }
        if ((convertedEmbo->earth_belief + 1) % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.emplace_back(convertedEmbo);
            RemoveEntity(_embo);
            return *convertedEmbo;
        }
        if (convertedEmbo->earth_belief % 4 == 0)
        {
            GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.emplace_back(convertedEmbo);
            RemoveEntity(_embo);
            return *convertedEmbo;
        }      
        int random = std::rand() % RAND_MAX;
        (random % 2 == 0 ? GameManager::get()->getSoulManager()->m_Hell_wanderingSouls : GameManager::get()->getSoulManager()->m_Heven_wanderingSouls).emplace_back(convertedEmbo);
        RemoveEntity(_embo);
        return *convertedEmbo;
    }
}

void ReincarnationManager::RemoveEntity(EMBO& _embo)
{
    auto& earthEMBO = GameManager::get()->getSoulManager()->m_Earth_Souls;
    
    auto it = std::find_if(earthEMBO.begin(), earthEMBO.end(),
        [_embo](const std::shared_ptr<EMBO>& element) {
                  return element.get() == &_embo;
              });
    // Erase the element from the vector if found
    if (it != GameManager::get()->getSoulManager()->m_Earth_Souls.end())
    {
        GameManager::get()->getSoulManager()->m_Earth_Souls.erase(it);
    }
}

void ReincarnationManager::RemoveEntity(Soul& _soul)
{
    auto& hellZonedSouls = GameManager::get()->getSoulManager()->m_Hell_ZonedSouls;
    auto& hellWanderingSouls = GameManager::get()->getSoulManager()->m_Hell_wanderingSouls;
    auto& hevenZonedSouls = GameManager::get()->getSoulManager()->m_Heven_ZonedSouls;
    auto& hevenWanderingSouls = GameManager::get()->getSoulManager()->m_Heven_wanderingSouls;

    // if (!hellZonedSouls.empty())
    // {
    //     hellZonedSouls.erase(std::find(hellZonedSouls.begin(), hellZonedSouls.end(), _soul));
    // }

    // for (auto element : hellZonedSouls)
    // {
    //     if (element.get() == &_soul)
    //     {
    //         hellZonedSouls.erase(std::find(hellZonedSouls.begin(), 
    //                   hellZonedSouls.end(), _soul));
    //         break;
    //     }
    // }
    // for (auto element : hellWanderingSouls)
    // {
    //     if (element.get() == &_soul)
    //     {
    //         hellWanderingSouls.erase(std::find(hellWanderingSouls.begin(), 
    //                   hellWanderingSouls.end(), _soul));
    //         break;
    //     }
    // }
    //
    // // Heaven
    //
    // for (auto element : hevenZonedSouls)
    // {
    //     if (element.get() == &_soul)
    //     {
    //         hevenZonedSouls.erase(std::find(hevenZonedSouls.begin(), 
    //                   hevenZonedSouls.end(), _soul));
    //         break;
    //     }
    // }
    //
    // for (auto element : hevenWanderingSouls)
    // {
    //     if (element.get() == &_soul)
    //     {
    //         hevenWanderingSouls.erase(std::find(hevenWanderingSouls.begin(), 
    //                   hevenWanderingSouls.end(), _soul));
    //         break;
    //     }
    // }
}



void ReincarnationManager::RemoveFromList(EMBO* _embo)
{
    if (_embo != nullptr && GameManager::get()->getSoulManager()->m_Earth_Souls.size() != 0)
    {
        // auto it = find(earthEMBOs.begin(), earthEMBOs.end(), _embo);
        // if (it != earthEMBOs.end())
        // {
        //     std::cout << "Found in earthEMBOS" << std::endl;
        //     earthEMBOs.erase(it);
        // }
        auto it = std::find_if(GameManager::get()->getSoulManager()->m_Earth_Souls.begin(), 
                      GameManager::get()->getSoulManager()->m_Earth_Souls.end(),
                      [_embo](const std::shared_ptr<EMBO>& element) {
                          return element.get() == _embo;
                      });
        // Erase the element from the vector if found
        if (it != GameManager::get()->getSoulManager()->m_Earth_Souls.end())
        {
            GameManager::get()->getSoulManager()->m_Earth_Souls.erase(it);
            earthEMBOs = GameManager::get()->getSoulManager()->m_Earth_Souls;
        }
    }
}

void ReincarnationManager::RemoveFromList(Soul* _soul)
{
    if (_soul != nullptr)
    {
        std::shared_ptr<Soul> soulToRemove = make_unique<Soul>(*_soul);
        // Get references to the containers
        auto& hellZonedSouls = GameManager::get()->getSoulManager()->m_Hell_ZonedSouls;
        auto& hellWanderingSouls = GameManager::get()->getSoulManager()->m_Hell_wanderingSouls;
        auto& hevenZonedSouls = GameManager::get()->getSoulManager()->m_Heven_ZonedSouls;
        auto& hevenWanderingSouls = GameManager::get()->getSoulManager()->m_Heven_wanderingSouls;

        // Search and remove the item from the Hell Zoned Souls container
        auto hellZonedIter = std::find_if(hellZonedSouls.begin(), hellZonedSouls.end(),
            [&](const std::shared_ptr<Soul>& soul) {
                return soul.get() == soulToRemove.get();
            });
        if (hellZonedIter != hellZonedSouls.end()) {
            hellZonedSouls.erase(hellZonedIter);
        }

        // Search and remove the item from the Hell Wandering Souls container
        auto hellWanderingIter = std::find_if(hellWanderingSouls.begin(), hellWanderingSouls.end(),
            [&](const std::shared_ptr<Soul>& soul) {
                return soul.get() == soulToRemove.get();
            });
        if (hellWanderingIter != hellWanderingSouls.end()) {
            hellWanderingSouls.erase(hellWanderingIter);
        }

        // Search and remove the item from the Heven Zoned Souls container
        auto hevenZonedIter = std::find_if(hevenZonedSouls.begin(), hevenZonedSouls.end(),
            [&](const std::shared_ptr<Soul>& soul) {
                return soul.get() == soulToRemove.get();
            });
        if (hevenZonedIter != hevenZonedSouls.end()) {
            hevenZonedSouls.erase(hevenZonedIter);
        }

        // Search and remove the item from the Heven Wandering Souls container
        auto hevenWanderingIter = std::find_if(hevenWanderingSouls.begin(), hevenWanderingSouls.end(),
            [&](const std::shared_ptr<Soul>& soul) {
                return soul.get() == soulToRemove.get();
            });
        if (hevenWanderingIter != hevenWanderingSouls.end()) {
            hevenWanderingSouls.erase(hevenWanderingIter);
        }
    }







        
    // {
    //     // for (auto & container : allContainers)
    //     // {
    //     //     auto sharedSoulToFind = std::make_shared<Soul>(*_soul);
    //     //     auto it = std::find_if(container.begin(), container.end(), SoulComparator(sharedSoulToFind));
    //     //     if (it != container.end()) {
    //     //         // The object was found in the vector, erase it
    //     //         container.erase(it);
    //     //     }
    //     //     else
    //     //     {
    //     //         cout << "Moving to next container" << endl;
    //     //     }
    //     // }
    //     auto sharedSoulToFind = std::make_shared<Soul>(*_soul);
    //     //auto it2 = find(hellZonedSouls_.begin(), hellZonedSouls_.end(), _soul);
    //     auto it2 = std::find_if(hellZonedSouls_.begin(), hellZonedSouls_.end(), SoulComparator(sharedSoulToFind));
    //     if (it2 != hellZonedSouls_.end())
    //     {
    //         std::cout << "Found in hellZonedSouls_" << std::endl;
    //         GameManager::get()->getSoulManager()->m_Hell_ZonedSouls.erase(it2);
    //     }
    //     auto it3 = std::find_if(hellWanderingSouls_.begin(), hellWanderingSouls_.end(), SoulComparator(sharedSoulToFind));
    //     if (it3 != hellWanderingSouls_.end())
    //     {
    //         std::cout << "Found in hellZonedSouls_" << std::endl;
    //         GameManager::get()->getSoulManager()->m_Hell_wanderingSouls.erase(it3);
    //     }
    //     // auto it3 = find(hellWanderingSouls_.begin(), hellWanderingSouls_.end(), _soul);
    //     // if (it3 != hellWanderingSouls_.end())
    //     // {
    //     //     std::cout << "Found in hellZonedSouls_" << std::endl;
    //     //     hellWanderingSouls_.erase(it3);
    //     // }
    //     auto it4 = std::find_if(heavenZonedSouls_.begin(), heavenZonedSouls_.end(), SoulComparator(sharedSoulToFind));
    //     if (it3 != heavenZonedSouls_.end())
    //     {
    //         std::cout << "Found in hellZonedSouls_" << std::endl;
    //         GameManager::get()->getSoulManager()->m_Heven_ZonedSouls.erase(it4);
    //     }
    //     // auto it4 = find(heavenZonedSouls_.begin(), heavenZonedSouls_.end(), _soul);
    //     // if (it4 != heavenZonedSouls_.end())
    //     // {
    //     //     std::cout << "Found in hellZonedSouls_" << std::endl;
    //     //     heavenZonedSouls_.erase(it4);
    //     // }
    //     auto it5 = std::find_if(heavenWanderingSouls_.begin(), heavenWanderingSouls_.end(), SoulComparator(sharedSoulToFind));
    //     if (it3 != heavenWanderingSouls_.end())
    //     {
    //         std::cout << "Found in hellZonedSouls_" << std::endl;
    //         GameManager::get()->getSoulManager()->m_Heven_wanderingSouls.erase(it5);
    //     }
    //     // auto it5 = find(heavenWanderingSouls_.begin(), heavenWanderingSouls_.end(), _soul);
    //     // if (it5 != heavenWanderingSouls_.end())
    //     // {
    //     //     std::cout << "Found in hellZonedSouls_" << std::endl;
    //     //     heavenWanderingSouls_.erase(it5);
    //     // }   
    
}
