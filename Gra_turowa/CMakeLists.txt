cmake_minimum_required(VERSION 3.21)
project(Gra_turowa)

set(CMAKE_CXX_STANDARD 20)

add_executable(Gra_turowa Game/main.cpp Monster/monster.cpp sills/special_power.cpp sills/hpp/special_power.hpp Monster/hpp/monster.hpp Game/controler.cpp Game/hpp/controler.hpp Game/game.cpp Game/hpp/game.hpp sills/boost_skill.cpp sills/hpp/boost_skill.hpp sills/debuff_skill.cpp sills/hpp/debuff_skill.hpp Game/player.cpp Game/hpp/player.hpp)
