#include "gamefactory.h"
#include "../board/board.h"
#include "../board/edge.h"
#include "../board/vertex.h"
#include "../common/resource.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "builder.h"
#include "game.h"
#include <fstream>
#include <memory>
#include <vector>

GameFactory::GameFactory(unsigned seed) : seed{seed} {}

GameFactory::~GameFactory() {}

std::unique_ptr<Game> GameFactory::loadFromGame(std::string filename) {
    // TODO
}

std::unique_ptr<Game> GameFactory::loadFromBoard(std::string filename) {
    std::vector<TileInitData> data;
    Resource resource;
    int tileValue;
    std::ifstream dataFile{filename};
    while (dataFile >> resource >> tileValue) {
        data.push_back(TileInitData{tileValue, resource});
    }
    dataFile.close();
    // TODO integrity checks
    // TODO call function from Game
    return std::make_unique<Game>(seed, data);
}

void GameFactory::save(std::string filename, Game& game) {
    std::ofstream outputFile{filename};
    outputFile << game.getCurrentBuilder() << std::endl;
    for (const Builder* b : game.getBuilders()) {
        // Resource inventory
        outputFile << b->inventory.at(Resource::BRICK) << " " << b->inventory.at(Resource::ENERGY) << " " << b->inventory.at(Resource::GLASS) << " " << b->inventory.at(Resource::HEAT) << " " << b->inventory.at(Resource::WIFI) << std::endl;
        // Roads
        outputFile << "r";
        for (const std::shared_ptr<Road>& r : b->roads) {
            outputFile << " " << r->getLocation().getEdgeNumber();
        }
        // Residences
        outputFile << " h";
        for (const std::shared_ptr<Residence>& h : b->residences) {
            outputFile << " " << h->getLocation().getVertexNumber() << " " << h->getResidenceLetter();
        }
        outputFile << std::endl;
    }
    for (int i = 0; i < Board::NUM_TILES; i++) {
        outputFile << game.getBoard().getTile(i)->getResource() << " " << game.getBoard().getTile(i)->getTileValue();
    }
    outputFile << std::endl;
    outputFile << game.getGooseLocation() << std::endl;
    outputFile.close();
}
