#pragma once
#include <string>
#include <vector>
#include <map>
#include <string>
#include <memory>

struct special_power;

struct monster {
    enum class monster_type {
        water = 1,
        earth = 2,
        fire = 3,
        air = 4,
        ice = 5,
        steel = 6
    };

    int lvl;
    std::string name;
    int maxHealth;
    int maxPower;
    int maxAgility;
    int health;
    int power;
    int agility;
    int exp;
    monster_type type;
    special_power *specialPower;
    bool alive = (health > 0);
    bool underInfluenceBoost;
    bool underInfluenceDebuff;
    int influenceCounterBoost;
    int influenceCounterDebuff;
    int amountToUsePok;


    monster();

    monster(int nameIndex);

    monster(monster const &other);

    /**
     * Wybiera losowo skill dla pokemona odpowiedni dla jego typu
     */
    void chooseSpecialSkill();

    /**
     * Pula nazw dla pokemonów
     */
    std::vector<std::string> names = std::vector<std::string>{
            "Ka5a", "Hvmak", "Sowa", "Kebab", "Doctor", "Wrogonastawiony", "Koks", "Skarab", "Russo", "Corel",
            "Wercik", "Darioth", "Rzeznik", "Martyna",  "Ewelina"
    };

    /**
     * Pula typów do wylosowania
     */
    std::map<int, monster_type> types = std::map<int, monster::monster_type>{
            {1, monster_type::water},
            {2, monster_type::earth},
            {3, monster_type::fire},
            {4, monster_type::air},
            {5, monster_type::ice},
            {6, monster_type::steel}
    };


    /**
 * Ustawia atrybuty
 */
    void set_attributes();

    void set_max_min_attributes(int health_min, int health_max, int power_min, int power_max, int agility_min,
                                int agility_max);

    /**
     * @return typ pokemona
     */
    std::string show_type() const;

    /**
     * @return informacje o obiektecie
     */
    std::string show();

    /**
     * atakuje
     */
    void attack(monster &m1);

    bool isAlive();

    /**
     * @return mnożnik wykorzystywany przy oddziaływaniu pokemonów
     */
    double comparatorPokemon(monster *m1, monster const &m2);

    /**
     * Wskrzeszenie pokemona, i zdjecie z niego debuffow/buffow
     */
    void revivePokemon();

    /**
     * Ewolucja pokemona
     */
    void evolution();

    /**
     * Sprawdza czy pokemon powinien być jeszcze pod wpływem specjalnej umiejętności, a jeśli nie to zmienia mu statystki
     */
    void isUnderInfluencedBoost();
    void isUnderInfluencedDebuff();

    void isUnderInfluenced();

};