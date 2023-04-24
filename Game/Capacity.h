#pragma once
#include "soulmanager.h"

struct Capacity
{
    int MaximumCapacity; //UNCHANGEABLE
    int CurrentCapacity;
    std::vector<std::shared_ptr<Soul>> TemporaryCapacity;
    std::vector<std::shared_ptr<Soul>> PermanentCapacity;
};