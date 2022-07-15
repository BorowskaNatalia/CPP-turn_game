
#include <string>
#include "hpp/special_power.hpp"
special_power::special_power(const std::string &name,
                             int duration, int amountToUse, std::vector<monster::monster_type> possibleType) : name(name), duration(duration), amountToUse(amountToUse), possibleType(possibleType) {}

special_power::special_power() {
}

special_power::special_power(special_power const& other)
: name(other.name), duration(other.duration), amountToUse(other.amountToUse)
{}

bool special_power::use(monster &player, monster &enemy)  {
    std::cout << "auuu!\n";
}
