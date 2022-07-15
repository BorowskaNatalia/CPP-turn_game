#include <vector>
#include "hpp/monster.hpp"
#include "../sills/hpp/boost_skill.hpp"
#include "../sills/hpp/debuff_skill.hpp"

/**
 * Pula skilli to wylosowania przez pokemony
 */
using mt = monster::monster_type;
using s = special_power::stats;
std::vector<special_power *> skills = std::vector<special_power *>{
        new boost_skill("Blizzard wizard", 2, 2, std::vector<mt>{mt::water, mt::air}, s::agility, 20),
        new boost_skill("Healing dealing", 3, 1,
                        std::vector<mt>{mt::air, mt::steel, mt::water, mt::fire, mt::earth, mt::ice}, s::health, 50),
        new boost_skill("Ground strengthening", 2, 2, std::vector<mt>{mt::earth}, s::power, 70),
        new boost_skill("Fire dance", 2, 2, std::vector<mt>{mt::fire}, s::agility, 50),
        new boost_skill("World enhancement", 1,3, std::vector<mt>{mt::air, mt::steel, mt::water, mt::fire, mt::earth, mt::ice}, s::power, 30),
        new boost_skill("H2O - Just add water", 2, 1, std::vector<mt> {mt::water, mt::ice}, s::power, 30),
        new debuff_skill("Freezing breezing", 2, 2, std::vector<mt>{mt::air, mt::ice, mt::water}, s::agility, 20),
        new debuff_skill("Conflagration creation", 2, 1, std::vector<mt>{mt::fire}, s::health, 50),
        new debuff_skill("Steel embrace arms race", 3, 1, std::vector<mt>{mt::steel}, s::health, 60),
        new debuff_skill("Rain pain", 3, 1, std::vector<mt>{mt::water, mt::ice}, s::health, 50),
        new debuff_skill("Fire ball", 3, 1, std::vector<mt>{mt::fire}, s::health, 50),
        new debuff_skill("Tornado obbligato", 2, 2, std::vector<mt>{mt::air}, s::agility, 20),
        new debuff_skill("Overwhelming fire", 1,3, std::vector<mt>{mt::fire}, s::power, 20),
        new debuff_skill("Crushing of steel", 2, 2, std::vector<mt>{mt::steel}, s::power, 20),
        new debuff_skill("Avalanche", 2, 3, std::vector<mt>{mt::earth, mt::ice}, s::power, 10),



};

void monster::chooseSpecialSkill() {
    bool flag = true;
    while (flag) {
        special_power *randomSkill = skills[(std::rand() % skills.size())];
        if (std::find(randomSkill->possibleType.begin(), randomSkill->possibleType.end(), type) !=
            randomSkill->possibleType.end()) {
            flag = !flag;
            specialPower = randomSkill;
        }
    }
}

monster::monster() {
    exp = 0;
    lvl = 1;
    name = "domyslne";
    alive = true;
    type = types.at((std::rand() % 6) + 1);
    set_attributes();
    chooseSpecialSkill();
    maxHealth = health;
}

monster::monster(int nameIndex) {
    exp = 0;
    lvl = 1;
    type = types.at((std::rand() % 6) + 1);
    alive = true;
    underInfluenceBoost = false;
    underInfluenceDebuff = false;
    set_attributes();
    name = monster::names[nameIndex];
    chooseSpecialSkill();
    influenceCounterBoost =  0;
    influenceCounterDebuff = 0;
    amountToUsePok = specialPower->amountToUse;

}

void monster::set_attributes() {
    switch (type) {
        case monster::monster_type::water : {
            monster::set_max_min_attributes(300, 500, 50, 75, 10, 15);
        }
            break;
        case monster::monster_type::earth : {
            monster::set_max_min_attributes(300, 500, 70, 100, 0, 10);
        }
            break;
        case monster::monster_type::fire : {
            monster::set_max_min_attributes(200, 300, 50, 75, 10, 50);
        }
            break;
        case monster::monster_type::air : {
            monster::set_max_min_attributes(75, 100, 20, 30, 50, 70);
        }
            break;
        case monster::monster_type::ice : {
            monster::set_max_min_attributes(200, 400, 70, 100, 0, 10);
        }
            break;
        case monster::monster_type::steel : {
            monster::set_max_min_attributes(100, 200, 20, 50, 30, 40);
        }
            break;
    }
    maxHealth = health;
    maxAgility = agility;
    maxPower = power;
}

void monster::set_max_min_attributes(int health_min, int health_max, int power_min, int power_max, int agility_min,
                                     int agility_max) {
    health = (rand() % (health_max - health_min) + health_min) / 10 * 10;
    power = (rand() % (power_max - power_min) + power_min) / 10 * 10;
    agility = rand() % (agility_max - agility_min) + agility_min;

}

std::string monster::show_type() const {

    switch (type) {
        case monster::monster_type::water : {
            return "water";
        }
        case monster::monster_type::earth : {
            return "earth";
        }
        case monster::monster_type::fire : {
            return "fire";
        }
        case monster::monster_type::air : {
            return "air";
        }
        case monster::monster_type::ice : {
            return "ice";
        }
        case monster::monster_type::steel : {
            return "steel";
        }
    }
    return "";
}

std::string monster::show() {
    return {name + " typ: " + show_type() + "\n\thealth: " + std::to_string(health) + "\n\tpower: " +
            std::to_string(power) + "\n\tagility: " + std::to_string(agility) + "\n\tspecial power: " +
            specialPower->name + " liczba uzyc: " + std::to_string(amountToUsePok) + "\n"};

}

void monster::attack(monster &m1) {
    double factor;
    factor = this->comparatorPokemon(this, m1);
    int los = (std::rand() % 100);
    bool dodge = (los <= m1.agility);
    if (dodge) {
        std::cout << m1.name << " wykonal unik!\n";
        return;
    }
    double dmg = factor * power;
    m1.health -= dmg;
    std::cout << name << " zadal " << dmg << "dmg!\n";
    if (!m1.isAlive()) {
        std::cout << m1.name << " znokautowny!\n";
    }
}

bool monster::isAlive() {
    alive = health > 0;
    return alive;
}

void monster::revivePokemon() {
    health = maxHealth;
    power = maxPower;
    agility = maxAgility;
}

void monster::evolution() {
    if (exp >= 500){
        for (int i = 0; i < 2; i++){
            std::cout << "Wybierz atrybuty to ewolucji: \n [1] - health\t [2] - power\t [3] - agility\n";
            int decision;
            std::cin >> decision;
            switch (decision) {
                case 1:{
                    health += (maxHealth*0.2);
                    maxHealth = maxHealth*1.2;
                } break;
                case 2:{
                    power += (maxPower*0.2);
                    maxPower = maxPower*1.2;
                } break;
                case 3:{
                    agility += (maxAgility*0.2);
                    maxAgility += maxAgility*1.2;
                }break;
                default: {
                    this->evolution();
                }
            }
        }
        lvl++;
        exp = 0;
        std::cout << "Pokemon " << name << " ewoluowal!\n";
    } else{
        std::cout << "Nie masz wystarczajaco expa. Brakuje ci jeszcze: " << (500 - exp) <<"exp.\n";
    }
}

void monster::isUnderInfluencedBoost() {

    if (underInfluenceBoost) {
        if (influenceCounterBoost != 0) {
            influenceCounterBoost--;
        } else {
            agility = maxAgility;
            power = maxPower;
            underInfluenceBoost = !underInfluenceBoost;
        }
    }
}

void monster::isUnderInfluencedDebuff() {
    if (underInfluenceDebuff) {
        if (influenceCounterDebuff!= 0) {
            influenceCounterDebuff--;
        } else {
            agility = maxAgility;
            power = maxPower;
            underInfluenceDebuff = !underInfluenceDebuff;
        }
    }
}

void monster::isUnderInfluenced(){
    this->isUnderInfluencedDebuff();
    this->isUnderInfluencedBoost();
}

double monster::comparatorPokemon(monster *m1, const monster &m2) {
    auto t1 = m1->type;
    auto t2 = m2.type;

    if (t1 == mt::water && t2 == mt::water) return 0.75;
    if ((t1 == mt::air && t2 == mt::earth) || (t1 == mt::earth && t2 == mt::air) ||
        (t1 == mt::air && t2 == mt::steel))
        return 0.75;
    if (t1 == mt::fire && (t2 == mt::water || t2 == mt::earth)) return 0.75;
    if (t1 == mt::ice && (t2 == mt::water || t2 == mt::fire || t2 == mt::ice)) return 0.75;
    if (t1 == mt::ice && t2 == mt::earth ) { return 1.25; }

    if (t1 == mt::steel && (t2 == mt::fire || t2 == mt::steel)) return 0.75;
    if (t1 == mt::water && (t2 == mt::earth || t2 == mt::fire)) return 1.25;

    if (t1 == mt::earth && (t2 == mt::fire || t2 == mt::ice || t2 == mt::steel)) return 1.25;
    if (t1 == mt::air && t2 == mt::ice) { return 1.25; }
    if (t1 == mt::fire && (t2 == mt::ice || t2 == mt::steel)) { return 1.25; }
    if (t1 == mt::steel && (t2 == mt::water || t2 == mt::air)) return 1.25;

    return 1.0;

};

/**
 * konstruktor kopiujący
 */
monster::monster(monster const &other)
        : name(other.name), health(other.health), power(other.power), agility(other.agility), exp(other.exp),
          type(other.type), specialPower(other.specialPower), maxHealth(other.maxHealth), lvl(other.lvl), maxAgility(other.maxAgility), maxPower(other.maxPower), underInfluenceDebuff(other.underInfluenceDebuff), underInfluenceBoost(other.underInfluenceBoost), influenceCounterDebuff(other.influenceCounterDebuff), influenceCounterBoost(other.influenceCounterBoost), alive(other.alive),amountToUsePok(other.amountToUsePok) {}




