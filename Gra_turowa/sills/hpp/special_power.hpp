#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../../Monster/hpp/monster.hpp"

struct special_power {
    enum class stats{
        agility, health, power
    };

    std::string name;
    int duration;
    int amountToUse;
    std::vector<monster::monster_type> possibleType;
    special_power(const std::string &name, int duration, int amountToUse, std::vector<monster::monster_type> possibleType);
    special_power(special_power const& other);
    special_power();

    virtual bool use(monster& player, monster& enemy);

};




