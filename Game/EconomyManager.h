#pragma once
#include "Manager.h"

class EconomyManager : public Manager
{
public:
    void update(GameData& _game_data) override;

    ////////////////////////////////////////////////////////////
    /// \brief Calculates the amount of gold each soul gives to the player.
    ///
    /// \param population Current population in the game world.
    ///	\param amount_of_tiles Amount of tiles that have been populated. 
    ///	\param year Current year in the game. 
    ///	\param rate_multiplier Float multiplier to transform year into a small value eg. 0.02023. 
    ///
    ////////////////////////////////////////////////////////////
    static float CalculateSoulRate(float population, float amount_of_tiles, int year, float rate_multiplier);

    ////////////////////////////////////////////////////////////
    /// \brief Adds gold to the player.
    ///
    /// \param amount The amount that will be given to the player.
    ////////////////////////////////////////////////////////////
    void AddGold(float amount){total_gold_ += amount;}

    ////////////////////////////////////////////////////////////
    /// \brief Remove gold from the player.
    ///
    /// \param amount The amount that will be removed from the player.
    ////////////////////////////////////////////////////////////
    void RemoveGold(float amount){total_gold_ -= amount;}

    ////////////////////////////////////////////////////////////
    /// \brief Round the float to decimal digits.
    ///
    /// \param value The value that will be converted.
    /// \param digits Number of digits the value should be rounded.
    ////////////////////////////////////////////////////////////
    static float Round(float value, int digits);


    // Variables
    ////////////////////////////////////////////////////////////
    /// \brief Get the value of cost.
    ////////////////////////////////////////////////////////////
    uint8_t cost() const { return cost_; }

    ////////////////////////////////////////////////////////////
    /// \brief Set the value of cost.
    ////////////////////////////////////////////////////////////
    void set_cost(const uint8_t cost) { cost_ = cost; }

    ////////////////////////////////////////////////////////////
    /// \brief Get player's total gold.
    ////////////////////////////////////////////////////////////
    float total_gold() const { return total_gold_; }

    ////////////////////////////////////////////////////////////
    /// \brief Set player's total gold.
    ////////////////////////////////////////////////////////////
    void set_total_gold(const float total_gold) { total_gold_ = total_gold; }
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the yearly paycheck value.
    ////////////////////////////////////////////////////////////
    float yearly_paycheck() const { return yearly_paycheck_; }

    ////////////////////////////////////////////////////////////
    /// \brief Set the yearly paycheck amount.
    ////////////////////////////////////////////////////////////
    void set_yearly_paycheck(const float yearly_paycheck) { yearly_paycheck_ = yearly_paycheck; }
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the gold per soul.
    ////////////////////////////////////////////////////////////
    float gold_per_soul() const { return gold_per_soul_; }

    ////////////////////////////////////////////////////////////
    /// \brief Set the amount of gold per soul the player gets.
    ////////////////////////////////////////////////////////////
    void set_gold_per_soul(const float gold_per_soul) { gold_per_soul_ = gold_per_soul; }
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the year rate multiplier.
    ////////////////////////////////////////////////////////////
    float rate_multiplier() const { return rate_multiplier_; }

    ////////////////////////////////////////////////////////////
    /// \brief Set the rate multiplier value
    ////////////////////////////////////////////////////////////
    void set_rate_multiplier(const float rate_multiplier) { rate_multiplier_ = rate_multiplier; }

private:
    uint8_t cost_ = 0;    float total_gold_ = 0;
    float yearly_paycheck_ = 0;
    float gold_per_soul_ = 0;
    float rate_multiplier_ = 0.01f;  
    
};
