
#include <iostream>
#include "hpp/controler.hpp"
#include "hpp/game.hpp"
#include "algorithm"
#include <set>
#include <map>
#include <random>

void controler::welcome() {
    std::string decision;
    do {
        std::cout << "-----------------------------------------\n";
        std::cout << "| Witaj w grze \"RTG - Richer than gods\" |\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "\n[1] - nowa gra";
        std::cout << "\n[2] - wczytaj gre";
        std::cout << "\n[0] - wyjdz";
        std::cin >> decision;
    } while (!(decision == "1" || decision == "2" || decision == "0"));

    switch (std::stoi(decision)) {
        case 1: {
            game game;
            controler::nameGame(game); //nazywamy gre
            controler::newGame(game); // tworzymy gre, poziom trudnosci i ilosc przeciwników
            controler::generateMonstersForPlayer(game); // generacja potworów

            for (int i = 0; i < game.round; i++) {
                controler::round(game);
                std::cout << "Koniec rundy!\n";
                game.round++;
                controler::revivePokemons(game.player.team, game.player.hand);
                std::string decision;
                do {
                    std::cout << "[1] - graj dalej\t[2] - zapisz - gre\t[0] - wyjdz\n";
                    std::cin >> decision;
                } while (!(decision == "1" || decision == "2" || decision == "0"));

                switch (std::stoi(decision)){
                    case 1:
                        continue;
                        break;
                    case 2: {
                        controler::save(game);

                    }
                        break;
                    case 0:{
                        exit(0);
                    }
                }
            }
        }
            break;
        case 2: {
            std::cout << "Wczytano gre! (w przyszlosci)\t";
            std::cout << "Tworzymy nowa gre.\n";
            controler::welcome();

        }break;
        case 0:{
            return;
        }
        default:
            controler::welcome();
    }
}

void controler::nameGame(game &game) {
    std::string nameGame;
    std::cout << "Nazwa gry: \n";
    std::cin >> nameGame;
    game.name = nameGame;
}

void controler::newGame(game &game) {
    std::string decision;
    game.difficulty_level = 0;
    do {
        std::cout << "\nWybierz poziom trudnosci: ";
        std::cout << "\n[1] - easy";
        std::cout << "\n[2] - medium";
        std::cout << "\n[3] - hard\n";
        std::cin >> decision;
        if (decision == "1" || decision == "2" || decision == "3") {
            game.difficulty_level = std::stoi(decision);
            game.enemyAlive = 3 + std::stoi(decision);
        }
    } while (game.difficulty_level == 0);

}

void controler::generateMonstersForPlayer(game &game) {
    std::map<int, monster> monsterToChoose;
    for (int i = 0; i < 15; i++) {
        monster monsterToAdd = monster(i);
        monsterToChoose[i] = monsterToAdd;
        int counter = i;
        std::cout << "----------[" + std::to_string(counter + 1) + "]-----------\n";
        std::cout << monsterToChoose[i].show();
        std::cout << "-------------------------\n";
    }

    int decision;
    std::set<int> decisions;
    while (decisions.size() != 6) {
        std::cout << "Wybierz swoja druzyne:";
        std::cin >> decision;
        if (decision > 0 && decision <= 15) {
            decisions.insert(decision - 1);
        }
    }

    for (int index: decisions) {
        game.player.team.push_back(monsterToChoose[index]); //dodaje wybrane pokemony do koszyka gracza
        monsterToChoose.erase(index); //usuwam wybranego pokemona z puli dla przeciwnikow
    }


    std::vector<int> indexToChooseForEnemy;

    for (auto e: monsterToChoose) {
        indexToChooseForEnemy.push_back(e.first);
    }

/**
 * Wykorzystany algorytm losowania/mieszania ze strony https://en.cppreference.com/w/cpp/algorithm/ranges/shuffle
 */
    for (int enemyCounter = 0; enemyCounter < game.enemyAlive; enemyCounter++) {
        std::vector<monster> vector = std::vector<monster>();

        std::set<int> choseIndexes;
        std::random_device rd;
        std::mt19937 gen{rd()};
        while (choseIndexes.size() != (4 + game.difficulty_level - 1)) {
            std::ranges::shuffle(indexToChooseForEnemy, gen);
            choseIndexes.insert(indexToChooseForEnemy[0]);
        }


        for (auto e: choseIndexes) {
            vector.push_back(monsterToChoose[e]);
        }
        game.enemy_team.push_back(vector);
    }

    std::cout << "\nWybrane pokemony: \n";
    for (int i = 0; i < game.player.team.size(); i++) {
        std::cout << game.player.team[i].name;
        std::cout << '\t';
    }

    std::cout << "\nENEMY TEAM: \n";
    for (std::vector<monster> m: game.enemy_team) {
        for (monster e: m) {
            std::cout << e.name << '\t';
        }
        std::cout << "\n";
    }
}

void controler::round(game &game) {
    if (game.round ==1) {
        game.player.hand = game.player.team[0];
        game.player.team.erase(game.player.team.begin());
    }
    std::cout << "\nRunda nr: " << game.round << '\n';
    std::cout << "Pokemon przeciwnika: \n" << game.enemy_team[0][0].show() << '\n';
    std::cout << "Twoj pokemon: \n" << game.player.hand.show() << '\n';

    while (!game.enemy_team[0].empty()) {
        std::string decision;
        do {
            std::cout
                    << "[1] - atakuj\t[2] - zmien pokemona\t[3] - umiejetnosc specjalna\t[4] - pokaz pokemony\t[5] - ewolucja\n";
            std::cin >> decision;
            if (decision == "-h" || decision == "--help") {
                controler::help();
            }
        } while (!(decision == "1" || decision == "2" || decision == "3" || decision == "4" || decision == "5"));


        switch (std::stoi(decision)) {
            case 1: {

                controler::enemyAttack(game, false);
            }
                break;
            case 2: {
                controler::showTeam(game.player.team);
                controler::changePokemon(game);
            }
                break;
            case 3: {
                controler::enemyAttack(game, true);
            }
                break;
            case 4: {
                std::cout << "Pokemon na rece:\n";
                std::cout << game.player.hand.show();
                std::cout << "Twoja druzyna:\n";
                controler::showTeam(game.player.team);
                std::cout << "\nPrzeciwnika druzyna:\n";
                controler::showTeam(game.enemy_team[0]);
            }
                break;
            case 5: {
                game.player.hand.evolution();
            }
        }
    }
    if (game.enemy_team.empty()) {
        std::cout << "Koniec gry!";
        controler::welcome();
    }
    game.enemy_team.erase(game.enemy_team.begin());
}

void controler::changePokemon(game &game) {
    int pokeDecision;
    std::cout << "Podaj numer pokemona: \n";
    std::cin >> pokeDecision;

    if (pokeDecision > game.player.team.size()) {
        controler::changePokemon(game);
    }
    game.player.team.push_back(game.player.hand);
    game.player.hand = game.player.team[pokeDecision - 1];
    game.player.team.erase(game.player.team.begin() + (pokeDecision - 1));
    std::cout << "Zmieniles pokemona na: " << game.player.hand.name << '\n';
}

void controler::showTeam(std::vector<monster> team) {
    int counter = 1;
    for (auto pokemon: team) {
        std::cout << counter << " " << pokemon.show() << '\n';
        counter++;
    }
}

void controler::save(game &game) {
    std::cout << "czy chcesz zapisac gre?\t\t[1] - tak\t[2] - nie";
    int decision;
    std::cin >> decision;
    switch (decision) {
        case 1: {
            //zapis gry
            std::cout << "Zapis gry! (w przyszlosci)\n";
            return;
        }
            break;
        case 2: {
            return;
        }
            break;
        default: {
            controler::save(game);
        }
            break;
    }
}

void controler::revivePokemons(std::vector<monster>& vector, monster& monsterAtHand ) {
    for (monster& p: vector) {
        p.revivePokemon();
        p.alive = true;
    }
    monsterAtHand.revivePokemon();
    monsterAtHand.alive = true;
}

void controler::help() {
    std::cout << "\n----------------------HELP----------------------------\n";
    std::cout << "| Wykorzystuj klawiature do interakcji z programem   |\n";
    std::cout << "| Zwracaj uwage na typ pokemona. Niektore pokemony   |\n";
    std::cout << "| sa lepsze przeciwko danemu typowi i ich ataki sa   |\n";
    std::cout << "| wzmacniane a nie ktore sa labsze i ich ataki sa    |\n";
    std::cout << "| debuffowane.                                       |\n";
    std::cout << "| Gdy zbierzesz 500exp mozesz ewoulowac pokemona.    |\n";
    std::cout << "| Ulepszaj statystyki ktore sa premiowane.           |\n";
    std::cout << "| Mozesz uzywac specjalnych umiejetnosci. Jesli,     |\n";
    std::cout << "| nie bedziesz mogl jej uzyc wykona sie zwykly atak. |\n";
    std::cout << "| Ewolucja:                                          |\n";
    std::cout << "| Za zabicie pokemona przeciwnika dostajesz 100expa. |\n";
    std::cout << "| Po otrzymaniu 500 exp mozesz ewoluowac pokemona.   |\n";
    std::cout << "| Mozesz wtedy wybrac 2 umiejtnosci ktore chcesz     |\n";
    std::cout << "| ulepszyc o 0.2 maksymalnej wartosci.               |\n";
    std::cout << "| Umiejetnosci:                                      |\n";
    std::cout << "| 1. Blizzard wizard. Agility +20pkt. 2 / 2          |\n";
    std::cout << "| 2. Healing dealing. Health +50pkt. 3/1             |\n";
    std::cout << "| 3. Fire ball. Health enemy -50pkt. 3/1             |\n";
    std::cout << "| 4. Tornado obbligato. Agility enemy -20pkt 2/2     |\n";
    std::cout << "| 5. Ground strenghening. Power +70 2/2              |\n";
    std::cout << "| 6. Freezing brezzing Agility enemy -20pkt. 2/2     |\n";
    std::cout << "| 7. Conflagration creation. Health enemy -50pkt 2/1 |\n";
    std::cout << "| 8. Steel embrace arms race. Health enemy -50pkt 3/1|\n";
    std::cout << "| 9. Rain pain. Health enemy -50pkt 3/1              |\n";
    std::cout << "| 10. Fire dance. Agility +50pkt 2/2                 |\n";
    std::cout << "| 11. World enhancement. Power +30pkt 1/3            |\n";
    std::cout << "| 12. H2O - Just add water. Power +30 2/1            |\n";
    std::cout << "| 13. Overwhelming fire. Power enemy -20 1/3         |\n";
    std::cout << "| 14. Crushing of steel. Power enemy -20 2/2         |\n";
    std::cout << "| 15. Avalanche. Power enemy -10 2/3                 |\n";
    std::cout << "----------------------HELP----------------------------\n";
}

void controler::enemyAttack(game &game, bool specialP){
    //gracz atakuje
    if (specialP && game.player.hand.specialPower->use(game.player.hand, game.enemy_team[0][0])){
        game.player.hand.isUnderInfluenced();
    } else{
        game.player.hand.attack(game.enemy_team[0][0]);

    }
    //jesli enemy zostal znokautowany usuwamy go z puli do przeciwnika
    if (!game.enemy_team[0][0].isAlive()) {
        game.player.hand.exp += 100;
        game.enemy_team[0].erase(game.enemy_team[0].begin());
    }

    int los = (std::rand() % 2) + 1;
    if (los == 1 && game.enemy_team[0][0].specialPower->use(game.enemy_team[0][0], game.player.hand)){
        std::cout << game.enemy_team[0][0].name << " uzywa specjalnej umiejetnosci!\n";
    } else{
        game.enemy_team[0][0].attack(game.player.hand);
        game.enemy_team[0][0].isUnderInfluenced();
    }

    //przeciwnik atakuje
    std::cout << '\n';
    std::cout << "Twoj pokemon: " << game.player.hand.name << ' ' << game.player.hand.show_type() << ' '
              << game.player.hand.health << "hp" << '\t';
    std::cout << "Pokemon przeciwnika: " << game.enemy_team[0][0].name << ' '
              << game.enemy_team[0][0].show_type() << ' ' << game.enemy_team[0][0].health << "hp\n";


    //szukamy pokemona ktory zyje
    if (!game.player.hand.isAlive()) {
        game.player.team.push_back(game.player.hand);
        int counter = 0;
        monster aliveMonster = game.player.team[counter];
        while (!aliveMonster.isAlive()) {
            counter++;
            if (counter == 6) {
                std::string decision;
                do {
                    std::cout << "Koniec gry!\n Zostales pokonany!\t Sprobuj ponownie!\n[1] - nowa gra [0] - wyjdz\n";
                    std::cin >> decision;
                } while (!(decision == "1" || decision == "0"));

                switch (std::stoi(decision)) {
                    case 1: {
                        controler::welcome();
                        return;
                    }                    break;

                    case 0:{
                        exit(0);
                    }
                }

                return;
            }
            aliveMonster = game.player.team[counter];

        }
        //zmiana martwego pokemona
        game.player.hand = game.player.team[counter];
        game.player.team.erase(game.player.team.begin() + counter);
        std::cout << "Twoj pokemon to teraz: \n" << game.player.hand.show() << '\n';
    }
}


