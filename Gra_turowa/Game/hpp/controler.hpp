#pragma once
#include "game.hpp"
struct controler {
    /**
     * Ekran starotwy
     */
    static void welcome();

    /**
     * Ustawia nazwę gry, poziom trudności
     */
    static void newGame(game &game);

    /**
     * Pozwala ustawić nazwę dla zapisu
     */
    static void nameGame(game &game);

    /**
     * Generowanie pokemonow do wyboru, wybor pokemonow dla gracza i przeciwnikow
     */
    static void generateMonstersForPlayer(game &game);

    /**
     * Walka
     */
    static void round(game &game);

    /**
     * Zmiana pokemona na ręce
     */
    static void changePokemon(game &game);

/**
 * Wyswietlenie druzyny pokemonow
 */
    static void showTeam(std::vector<monster> team);

    /**
     * zapisuje gre
     */
    static void save(game &game);

    static void revivePokemons(std::vector<monster>& vector, monster& monsterAtHand);

    static void help();

    static void enemyAttack(game &game, bool specialP);
};




