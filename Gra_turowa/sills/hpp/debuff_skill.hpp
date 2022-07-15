#pragma once
#include "special_power.hpp"
struct debuff_skill : special_power{

    stats whatDebuff;
    int strength;

    debuff_skill();
    debuff_skill(const std::string &name, int duration, int amountToUse, std::vector<monster::monster_type> possibleType,
                stats whatDebuff, int strength);

    /**konstruktor kopiujący
     *
     *
     */
    debuff_skill(debuff_skill const& other);

    bool use(monster& player, monster& enemy) override;
};