#include "game.h"
#include "builder.h"
#include <vector>

Game::Game(unsigned seed) {
    board = std::make_unique<Board>(generateRandomBoard(seed));
    builders.push_back(std::make_unique<Builder>(0, 'B', seed));
    builders.push_back(std::make_unique<Builder>(1, 'R', seed));
    builders.push_back(std::make_unique<Builder>(2, 'O', seed));
    builders.push_back(std::make_unique<Builder>(3, 'Y', seed));
    currentBuilder = 0;
}

Game::Game(unsigned seed, std::vector<TileInitData> data) {
    board = std::make_unique<Board>(data);
    builders.push_back(std::make_unique<Builder>(0, 'B', seed));
    builders.push_back(std::make_unique<Builder>(1, 'R', seed));
    builders.push_back(std::make_unique<Builder>(2, 'O', seed));
    builders.push_back(std::make_unique<Builder>(3, 'Y', seed));
    currentBuilder = 0;
}

Game::Game(unsigned seed, std::vector<TileInitData>data, std::vector<BuilderResourceData> resourceData, std::vector<BuilderStructureData> structureData, int currentBuilder, int GeeseTile) {
    std::vector<std::pair<Builder&, BuilderStructureData>> structures; 
    builders.push_back(std::make_unique<Builder>(0, 'B', seed));
    builders.push_back(std::make_unique<Builder>(1, 'R', seed));
    builders.push_back(std::make_unique<Builder>(2, 'O', seed));
    builders.push_back(std::make_unique<Builder>(3, 'Y', seed));
    for (int i = 0; i < builders.size(); i++) {
        builders[i]->inventory[Resource::BRICK] = resourceData[i].brickNum;
        builders[i]->inventory[Resource::ENERGY] = resourceData[i].energyNum;
        builders[i]->inventory[Resource::GLASS] = resourceData[i].glassNum;
        builders[i]->inventory[Resource::HEAT] = resourceData[i].heatNum;
        builders[i]->inventory[Resource::WIFI] = resourceData[i].wifiNum;
        structures.emplace_back(std::make_pair(builders[i], structureData[i]));
    }
    board = std::make_unique<Board>(data, structures);  
    this->currentBuilder = currentBuilder;
    board->setGeeseTile(GeeseTile);  
}

std::vector<TileInitData> Game::generateRandomBoard(unsigned seed) {
    std::default_random_engine rng{seed};
    std::vector<TileInitData> data;
    std::vector<int> tileValues = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::vector<Resource> resources;
    resources.insert(resources.end(), 3, Resource::WIFI);
    resources.insert(resources.end(), 3, Resource::HEAT);
    resources.insert(resources.end(), 4, Resource::BRICK);
    resources.insert(resources.end(), 4, Resource::ENERGY);
    resources.insert(resources.end(), 4, Resource::GLASS);

    // Shuffle resources
    shuffle(resources.begin(), resources.end(), rng);
    for (int i = 0; i < 18; i++) {
        data.push_back(TileInitData{tileValues[i], resources[i]});
    }
    data.push_back(TileInitData{7, Resource::PARK});
    shuffle(data.begin(), data.end(), rng);
    return data;
}
int Game::getCurrentBuilder() const {
    return currentBuilder;
}

std::vector<const Builder*> Game::getBuilders() const {
    std::vector<const Builder*> builders;
    for (const std::unique_ptr<Builder>& b : this->builders)
        builders.push_back(b.get());
    return builders;
}

int Game::getGooseLocation() const {
    return board->getGeeseTile();
}

const Board& Game::getBoard() const {
    return *board;
}

void Game::play() {
    // TODO
}
