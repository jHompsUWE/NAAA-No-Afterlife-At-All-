#include "pch.h"
#include "EconomyManager.h"
#include <ostream>

void EconomyManager::update(GameData& _game_data)
{
}

float EconomyManager::CalculateSoulRate(float population, float amount_of_tiles, int year, float rate_multiplier)
{
    return Round(population / amount_of_tiles * (static_cast<float>(year) * rate_multiplier), 2);
}

float EconomyManager::Round(float value, int digits)
{
    auto mult = pow(10.0f, digits);
    return roundf(value*mult) / mult;
}

