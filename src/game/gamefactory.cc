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
#include <sstream>
#include <vector>

GameFactory::GameFactory(unsigned seed) : seed{seed} {}

GameFactory::~GameFactory() {}

std::unique_ptr<Game> GameFactory::loadFromGame(std::string filename) {
#include <iostream>
    std::vector<TileInitData> tileData;
    std::vector<BuilderResourceData> builderResourceData;
    std::vector<BuilderStructureData> builderStructureData;
    std::string currentBuilder;
    std::ifstream dataFile{filename};
    getline(dataFile, currentBuilder);

    // Builder status
    std::string line;
    for (int i = 0; i < Game::NUM_BUILDERS; i++) {
        getline(dataFile, line);
        std::istringstream ss{line};
        int brickNum, energyNum, glassNum, heatNum, wifiNum;
        ss >> brickNum >> energyNum >> glassNum >> heatNum >> wifiNum;
        builderResourceData.push_back(BuilderResourceData{brickNum, energyNum, glassNum, heatNum, wifiNum});
        std::string token;
        ss >> token; // ignore one token, should be 'r'
        std::vector<int> roads;
        ss >> token;
        while (token != "h") {
            roads.push_back(std::stoi(token));
            ss >> token;
        }
        std::vector<std::pair<int, char>> residences;
        int vertexNum;
        char residenceType;
        while (ss >> vertexNum >> residenceType) {
            residences.emplace_back(vertexNum, residenceType);
        }
        builderStructureData.emplace_back(residences, roads);
    }
    // Resource layour
    getline(dataFile, line);
    std::istringstream ss{line};
    Resource resource;
    int tileValue;
    while (ss >> resource >> tileValue) {
        tileData.push_back(TileInitData{tileValue, resource});
    }
    int geeseTile;
    dataFile >> geeseTile;
    dataFile.close();
    return std::make_unique<Game>(seed, tileData, builderResourceData, builderStructureData, std::stoi(currentBuilder), geeseTile);
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
    return std::make_unique<Game>(seed, data);
}
