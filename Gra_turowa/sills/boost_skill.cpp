
#include <iostream>
#include "hpp/boost_skill.hpp"

boost_skill::boost_skill(const std::string &name, int duration, int amountToUse,
                         std::vector<monster::monster_type> possibleType, special_power::stats whatBoost,
                         int strength) : special_power(name, duration, amountToUse, possibleType), whatBoost(whatBoost),
                                         strength(strength) {}

boost_skill::boost_skill() {}

boost_skill::boost_skill(boost_skill const &other)
        : special_power(other.name, other.duration, other.amountToUse, other.possibleType), whatBoost(other.whatBoost),
          strength(other.strength) {}

bool boost_skill::use(monster &player, monster &enemy) {
    if (!player.underInfluenceBoost) {
        if (!(player.amountToUsePok == 0)) {
            player.amountToUsePok--;
            player.influenceCounterBoost = duration;
            std::string description;
            switch (whatBoost) {
                case special_power::stats::agility : {
                    player.agility += strength;
                    description = "agility";
                }
                    break;
                case special_power::stats::health : {
                    player.health += strength;
                    description = "health";
                }
                    break;
                case special_power::stats::power : {
                    player.power += strength;
                    description = "power";
                }
            }
            player.underInfluenceBoost = true;
            std::cout << "Uzyto: " << name << "!\t"<< description << " +" << strength << "\n";
            return true;
        } else{
            std::cout << "Nie mozesz juz uzyc tej umiejetnosci\n";
            return false;
        }
    } else{
        std::cout << "Jestes juz pod wplywem jeszcze przez: " << player.influenceCounterBoost << "\n";
        return false;
    }
};


