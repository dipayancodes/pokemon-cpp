#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::string> read_pokemon_names() {
    std::vector<std::string> pokemons;
    std::ifstream file("pokemons.txt");
    std::string pokemon;
    while (std::getline(file, pokemon)) {
        pokemons.push_back(pokemon);
    }
    return pokemons;
}

void catch_pokemon(int& pokeballs, int& money, std::vector<std::string>& caught_pokemon) {
    std::vector<std::string> pokemons = read_pokemon_names();
    std::string pokemon = pokemons[rand() % pokemons.size()];
    std::cout << "A wild " << pokemon << " appears!" << std::endl;
    std::cout << "Enter 'C' to catch or 'R' to run: ";
    char action;
    std::cin >> action;
    if (action == 'C' || action == 'c') {
        if (pokeballs > 0) {
            pokeballs--;
            if (static_cast<double>(rand()) / RAND_MAX < 0.5) {
                std::cout << "You caught the " << pokemon << "!" << std::endl;
                caught_pokemon.push_back(pokemon);
            } else {
                std::cout << pokemon << " escaped!" << std::endl;
            }
        } else {
            std::cout << "You don't have any pokeballs!" << std::endl;
        }
    } else {
        std::cout << "You ran away!" << std::endl;
    }
}

void visit_shop(int& pokeballs, int& money) {
    std::cout << "Welcome to the Shop!" << std::endl;
    std::cout << "Pokeballs: $10 each" << std::endl;
    int quantity;
    std::cout << "Enter the number of pokeballs you want to buy: ";
    std::cin >> quantity;
    if (money >= (10 * quantity)) {
        pokeballs += quantity;
        money -= 10 * quantity;
        std::cout << "You bought " << quantity << " pokeballs!" << std::endl;
    } else {
        std::cout << "You don't have enough money!" << std::endl;
    }
}

void battle(int& level, int& money) {
    int opponent_level = rand() % 10 + 1;
    std::cout << "A wild Pokemon (Level " << opponent_level << ") appears!" << std::endl;
    while (true) {
        std::cout << "Enter 'A' to attack or 'R' to run: ";
        char action;
        std::cin >> action;
        if (action == 'A' || action == 'a') {
            int player_attack = rand() % level + 1;
            int opponent_attack = rand() % opponent_level + 1;
            if (player_attack >= opponent_attack) {
                std::cout << "You won the battle!" << std::endl;
                money += opponent_level * 10;
                level++;
                break;
            } else {
                std::cout << "You lost the battle!" << std::endl;
                break;
            }
        } else if (action == 'R' || action == 'r') {
            std::cout << "You ran away!" << std::endl;
            break;
        } else {
            std::cout << "Invalid input. Try again!" << std::endl;
        }
    }
}

void see_caught_pokemon(const std::vector<std::string>& caught_pokemon) {
    std::cout << "\nCaught Pokemon:" << std::endl;
    if (!caught_pokemon.empty()) {
        for (const std::string& pokemon : caught_pokemon) {
            std::cout << pokemon << std::endl;
        }
    } else {
        std::cout << "No Pokemon caught yet!" << std::endl;
    }
}

void play_game() {
    std::string player_name;
    std::cout << "Enter your player name: ";
    std::cin >> player_name;

    int pokeballs = 5;
    int money = 100;
    int level = 1;
    std::vector<std::string> caught_pokemon;

    while (level <= 10) {
        std::cout << "\n----- Level " << level << " -----" << std::endl;
        std::cout << "Player: " << player_name << std::endl;
        std::cout << "Pokeballs: " << pokeballs << std::endl;
        std::cout << "Money: $" << money << std::endl;
        std::cout << "Enter 'C' to catch a Pokemon, 'S' to visit the shop, 'B' to battle, 'P' to see caught Pokemon, or 'Q' to quit: ";
        char action;
        std::cin >> action;

        if (action == 'C' || action == 'c') {
            catch_pokemon(pokeballs, money, caught_pokemon);
        } else if (action == 'S' || action == 's') {
            visit_shop(pokeballs, money);
        } else if (action == 'B' || action == 'b') {
            battle(level, money);
        } else if (action == 'P' || action == 'p') {
            see_caught_pokemon(caught_pokemon);
        } else if (action == 'Q' || action == 'q') {
            std::cout << "Thanks for playing!" << std::endl;
            break;
        } else {
            std::cout << "Invalid input. Try again!" << std::endl;
        }
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << "Welcome to the Pokemon Game!" << std::endl;
    play_game();
    return 0;
}

