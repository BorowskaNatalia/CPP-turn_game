
#include "hpp/debuff_skill.hpp"

debuff_skill::debuff_skill(const std::string &name, int duration, int amountToUse, std::vector<monster::monster_type> possibleType, special_power::stats whatBoost,
                         int strength) : special_power(name, duration, amountToUse, possibleType), whatDebuff(whatBoost),
                                         strength(strength) {}

debuff_skill::debuff_skill() {}

debuff_skill::debuff_skill(debuff_skill const& other)
        : special_power(other.name, other.duration, other.amountToUse, other.possibleType), whatDebuff(other.whatDebuff), strength(other.strength){}

bool debuff_skill::use(monster& player, monster& enemy) {
    if (!enemy.underInfluenceDebuff) {
        if ( player.amountToUsePok != 0) {
            player.amountToUsePok--;
            enemy.influenceCounterDebuff = duration;
            std::string description;
            switch (whatDebuff) {
                case special_power::stats::agility : {
                    enemy.agility -= strength;
                    description = "agility";
                }
                    break;
                case special_power::stats::health : {
                    enemy.health -= strength;
                    description = "health";
                }
                    break;
                case special_power::stats::power : {
                    enemy.power -= strength;
                    description = "power";
                }
            }
            enemy.underInfluenceDebuff = true;
            std::cout << "Uzyto: " << name << "!\t"<< description << " przeciwnika -"<<strength << "\n";
            return true;
        } else {
            std::cout << "Nie mozesz juz uzyc tej umiejetnosci!\n";
            return false;
        }
    } else{
        std::cout << "Przeciwnik jest juz pod wplywem twojej umiejetnosci\n";
        return false;
    }
};

