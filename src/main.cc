#include "common/randomengine.h"
#include "game/game.h"
#include "game/gamefactory.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <unordered_map>

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, std::string> args;

    assert(argc > 1);
    // Process the command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        // Tags that come with a value
        if (arg == "-seed" || arg == "-load" || arg == "-board") {
            if (i + 1 < argc) {
                args[arg] = argv[i + 1];
                i++;
            }
            else {
                std::cout << "Error: Missing value for " << arg << " tag." << std::endl;
                return 1;
            }
        }
        // Tags that are just flags
        else if (arg == "-random-board") {
            args[arg] = "T";
        }
        else {
            std::cout << "Error: Unrecognized tag " << arg << std::endl;
            return 1;
        }
    }

    // Create the game
    if (args["-seed"].empty()) {
        RandomEngine::setSeed(1); //set to default to same 
    }
    else {
        RandomEngine::setSeed(std::stoul(args["-seed"]));
    }
    GameFactory factory;
    std::unique_ptr<Game> game;

    // Game loop
    bool newGame = true;
    while (true) {
        if (!args["-load"].empty()) {
            game = factory.loadFromGame(args["-load"]);
            newGame = false;
        }
        else if (!args["-board"].empty()) {
            game = factory.loadFromBoard(args["-board"]);
        }
        else if (!args["-random-board"].empty()) {
            game = factory.loadFromRandomBoard();
        }
        else {
            std::cout << "Error: No board configuration specified." << std::endl;
            return 1;
        }
        // Play game, returns true if finished and false if unfinished
        if (game->play(std::cin, std::cout, newGame)) {
            std::cout << "Would you like to play again?" << std::endl;
            std::string resp;
            while (std::cin >> resp) {
                if (resp == "yes") {
                    // Restart a new game with random configuration and new seed
                    args["-seed"] = "";
                    args["-load"] = "";
                    args["-board"] = "";
                    args["-random-board"] = "T";
                    newGame = true;
                    break;
                }
                else if (resp == "no") {
                    return 0;
                }
                else {
                    std::cout << "Error: Invalid response. Answer yes or no." << std::endl;
                }
            }
        }
        else {
            // if unfinished, save game
            game->save("backup.sv");
            return 0;
        }
    }
}
