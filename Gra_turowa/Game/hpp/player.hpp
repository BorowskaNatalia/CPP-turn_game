
#include <string>
#include "../../Monster/hpp/monster.hpp"

struct player{
    std::string name;
    int wins;
    int loses;
    monster hand;
    std::vector<monster> team;
};