#include "filehandler.h"
#include "../board/board.h"
#include "../common/resource.h"
#include <fstream>
#include <vector>

FileHandler::FileHandler(Game&) : game{game} {}

FileHandler::~FileHandler() {}

void FileHandler::loadFromGame(std::string filename) {
    // TODO
}

void FileHandler::loadFromBoard(std::string filename) {
    std::vector<TileInitData> data;
    int resource;
    int tileValue;
    std::ifstream dataFile{filename};
    while (dataFile >> resource >> tileValue) {
        data.push_back(TileInitData{tileValue, resourceFromInt(resource)});
    }
    dataFile.close();
    // TODO integrity checks
    // TODO call function from Game
}

void FileHandler::save(std::string) {
    // TODO
}
