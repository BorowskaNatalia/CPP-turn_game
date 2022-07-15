#pragma once
#include "special_power.hpp"


struct boost_skill : special_power{

    stats whatBoost;
    int strength;

    boost_skill();
    boost_skill(const std::string &name, int duration, int amountToUse, std::vector<monster::monster_type> possibleType,
                stats whatBoost, int strength);

    /**konstruktor kopiujący
     *
     *
     */
    boost_skill(boost_skill const& other);

    bool use(monster& player, monster& enemy) override;
};