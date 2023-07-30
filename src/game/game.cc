#include "game.h"

std::vector<TileInitData> Game::generateRandomBoard() {
    std::vector<TileInitData> data;
    std::vector<int> tileValues = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::vector<Resource> resources;

    // load resources
    for (int i = 0; i < 3; i++) {
        resources.push_back(Resource::WIFI);
    }
    for (int i = 0; i < 3; i++) {
        resources.push_back(Resource::HEAT);
    }
    for (int i = 0; i < 4; i++) {
        resources.push_back(Resource::BRICK);
    }
    for (int i = 0; i < 4; i++) {
        resources.push_back(Resource::ENERGY);
    }
    for (int i = 0; i < 4; i++) {
        resources.push_back(Resource::GLASS);
    }

    // shuffle resources
    for (int i = 0; i < 18; i++) {
        shuffle(resources.begin(), resources.end(), rng);
        shuffle(tileValues.begin(), tileValues.end(), rng);
        data.push_back(TileInitData{tileValues.back(), resources.back()});
        resources.pop_back();
        tileValues.pop_back();
    }
    data.push_back(TileInitData{7, Resource::PARK});
    shuffle(data.begin(), data.end(), rng);
    return data;
}
