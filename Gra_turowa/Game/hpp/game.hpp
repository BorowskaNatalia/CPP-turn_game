
#pragma once

#include <string>
#include <vector>
#include <set>
#include "../../Monster/hpp/monster.hpp"
#include "../../sills/hpp/boost_skill.hpp"
#include "../../sills/hpp/special_power.hpp"
#include "player.hpp"

struct game {
    std::string name;
    player player;
    int difficulty_level;
    int round;
    int enemyAlive;

    std::vector<std::vector<monster>> enemy_team;


    game();

};



