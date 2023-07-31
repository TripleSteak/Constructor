#include "game.h"
#include "../board/board.h"
#include "../board/edge.h"
#include "../board/vertex.h"
#include "../common/inventoryupdate.h"
#include "../common/randomengine.h"
#include "../common/trade.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "builder.h"
#include <fstream>
#include <map>
#include <string>
#include <vector>

Game::Game() : currentBuilder{0} {
    board = std::make_unique<Board>(generateRandomBoard());
    builders.push_back(std::make_unique<Builder>(0, 'B'));
    builders.push_back(std::make_unique<Builder>(1, 'R'));
    builders.push_back(std::make_unique<Builder>(2, 'O'));
    builders.push_back(std::make_unique<Builder>(3, 'Y'));
}

Game::Game(std::vector<TileInitData> data) : currentBuilder{0} {
    board = std::make_unique<Board>(data);
    builders.push_back(std::make_unique<Builder>(0, 'B'));
    builders.push_back(std::make_unique<Builder>(1, 'R'));
    builders.push_back(std::make_unique<Builder>(2, 'O'));
    builders.push_back(std::make_unique<Builder>(3, 'Y'));
}

Game::Game(std::vector<TileInitData> data, std::vector<BuilderResourceData> resourceData, std::vector<BuilderStructureData> structureData, int currentBuilder, int GeeseTile) : currentBuilder{currentBuilder} {
    builders.push_back(std::make_unique<Builder>(0, 'B', resourceData[0]));
    builders.push_back(std::make_unique<Builder>(1, 'R', resourceData[1]));
    builders.push_back(std::make_unique<Builder>(2, 'O', resourceData[2]));
    builders.push_back(std::make_unique<Builder>(3, 'Y', resourceData[3]));

    std::vector<std::pair<Builder*, BuilderStructureData>> structures = {{builders.at(0).get(), structureData.at(0)}, {builders.at(1).get(), structureData.at(1)}, {builders.at(2).get(), structureData.at(2)}, {builders.at(3).get(), structureData.at(3)}};
    board = std::make_unique<Board>(data, structures);
    board->setGeeseTile(GeeseTile);
}

Game::~Game() {}

std::vector<TileInitData> Game::generateRandomBoard() {
    std::vector<TileInitData> data;
    std::vector<int> tileValues = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    std::vector<Resource> resources;

    resources.insert(resources.end(), 3, Resource::WIFI);
    resources.insert(resources.end(), 3, Resource::HEAT);
    resources.insert(resources.end(), 4, Resource::BRICK);
    resources.insert(resources.end(), 4, Resource::ENERGY);
    resources.insert(resources.end(), 4, Resource::GLASS);

    // Shuffle resources
    shuffle(resources.begin(), resources.end(), RandomEngine::getEngine());
    for (int i = 0; i < 18; i++) {
        data.push_back(TileInitData{tileValues[i], resources[i]});
    }
    data.push_back(TileInitData{7, Resource::PARK});
    shuffle(data.begin(), data.end(), RandomEngine::getEngine());
    return data;
}

int Game::getCurrentBuilder() const {
    return currentBuilder;
}

const std::vector<const Builder*> Game::getBuilders() const {
    std::vector<const Builder*> builders;
    for (const std::unique_ptr<Builder>& b : this->builders)
        builders.push_back(b.get());
    return builders;
}

int Game::getGeeseLocation() const {
    return board->getGeeseTile();
}

const Board& Game::getBoard() const {
    return *board;
}

Builder& Game::getBuilder(std::string colour) {
    if (colour == "Blue") {
        return *builders.at(0);
    }
    else if (colour == "Red") {
        return *builders.at(1);
    }
    else if (colour == "Orange") {
        return *builders.at(2);
    }
    else if (colour == "Yellow") {
        return *builders.at(3);
    }
    else {
        throw std::invalid_argument("Invalid colour");
    }
}

void Game::manageTrade(Builder& proposee, Trade trade, std::ostream& out) {
    Builder& builder = *builders.at(currentBuilder);
    if (builder.inventory[trade.resourceToGive] > 0 && proposee.inventory[trade.resourceToTake] > 0) {
        builder.inventory[trade.resourceToGive]--;
        builder.inventory[trade.resourceToTake]++;
        proposee.inventory[trade.resourceToGive]++;
        proposee.inventory[trade.resourceToTake]--;
        out << "Trade completed." << std::endl;
    }
    else if (builder.inventory[trade.resourceToGive] == 0) {
        out << "You do not have any " << trade.resourceToGive << " to trade." << std::endl;
    }
    else if (proposee.inventory[trade.resourceToTake] == 0) {
        out << proposee.getBuilderColourString() << " does not have any " << trade.resourceToTake << " to trade." << std::endl;
    }
}

void Game::buildInitialResidences(std::istream& in, std::ostream& out) {
    int vertex;
    // build initial residences
    for (int i = 0; i < NUM_BUILDERS; i++) {
        out << "Builder " << builders[i]->getBuilderColourString() << ", where do you want to build a basement?" << std::endl;
        in >> vertex;
        while (!board->buildInitialResidence(*builders[i], vertex, out)) {
            out << "Builder " << builders[i]->getBuilderColourString() << ", where do you want to build a basement?" << std::endl;
            in >> vertex;
        }
    }
    for (int i = NUM_BUILDERS - 1; i >= 0; i--) {
        out << "Builder " << builders[i]->getBuilderColourString() << ", where do you want to build a basement?" << std::endl;
        in >> vertex;
        while (!board->buildInitialResidence(*builders[i], vertex, out)) {
            out << "Builder " << builders[i]->getBuilderColourString() << ", where do you want to build a basement?" << std::endl;
            in >> vertex;
        }
    }
}

std::vector<Resource> Game::discardRandomResource(Builder& builder, bool half) {
    std::vector<Resource> resources;
    for (auto const& resource : builder.inventory) {
        for (int i = 0; i < resource.second; i++) {
            resources.push_back(resource.first);
        }
    }
    std::shuffle(resources.begin(), resources.end(), rng);
    std::vector<Resource> resourcesToDiscard;
    if (half && resources.size() >= 10) { // discard half
        for (size_t i = 0; i < resources.size() / 2; i++) {
            resourcesToDiscard.push_back(resources[i]);
        }
    }
    else if (!half) { // steal one
        resourcesToDiscard.push_back(resources[0]);
    }
    return resourcesToDiscard; // if empty then less than 10
}

void Game::moveGeese(std::istream& in, std::ostream& out) {
    Builder& builder = *builders.at(currentBuilder);
    for (int i = 0; i < NUM_BUILDERS; i++) {
        std::vector<Resource> discard = discardRandomResource(*builders[i], true);
        std::map<Resource, int> discardNum;
        if (discard.size() > 0) {
            out << "Builder " << builders[i]->getBuilderColourString() << " loses" << discard.size() << " resources to the geese. They lose:" << std::endl;
            for (size_t i = 0; i < discard.size(); i++) {
                out << discard[i] << std::endl;
                builders[i]->inventory[discard[i]]--;
                discardNum[discard[i]]++;
            }
            // print out discarded resources
            for (auto const& resource : discardNum) {
                out << resource.first << " " << resource.second << std::endl;
            }
        }
    }
    int tile;
    out << "Choose where to place the GEESE.";
    in >> tile;
    while (tile != getGeeseLocation()) {
        out << "Where do you want to place the GEESE?";
        in >> tile;
    }
    board->setGeeseTile(tile);

    AbstractTile* t = board->getTile(tile);
    std::vector<int> neighbouringBuilders = t->getNeighbouringResidences(builder);
    out << "Builder " << builder.getBuilderColourString() << " can choose to steal from:";

    if (neighbouringBuilders.size() == 0) {
        out << "Builder " << builder.getBuilderColourString() << " has no builders to steal from." << std::endl;
        return;
    }

    for (size_t i = 0; i < neighbouringBuilders.size() - 1; i++) {
        out << " " << builders[neighbouringBuilders[i]]->getBuilderColourString() << ",";
    }
    out << " " << builders[neighbouringBuilders[neighbouringBuilders.size() - 1]]->getBuilderColourString() << std::endl;

    out << "Choose a builder to steal from." << std::endl;

    std::string builderToStealFromColour;
    in >> builderToStealFromColour;
    Builder& builderToStealFrom = getBuilder(builderToStealFromColour);

    Resource resourceToSteal = discardRandomResource(builderToStealFrom, false)[0];
    builder.inventory[resourceToSteal]++;
    builderToStealFrom.inventory[resourceToSteal]--;
    out << "Builder " << builder.getBuilderColourString() << " steals " << resourceToString(resourceToSteal) << " from builder " << builderToStealFrom.getBuilderColourString() << std::endl;
}

void Game::save(std::string filename) {
    std::ofstream outputFile{filename};
    outputFile << getCurrentBuilder() << std::endl;
    for (const Builder* b : getBuilders()) {
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
        outputFile << getBoard().getTile(i)->getResource() << " " << getBoard().getTile(i)->getTileValue();
    }
    outputFile << std::endl;
    outputFile << getGeeseLocation() << std::endl;
    outputFile.close();
}

void Game::beginTurn(std::istream& in, std::ostream& out) {
    Builder& builder = *builders.at(currentBuilder);
    std::string command;
    int roll;
    int loaded = 0;

    out << "Builder " << builder.getBuilderColourString() << "'s turn." << std::endl;
    out << builder.getStatus() << std::endl;
    out << (in.fail() ? "1" : "0") << std::endl;

    while (in >> command) {
        if (command == "load") {
            builder.setDice(true);
        }
        else if (command == "fair") {
            builder.setDice(false);
        }
        else if (command == "roll") {
            if (builder.getDice()) {
                while (loaded < 2 || loaded > 12) {
                    out << "Input a roll between 2 and 12:" << std::endl;
                    out << loaded << std::endl;
                    out << (in.fail() ? "1" : "0") << std::endl;
                    in >> loaded;
                    out << "1";
                    if (loaded < 2 || loaded > 12) {
                        out << "Invalid roll." << std::endl;
                    }
                }
            }
            roll = builder.rollDice(loaded);
            if (roll == 7) {
                moveGeese(in, out);
            }
            else { // distribute resources
                BuilderInventoryUpdate b = board->getResourcesFromDiceRoll(roll);
                if (!b.changed()) {
                    out << "No builder gained resources." << std::endl;
                }
                else {
                    // Output resources gained
                    if (b.b1.at(Resource::BRICK) > 0 || b.b1.at(Resource::ENERGY) > 0 || b.b1.at(Resource::GLASS) > 0 || b.b1.at(Resource::HEAT) > 0 || b.b1.at(Resource::WIFI) > 0) {
                        out << "Builder " << builders.at(0)->getBuilderColourString() << " gained:" << std::endl;
                        if (b.b1.at(Resource::BRICK) > 0) {
                            out << b.b1.at(Resource::BRICK) << " BRICK" << std::endl;
                        }
                        if (b.b1.at(Resource::ENERGY) > 0) {
                            out << b.b1.at(Resource::ENERGY) << " ENERGY" << std::endl;
                        }
                        if (b.b1.at(Resource::GLASS) > 0) {
                            out << b.b1.at(Resource::GLASS) << " GLASS" << std::endl;
                        }
                        if (b.b1.at(Resource::HEAT) > 0) {
                            out << b.b1.at(Resource::HEAT) << " HEAT" << std::endl;
                        }
                        if (b.b1.at(Resource::WIFI) > 0) {
                            out << b.b1.at(Resource::WIFI) << " WIFI" << std::endl;
                        }
                    }
                    if (b.b2.at(Resource::BRICK) > 0 || b.b2.at(Resource::ENERGY) > 0 || b.b2.at(Resource::GLASS) > 0 || b.b2.at(Resource::HEAT) > 0 || b.b2.at(Resource::WIFI) > 0) {
                        out << "Builder " << builders.at(1)->getBuilderColourString() << " gained:" << std::endl;
                        if (b.b2.at(Resource::BRICK) > 0) {
                            out << b.b2.at(Resource::BRICK) << " BRICK" << std::endl;
                        }
                        if (b.b2.at(Resource::ENERGY) > 0) {
                            out << b.b2.at(Resource::ENERGY) << " ENERGY" << std::endl;
                        }
                        if (b.b2.at(Resource::GLASS) > 0) {
                            out << b.b2.at(Resource::GLASS) << " GLASS" << std::endl;
                        }
                        if (b.b2.at(Resource::HEAT) > 0) {
                            out << b.b2.at(Resource::HEAT) << " HEAT" << std::endl;
                        }
                        if (b.b2.at(Resource::WIFI) > 0) {
                            out << b.b2.at(Resource::WIFI) << " WIFI" << std::endl;
                        }
                    }
                    if (b.b3.at(Resource::BRICK) > 0 || b.b3.at(Resource::ENERGY) > 0 || b.b3.at(Resource::GLASS) > 0 || b.b3.at(Resource::HEAT) > 0 || b.b3.at(Resource::WIFI) > 0) {
                        out << "Builder " << builders.at(2)->getBuilderColourString() << " gained:" << std::endl;
                        if (b.b3.at(Resource::BRICK) > 0) {
                            out << b.b3.at(Resource::BRICK) << " BRICK" << std::endl;
                        }
                        if (b.b3.at(Resource::ENERGY) > 0) {
                            out << b.b3.at(Resource::ENERGY) << " ENERGY" << std::endl;
                        }
                        if (b.b3.at(Resource::GLASS) > 0) {
                            out << b.b3.at(Resource::GLASS) << " GLASS" << std::endl;
                        }
                        if (b.b3.at(Resource::HEAT) > 0) {
                            out << b.b3.at(Resource::HEAT) << " HEAT" << std::endl;
                        }
                        if (b.b3.at(Resource::WIFI) > 0) {
                            out << b.b3.at(Resource::WIFI) << " WIFI" << std::endl;
                        }
                    }
                    if (b.b4.at(Resource::BRICK) > 0 || b.b4.at(Resource::ENERGY) > 0 || b.b4.at(Resource::GLASS) > 0 || b.b4.at(Resource::HEAT) > 0 || b.b4.at(Resource::WIFI) > 0) {
                        out << "Builder " << builders.at(3)->getBuilderColourString() << " gained:" << std::endl;
                        if (b.b4.at(Resource::BRICK) > 0) {
                            out << b.b4.at(Resource::BRICK) << " BRICK" << std::endl;
                        }
                        if (b.b4.at(Resource::ENERGY) > 0) {
                            out << b.b4.at(Resource::ENERGY) << " ENERGY" << std::endl;
                        }
                        if (b.b4.at(Resource::GLASS) > 0) {
                            out << b.b4.at(Resource::GLASS) << " GLASS" << std::endl;
                        }
                        if (b.b4.at(Resource::HEAT) > 0) {
                            out << b.b4.at(Resource::HEAT) << " HEAT" << std::endl;
                        }
                        if (b.b4.at(Resource::WIFI) > 0) {
                            out << b.b4.at(Resource::WIFI) << " WIFI" << std::endl;
                        }
                    }
                }
            }
            duringTurn(in, out, roll);
            return;
        }
        else {
            out << "Invalid command." << std::endl;
        }
    }
}

void Game::duringTurn(std::istream& in, std::ostream& out, int roll) {
    std::string command;
    while (in >> command && builders[0]->getBuildingPoints() < 10 && builders[1]->getBuildingPoints() < 10 && builders[2]->getBuildingPoints() < 10 && builders[3]->getBuildingPoints() < 10) {
        Builder& builder = *builders.at(currentBuilder);
        if (command == "board") {
            board->printBoard(out);
        }
        else if (command == "status") {
            for (size_t i = 0; i < builders.size(); i++) {
                out << builders[i]->getStatus() << std::endl;
            }
        }
        else if (command == "residences") {
            out << "Builder " << builder.getBuilderColourString() << " has built:" << std::endl;
            for (size_t i = 0; i < builder.residences.size(); i++) {
                out << builder.residences[i]->getLocation().getVertexNumber() << " " << builder.residences[i]->getResidenceLetter();
            }
        }
        else if (command.substr(0, 10) == "build-road") {
            board->buildRoad(builder, std::stoi(command.substr(11, 1)), out);
        }
        else if (command.substr(0, 9) == "build-res") {
            board->buildResidence(builder, std::stoi(command.substr(10, 1)), out);
        }
        else if (command.substr(0, 7) == "improve") {
            board->upgradeResidence(builder, std::stoi(command.substr(8, 1)), out);
        }
        else if (command.substr(0, 5) == "trade") {
            std::string space = " ";
            command.erase(0, 6);

            // get builder
            int pos = command.find_first_of(space);
            std::string proposeeColour = command.substr(0, pos);
            command.erase(0, pos + 1);

            // get give
            pos = command.find_first_of(space);
            std::string give = command.substr(0, pos);
            command.erase(0, pos + 1);

            // get take
            std::string take = command;

            Trade trade = builder.proposeTrade(proposeeColour, give, take, out);
            Builder& proposee = getBuilder(proposeeColour);
            if (proposee.respondToTrade(in, out)) {
                manageTrade(proposee, trade, out);
            }
        }
        else if (command == "next") {
            nextTurn(in, out);
            return;
        }
        else if (command.substr(0, 4) == "save") {
            save(command.substr(5, command.length() - 5));
        }
        else if (command == "help") {
            out << "Valid commands:" << std::endl;
            out << "board" << std::endl;
            out << "status" << std::endl;
            out << "residences" << std::endl;
            out << "build-road <edge#>" << std::endl;
            out << "build-res <housing#>" << std::endl;
            out << "improve <housing#>" << std::endl;
            out << "trade <colour> <give> <take>" << std::endl;
            out << "next" << std::endl;
            out << "save <file>" << std::endl;
            out << "help" << std::endl;
        }
        else {
            out << "Invalid command." << std::endl;
        }
    }
}

void Game::nextTurn(std::istream& in, std::ostream& out) {
    currentBuilder++;
    if (currentBuilder == 4) {
        currentBuilder = 0;
    }
    beginTurn(in, out);
}

bool Game::play(std::istream& in, std::ostream& out) {
    buildInitialResidences(in, out);
    board->printBoard(out);
    beginTurn(in, out);
    if (builders[0]->getBuildingPoints() == 10 || builders[1]->getBuildingPoints() == 10 || builders[2]->getBuildingPoints() == 10 || builders[3]->getBuildingPoints() == 10) {
        return true;
    }
    return false;
}
