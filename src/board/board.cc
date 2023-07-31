#include "board.h"
#include "../game/builder.h"
#include "../structures/basement.h"
#include "../structures/house.h"
#include "../structures/residence.h"
#include "../structures/road.h"
#include "../structures/tower.h"
#include "edge.h"
#include "geesetile.h"
#include "tile.h"
#include "vertex.h"

Board::Board(std::vector<TileInitData> tileInitData) : geeseTile{-1} {
    for (int i = 0; i < NUM_TILES; i++) {
        tiles.push_back(std::make_unique<Tile>(i, tileInitData.at(i).tileValue, tileInitData.at(i).resource));

        // Assume there is only one park tile
        if (tileInitData.at(i).resource == Resource::PARK) {
            setGeeseTile(i);
        }
    }

    for (int i = 0; i < NUM_EDGES; i++) {
        edges.push_back(std::make_unique<Edge>(i));
    }

    for (int i = 0; i < NUM_VERTICES; i++) {
        vertices.push_back(std::make_unique<Vertex>(i));
    }

    setupVertices();
    setupEdges();
    setupTiles();
}

Board::Board(std::vector<TileInitData> tileInitData, std::vector<std::pair<Builder*, BuilderStructureData>> structureData) : Board(tileInitData) {
    for (auto& pair : structureData) {
        Builder* builder = pair.first;
        BuilderStructureData data = pair.second;

        for (size_t i = 0; i < data.roads.size(); i++) {
            setRoad(*builder, data.roads.at(i));
        }
        for (size_t i = 0; i < data.residences.size(); i++) {
            setResidence(*builder, data.residences.at(i).first, data.residences.at(i).second);
        }
    }
}

Board::~Board() {}

void Board::setResidence(Builder& builder, int vertexNumber, char residenceType) {
    Vertex* vertex = getVertex(vertexNumber);
    if (residenceType == 'B') {
        std::shared_ptr<Residence> residence = std::make_shared<Basement>(builder, *vertex);
        builder.residences.push_back(residence);
        vertex->buildResidence(residence);
    }
    else if (residenceType == 'H') {
        std::shared_ptr<Residence> residence = std::make_shared<House>(builder, *vertex);
        builder.residences.push_back(residence);
        vertex->buildResidence(residence);
    }
    else if (residenceType == 'T') {
        std::shared_ptr<Residence> residence = std::make_shared<Tower>(builder, *vertex);
        builder.residences.push_back(residence);
        vertex->buildResidence(residence);
    }
}

void Board::setRoad(Builder& builder, int edgeNumber) {
    Edge* edge = getEdge(edgeNumber);
    std::shared_ptr<Road> road = std::make_shared<Road>(builder, *edge);
    builder.roads.push_back(road);
    edge->buildRoad(road);
}

AbstractTile* Board::getTile(int tileNumber) const {
    return tiles.at(tileNumber).get();
}

Vertex* Board::getVertex(int vertexNumber) const {
    return vertices.at(vertexNumber).get();
}

Edge* Board::getEdge(int edgeNumber) const {
    return edges.at(edgeNumber).get();
}

bool Board::buildRoad(Builder& builder, int edgeNumber, std::ostream& out) {
    Edge* edge = getEdge(edgeNumber);

    // check if can build road on edge
    if (!edge->canBuildRoad(builder)) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    // check if builder has resources to build road
    std::shared_ptr<Road> road = builder.tryBuildRoad(*edge);

    if (road != nullptr) {
        edge->buildRoad(road);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}

bool Board::buildResidence(Builder& builder, int vertexNumber, std::ostream& out) {
    Vertex* vertex = getVertex(vertexNumber);

    // check if can build residence on vertex
    if (!vertex->canBuildResidence(builder)) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    // check if builder has resources to build residence
    std::shared_ptr<Residence> residence = builder.tryBuildResidence(*vertex);

    if (residence != nullptr) {
        vertex->buildResidence(residence);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}

bool Board::buildInitialResidence(Builder& builder, int vertexNumber, std::ostream& out) {
    Vertex* vertex = getVertex(vertexNumber);

    // check if can build residence on vertex
    if (!vertex->canBuildInitialResidence()) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    std::shared_ptr<Residence> residence = builder.tryBuildInitialResidence(*vertex);
    vertex->buildResidence(residence);
    return true;
}

bool Board::upgradeResidence(Builder& builder, int vertexNumber, std::ostream& out) {
    Vertex* vertex = getVertex(vertexNumber);

    // check if can upgrade residence on vertex
    if (!vertex->canUpgradeResidence(builder)) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    // check if builder has resources to upgrade residence
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(*vertex);

    if (residence != nullptr) {
        vertex->upgradeResidence(residence);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}

int Board::getGeeseTile() const {
    return geeseTile;
}

void Board::setGeeseTile(int newGeeseTile) {
    // Remove existing geese tiles, if applicable
    if (geeseTile != -1) {
        tiles.at(geeseTile) = tiles.at(geeseTile).get()->removeGeese();
    }

    // Incorporate the new geese tile
    tiles.at(newGeeseTile) = std::make_unique<GeeseTile>(std::move(tiles.at(newGeeseTile)));
}

void Board::getResourcesFromDiceRoll(int rollNumber) const {
    for (size_t i = 0; i < tiles.size(); i++) {
        if (tiles.at(i)->getTileValue() == rollNumber) {
            tiles.at(i)->giveResourcesToBuilders();
        }
    }
}

void Board::printBoard(std::ostream& out) const {
    out << "                          " + printVertex(0) + printEdge(0, true) + printVertex(1) << std::endl;
    out << "                            |         |" << std::endl;
    out << "                           " << printEdge(1, false) + "    0   " + printEdge(2, false) << std::endl;
    out << "                            |" + printResource(0) + "|" << std::endl;
    out << "                " + printVertex(2) + printEdge(3, true) + printVertex(3) + printTile(0) + printVertex(4) + printEdge(4, true) + printVertex(5) << std::endl;
    out << "                  |         |" + printGeese(0) + "|         |" << std::endl;
    out << "                 " + printEdge(5, false) + "    1   " + printEdge(6, false) + "        " + printEdge(7, false) + "    2   " + printEdge(8, false) << std::endl;
    out << "                  |" + printResource(1) + "|         |" + printResource(2) + "|" << std::endl;
    out << "      " + printVertex(6) + printEdge(9, true) + printVertex(7) + printTile(1) + printVertex(8) + printEdge(10, true) + printVertex(9) + printTile(2) + printVertex(10) + printEdge(11, true) + printVertex(11) << std::endl;
    out << "        |         |" + printGeese(1) + "|         |" + printGeese(2) + "|         |" << std::endl;
    out << "       " + printEdge(12, false) + "    3   " + printEdge(13, false) + "        " + printEdge(14, false) + "    4   " + printEdge(15, false) + "        " + printEdge(16, false) + "    5   " + printEdge(17, false) << std::endl;
    out << "        |" + printResource(3) + "|         |" + printResource(4) + "|         |" + printResource(5) + "|" << std::endl;
    out << "      " + printVertex(12) + printTile(3) + printVertex(13) + printEdge(18, true) + printVertex(14) + printTile(4) + printVertex(15) + printEdge(19, true) + printVertex(16) + printTile(5) + printVertex(17) << std::endl;
    out << "        |" + printGeese(3) + "|         |" + printGeese(4) + "|         |" + printGeese(5) + "|" << std::endl;
    out << "       " + printEdge(20, false) + "        " + printEdge(21, false) + "    6   " + printEdge(22, false) + "        " + printEdge(23, false) + "    7   " + printEdge(24, false) + "        " + printEdge(25, false) << std::endl;
    out << "        |         |" + printResource(6) + "|         |" + printResource(7) + "|         |" << std::endl;
    out << "      " + printVertex(18) + printEdge(26, true) + printVertex(19) + printTile(6) + printVertex(20) + printEdge(27, true) + printVertex(21) + printTile(7) + printVertex(22) + printEdge(28, true) + printVertex(23) << std::endl;
    out << "        |         |" + printGeese(6) + "|         |" + printGeese(7) + "|         |" << std::endl;
    out << "       " + printEdge(29, false) + "    8   " + printEdge(30, false) + "        " + printEdge(31, false) + "    9   " + printEdge(32, false) + "        " + printEdge(33, false) + "   10   " + printEdge(34, false) << std::endl;
    out << "        |" + printResource(8) + "|         |" + printResource(9) + "|         |" + printResource(10) + "|" << std::endl;
    out << "      " + printVertex(24) + printTile(8) + printVertex(25) + printEdge(35, true) + printVertex(26) + printTile(9) + printVertex(27) + printEdge(36, true) + printVertex(28) + printTile(10) + printVertex(29) << std::endl;
    out << "        |" + printGeese(8) + "|         |" + printGeese(9) + "|         |" + printGeese(10) + "|" << std::endl;
    out << "       " + printEdge(37, false) + "        " + printEdge(38, false) + "   11   " + printEdge(39, false) + "        " + printEdge(40, false) + "   12   " + printEdge(41, false) + "        " + printEdge(42, false) << std::endl;
    out << "        |         |" + printResource(11) + "|         |" + printResource(12) + "|         |" << std::endl;
    out << "      " + printVertex(30) + printEdge(43, true) + printVertex(31) + printTile(11) + printVertex(32) + printEdge(44, true) + printVertex(33) + printTile(12) + printVertex(34) + printEdge(45, true) + printVertex(35) << std::endl;
    out << "        |         |" + printGeese(11) + "|         |" + printGeese(12) + "|         |" << std::endl;
    out << "       " + printEdge(46, false) + "   13   " + printEdge(47, false) + "        " + printEdge(48, false) + "   14   " + printEdge(49, false) + "        " + printEdge(50, false) + "   15   " + printEdge(51, false) << std::endl;
    out << "        |" + printResource(13) + "|         |" + printResource(14) + "|         |" + printResource(15) + "|" << std::endl;
    out << "      " + printVertex(36) + printTile(13) + printVertex(37) + printEdge(52, true) + printVertex(38) + printTile(14) + printVertex(39) + printEdge(53, true) + printVertex(40) + printTile(15) + printVertex(41) << std::endl;
    out << "        |" + printGeese(13) + "|         |" + printGeese(14) + "|         |" + printGeese(15) + "|" << std::endl;
    out << "       " + printEdge(54, false) + "        " + printEdge(55, false) + "   16   " + printEdge(56, false) + "        " + printEdge(57, false) + "   17   " + printEdge(58, false) + "        " + printEdge(59, false) << std::endl;
    out << "        |         |" + printResource(16) + "|         |" + printResource(17) + "|         |" << std::endl;
    out << "      " + printVertex(42) + printEdge(60, true) + printVertex(43) + printTile(16) + printVertex(44) + printEdge(61, true) + printVertex(45) + printTile(17) + printVertex(46) + printEdge(62, true) + printVertex(47) << std::endl;
    out << "                  |" + printGeese(16) + "|         |" + printGeese(17) + "|" << std::endl;
    out << "                 " + printEdge(63, false) + "        " + printEdge(64, false) + "   18   " + printEdge(65, false) + "        " + printEdge(66, false) << std::endl;
    out << "                  |         |" + printResource(18) + "|         |" << std::endl;
    out << "                " + printVertex(48) + printEdge(67, true) + printVertex(49) + printTile(18) + printVertex(50) + printEdge(68, true) + printVertex(51) << std::endl;
    out << "                            |" + printGeese(18) + "|" << std::endl;
    out << "                           " + printEdge(69, false) + "        " + printEdge(70, false) << std::endl;
    out << "                            |         |" << std::endl;
    out << "                          " + printVertex(52) + printEdge(71, true) + printVertex(53) << std::endl;
}

std::string Board::printVertex(int vertexNumber) const {
    Vertex* vertex = getVertex(vertexNumber);
    std::string vertexString = "|";

    if (vertex->getResidence() == nullptr) {
        if (vertexNumber < 10) {
            vertexString += " ";
        }
        vertexString += std::to_string(vertexNumber) + "|";
    }
    else {
        vertexString += std::to_string(vertex->getResidence()->getOwner().getBuilderColour()) + std::to_string(vertex->getResidence()->getResidenceLetter()) + "|";
    }

    return vertexString;
}

std::string Board::printEdge(int edgeNumber, bool isHorizontal) const {
    Edge* edge = getEdge(edgeNumber);
    std::string edgeString = "";

    if (isHorizontal) {
        edgeString += "--";
    }

    if (edge->getRoad() == nullptr) {
        if (edgeNumber < 10) {
            edgeString += " ";
        }
        edgeString += std::to_string(edgeNumber);
    }
    else {
        edgeString += std::to_string(edge->getRoad()->getOwner().getBuilderColour()) + "R";
    }

    if (isHorizontal) {
        edgeString += "--";
    }

    return edgeString;
}

std::string Board::printTile(int tileNumber) const {
    AbstractTile* tile = getTile(tileNumber);
    std::string tileString = "  ";

    if (tile->getTileValue() == 7) {
        tileString += "    ";
        return tileString;
    }

    if (tile->getTileValue() < 10) {
        tileString += " ";
    }

    tileString += std::to_string(tile->getTileValue());
    tileString += "  ";
    return tileString;
}

std::string Board::printResource(int tileNumber) const {
    AbstractTile* tile = getTile(tileNumber);
    Resource resource = tile->getResource();

    // Add leading spaces
    std::string tileString = resource == ENERGY ? " " : "  ";

    // Append Resource as string
    tileString += resourceToString(resource);

    // Append trailing spaces
    tileString += resource <= GLASS ? "  " : "   ";

    return tileString;
}

std::string Board::printGeese(int tileNumber) const {
    AbstractTile* tile = getTile(tileNumber);
    std::string tileString = "";

    if (tile->hasGeese()) {
        tileString += "  GEESE  ";
    }
    else {
        tileString += "         ";
    }

    return tileString;
}

void Board::setupVertices() {
    vertices[0]->addNeighbouringEdge(edges[0].get());
    vertices[0]->addNeighbouringEdge(edges[1].get());
    vertices[0]->addNeighbouringTile(tiles[0].get());

    vertices[1]->addNeighbouringEdge(edges[0].get());
    vertices[1]->addNeighbouringEdge(edges[2].get());
    vertices[1]->addNeighbouringTile(tiles[0].get());

    vertices[2]->addNeighbouringEdge(edges[3].get());
    vertices[2]->addNeighbouringEdge(edges[5].get());
    vertices[2]->addNeighbouringTile(tiles[1].get());

    vertices[3]->addNeighbouringEdge(edges[1].get());
    vertices[3]->addNeighbouringEdge(edges[3].get());
    vertices[3]->addNeighbouringEdge(edges[6].get());
    vertices[3]->addNeighbouringTile(tiles[0].get());
    vertices[3]->addNeighbouringTile(tiles[1].get());

    vertices[4]->addNeighbouringEdge(edges[2].get());
    vertices[4]->addNeighbouringEdge(edges[4].get());
    vertices[4]->addNeighbouringEdge(edges[7].get());
    vertices[4]->addNeighbouringTile(tiles[0].get());
    vertices[4]->addNeighbouringTile(tiles[2].get());

    vertices[5]->addNeighbouringEdge(edges[4].get());
    vertices[5]->addNeighbouringEdge(edges[8].get());
    vertices[5]->addNeighbouringTile(tiles[2].get());

    vertices[6]->addNeighbouringEdge(edges[9].get());
    vertices[6]->addNeighbouringEdge(edges[12].get());
    vertices[6]->addNeighbouringTile(tiles[3].get());

    vertices[7]->addNeighbouringEdge(edges[5].get());
    vertices[7]->addNeighbouringEdge(edges[9].get());
    vertices[7]->addNeighbouringEdge(edges[13].get());
    vertices[7]->addNeighbouringTile(tiles[1].get());
    vertices[7]->addNeighbouringTile(tiles[3].get());

    vertices[8]->addNeighbouringEdge(edges[6].get());
    vertices[8]->addNeighbouringEdge(edges[10].get());
    vertices[8]->addNeighbouringEdge(edges[14].get());
    vertices[8]->addNeighbouringTile(tiles[0].get());
    vertices[8]->addNeighbouringTile(tiles[1].get());
    vertices[8]->addNeighbouringTile(tiles[4].get());

    vertices[9]->addNeighbouringEdge(edges[7].get());
    vertices[9]->addNeighbouringEdge(edges[10].get());
    vertices[9]->addNeighbouringEdge(edges[15].get());
    vertices[9]->addNeighbouringTile(tiles[0].get());
    vertices[9]->addNeighbouringTile(tiles[2].get());
    vertices[9]->addNeighbouringTile(tiles[4].get());

    vertices[10]->addNeighbouringEdge(edges[8].get());
    vertices[10]->addNeighbouringEdge(edges[11].get());
    vertices[10]->addNeighbouringEdge(edges[16].get());
    vertices[10]->addNeighbouringTile(tiles[2].get());
    vertices[10]->addNeighbouringTile(tiles[5].get());

    vertices[11]->addNeighbouringEdge(edges[11].get());
    vertices[11]->addNeighbouringEdge(edges[17].get());
    vertices[11]->addNeighbouringTile(tiles[5].get());

    vertices[12]->addNeighbouringEdge(edges[12].get());
    vertices[12]->addNeighbouringEdge(edges[20].get());
    vertices[12]->addNeighbouringTile(tiles[3].get());

    vertices[13]->addNeighbouringEdge(edges[13].get());
    vertices[13]->addNeighbouringEdge(edges[18].get());
    vertices[13]->addNeighbouringEdge(edges[21].get());
    vertices[13]->addNeighbouringTile(tiles[1].get());
    vertices[13]->addNeighbouringTile(tiles[3].get());
    vertices[13]->addNeighbouringTile(tiles[6].get());

    vertices[14]->addNeighbouringEdge(edges[14].get());
    vertices[14]->addNeighbouringEdge(edges[18].get());
    vertices[14]->addNeighbouringEdge(edges[22].get());
    vertices[14]->addNeighbouringTile(tiles[1].get());
    vertices[14]->addNeighbouringTile(tiles[4].get());
    vertices[14]->addNeighbouringTile(tiles[6].get());

    vertices[15]->addNeighbouringEdge(edges[15].get());
    vertices[15]->addNeighbouringEdge(edges[19].get());
    vertices[15]->addNeighbouringEdge(edges[23].get());
    vertices[15]->addNeighbouringTile(tiles[2].get());
    vertices[15]->addNeighbouringTile(tiles[4].get());
    vertices[15]->addNeighbouringTile(tiles[7].get());

    vertices[16]->addNeighbouringEdge(edges[16].get());
    vertices[16]->addNeighbouringEdge(edges[19].get());
    vertices[16]->addNeighbouringEdge(edges[24].get());
    vertices[16]->addNeighbouringTile(tiles[2].get());
    vertices[16]->addNeighbouringTile(tiles[5].get());
    vertices[16]->addNeighbouringTile(tiles[7].get());

    vertices[17]->addNeighbouringEdge(edges[17].get());
    vertices[17]->addNeighbouringEdge(edges[25].get());
    vertices[17]->addNeighbouringTile(tiles[5].get());

    vertices[18]->addNeighbouringEdge(edges[20].get());
    vertices[18]->addNeighbouringEdge(edges[26].get());
    vertices[18]->addNeighbouringEdge(edges[29].get());
    vertices[18]->addNeighbouringTile(tiles[3].get());
    vertices[18]->addNeighbouringTile(tiles[8].get());

    vertices[19]->addNeighbouringEdge(edges[21].get());
    vertices[19]->addNeighbouringEdge(edges[26].get());
    vertices[19]->addNeighbouringEdge(edges[30].get());
    vertices[19]->addNeighbouringTile(tiles[3].get());
    vertices[19]->addNeighbouringTile(tiles[6].get());
    vertices[19]->addNeighbouringTile(tiles[8].get());

    vertices[20]->addNeighbouringEdge(edges[22].get());
    vertices[20]->addNeighbouringEdge(edges[27].get());
    vertices[20]->addNeighbouringEdge(edges[31].get());
    vertices[20]->addNeighbouringTile(tiles[4].get());
    vertices[20]->addNeighbouringTile(tiles[6].get());
    vertices[20]->addNeighbouringTile(tiles[9].get());

    vertices[21]->addNeighbouringEdge(edges[23].get());
    vertices[21]->addNeighbouringEdge(edges[27].get());
    vertices[21]->addNeighbouringEdge(edges[32].get());
    vertices[21]->addNeighbouringTile(tiles[4].get());
    vertices[21]->addNeighbouringTile(tiles[7].get());
    vertices[21]->addNeighbouringTile(tiles[9].get());

    vertices[22]->addNeighbouringEdge(edges[24].get());
    vertices[22]->addNeighbouringEdge(edges[28].get());
    vertices[22]->addNeighbouringEdge(edges[33].get());
    vertices[22]->addNeighbouringTile(tiles[5].get());
    vertices[22]->addNeighbouringTile(tiles[7].get());
    vertices[22]->addNeighbouringTile(tiles[10].get());

    vertices[23]->addNeighbouringEdge(edges[25].get());
    vertices[23]->addNeighbouringEdge(edges[28].get());
    vertices[23]->addNeighbouringEdge(edges[34].get());
    vertices[23]->addNeighbouringTile(tiles[5].get());
    vertices[23]->addNeighbouringTile(tiles[10].get());

    vertices[24]->addNeighbouringEdge(edges[29].get());
    vertices[24]->addNeighbouringEdge(edges[37].get());
    vertices[24]->addNeighbouringTile(tiles[8].get());

    vertices[25]->addNeighbouringEdge(edges[30].get());
    vertices[25]->addNeighbouringEdge(edges[35].get());
    vertices[25]->addNeighbouringEdge(edges[38].get());
    vertices[25]->addNeighbouringTile(tiles[6].get());
    vertices[25]->addNeighbouringTile(tiles[8].get());
    vertices[25]->addNeighbouringTile(tiles[11].get());

    vertices[26]->addNeighbouringEdge(edges[31].get());
    vertices[26]->addNeighbouringEdge(edges[35].get());
    vertices[26]->addNeighbouringEdge(edges[39].get());
    vertices[26]->addNeighbouringTile(tiles[6].get());
    vertices[26]->addNeighbouringTile(tiles[9].get());
    vertices[26]->addNeighbouringTile(tiles[11].get());

    vertices[27]->addNeighbouringEdge(edges[32].get());
    vertices[27]->addNeighbouringEdge(edges[36].get());
    vertices[27]->addNeighbouringEdge(edges[40].get());
    vertices[27]->addNeighbouringTile(tiles[7].get());
    vertices[27]->addNeighbouringTile(tiles[9].get());
    vertices[27]->addNeighbouringTile(tiles[12].get());

    vertices[28]->addNeighbouringEdge(edges[33].get());
    vertices[28]->addNeighbouringEdge(edges[36].get());
    vertices[28]->addNeighbouringEdge(edges[41].get());
    vertices[28]->addNeighbouringTile(tiles[7].get());
    vertices[28]->addNeighbouringTile(tiles[10].get());
    vertices[28]->addNeighbouringTile(tiles[12].get());

    vertices[29]->addNeighbouringEdge(edges[34].get());
    vertices[29]->addNeighbouringEdge(edges[42].get());
    vertices[29]->addNeighbouringTile(tiles[10].get());

    vertices[30]->addNeighbouringEdge(edges[37].get());
    vertices[30]->addNeighbouringEdge(edges[43].get());
    vertices[30]->addNeighbouringEdge(edges[46].get());
    vertices[30]->addNeighbouringTile(tiles[8].get());
    vertices[30]->addNeighbouringTile(tiles[13].get());

    vertices[31]->addNeighbouringEdge(edges[38].get());
    vertices[31]->addNeighbouringEdge(edges[43].get());
    vertices[31]->addNeighbouringEdge(edges[47].get());
    vertices[31]->addNeighbouringTile(tiles[8].get());
    vertices[31]->addNeighbouringTile(tiles[11].get());
    vertices[31]->addNeighbouringTile(tiles[13].get());

    vertices[32]->addNeighbouringEdge(edges[39].get());
    vertices[32]->addNeighbouringEdge(edges[44].get());
    vertices[32]->addNeighbouringEdge(edges[48].get());
    vertices[32]->addNeighbouringTile(tiles[9].get());
    vertices[32]->addNeighbouringTile(tiles[11].get());
    vertices[32]->addNeighbouringTile(tiles[14].get());

    vertices[33]->addNeighbouringEdge(edges[40].get());
    vertices[33]->addNeighbouringEdge(edges[44].get());
    vertices[33]->addNeighbouringEdge(edges[49].get());
    vertices[33]->addNeighbouringTile(tiles[9].get());
    vertices[33]->addNeighbouringTile(tiles[12].get());
    vertices[33]->addNeighbouringTile(tiles[14].get());

    vertices[34]->addNeighbouringEdge(edges[41].get());
    vertices[34]->addNeighbouringEdge(edges[45].get());
    vertices[34]->addNeighbouringEdge(edges[50].get());
    vertices[34]->addNeighbouringTile(tiles[10].get());
    vertices[34]->addNeighbouringTile(tiles[12].get());
    vertices[34]->addNeighbouringTile(tiles[15].get());

    vertices[35]->addNeighbouringEdge(edges[42].get());
    vertices[35]->addNeighbouringEdge(edges[45].get());
    vertices[35]->addNeighbouringEdge(edges[51].get());
    vertices[35]->addNeighbouringTile(tiles[10].get());
    vertices[35]->addNeighbouringTile(tiles[15].get());

    vertices[36]->addNeighbouringEdge(edges[46].get());
    vertices[36]->addNeighbouringEdge(edges[54].get());
    vertices[36]->addNeighbouringTile(tiles[13].get());

    vertices[37]->addNeighbouringEdge(edges[47].get());
    vertices[37]->addNeighbouringEdge(edges[52].get());
    vertices[37]->addNeighbouringEdge(edges[55].get());
    vertices[37]->addNeighbouringTile(tiles[11].get());
    vertices[37]->addNeighbouringTile(tiles[13].get());
    vertices[37]->addNeighbouringTile(tiles[16].get());

    vertices[38]->addNeighbouringEdge(edges[48].get());
    vertices[38]->addNeighbouringEdge(edges[52].get());
    vertices[38]->addNeighbouringEdge(edges[56].get());
    vertices[38]->addNeighbouringTile(tiles[11].get());
    vertices[38]->addNeighbouringTile(tiles[14].get());
    vertices[38]->addNeighbouringTile(tiles[16].get());

    vertices[39]->addNeighbouringEdge(edges[49].get());
    vertices[39]->addNeighbouringEdge(edges[53].get());
    vertices[39]->addNeighbouringEdge(edges[57].get());
    vertices[39]->addNeighbouringTile(tiles[12].get());
    vertices[39]->addNeighbouringTile(tiles[14].get());
    vertices[39]->addNeighbouringTile(tiles[17].get());

    vertices[40]->addNeighbouringEdge(edges[50].get());
    vertices[40]->addNeighbouringEdge(edges[53].get());
    vertices[40]->addNeighbouringEdge(edges[58].get());
    vertices[40]->addNeighbouringTile(tiles[12].get());
    vertices[40]->addNeighbouringTile(tiles[15].get());
    vertices[40]->addNeighbouringTile(tiles[17].get());

    vertices[41]->addNeighbouringEdge(edges[51].get());
    vertices[41]->addNeighbouringEdge(edges[59].get());
    vertices[41]->addNeighbouringTile(tiles[15].get());

    vertices[42]->addNeighbouringEdge(edges[54].get());
    vertices[42]->addNeighbouringEdge(edges[60].get());
    vertices[42]->addNeighbouringTile(tiles[13].get());

    vertices[43]->addNeighbouringEdge(edges[55].get());
    vertices[43]->addNeighbouringEdge(edges[60].get());
    vertices[43]->addNeighbouringEdge(edges[63].get());
    vertices[43]->addNeighbouringTile(tiles[13].get());
    vertices[43]->addNeighbouringTile(tiles[16].get());

    vertices[44]->addNeighbouringEdge(edges[56].get());
    vertices[44]->addNeighbouringEdge(edges[61].get());
    vertices[44]->addNeighbouringEdge(edges[64].get());
    vertices[44]->addNeighbouringTile(tiles[14].get());
    vertices[44]->addNeighbouringTile(tiles[16].get());
    vertices[44]->addNeighbouringTile(tiles[18].get());

    vertices[45]->addNeighbouringEdge(edges[57].get());
    vertices[45]->addNeighbouringEdge(edges[61].get());
    vertices[45]->addNeighbouringEdge(edges[65].get());
    vertices[45]->addNeighbouringTile(tiles[14].get());
    vertices[45]->addNeighbouringTile(tiles[17].get());
    vertices[45]->addNeighbouringTile(tiles[18].get());

    vertices[46]->addNeighbouringEdge(edges[58].get());
    vertices[46]->addNeighbouringEdge(edges[62].get());
    vertices[46]->addNeighbouringEdge(edges[66].get());
    vertices[46]->addNeighbouringTile(tiles[15].get());
    vertices[46]->addNeighbouringTile(tiles[17].get());

    vertices[47]->addNeighbouringEdge(edges[59].get());
    vertices[47]->addNeighbouringEdge(edges[62].get());
    vertices[47]->addNeighbouringTile(tiles[15].get());

    vertices[48]->addNeighbouringEdge(edges[63].get());
    vertices[48]->addNeighbouringEdge(edges[67].get());
    vertices[48]->addNeighbouringTile(tiles[16].get());

    vertices[49]->addNeighbouringEdge(edges[64].get());
    vertices[49]->addNeighbouringEdge(edges[67].get());
    vertices[49]->addNeighbouringEdge(edges[69].get());
    vertices[49]->addNeighbouringTile(tiles[16].get());
    vertices[49]->addNeighbouringTile(tiles[18].get());

    vertices[50]->addNeighbouringEdge(edges[65].get());
    vertices[50]->addNeighbouringEdge(edges[68].get());
    vertices[50]->addNeighbouringEdge(edges[70].get());
    vertices[50]->addNeighbouringTile(tiles[17].get());
    vertices[50]->addNeighbouringTile(tiles[18].get());

    vertices[51]->addNeighbouringEdge(edges[66].get());
    vertices[51]->addNeighbouringEdge(edges[68].get());
    vertices[51]->addNeighbouringTile(tiles[17].get());

    vertices[52]->addNeighbouringEdge(edges[69].get());
    vertices[52]->addNeighbouringEdge(edges[71].get());
    vertices[52]->addNeighbouringTile(tiles[18].get());

    vertices[53]->addNeighbouringEdge(edges[70].get());
    vertices[53]->addNeighbouringEdge(edges[71].get());
    vertices[53]->addNeighbouringTile(tiles[18].get());
}

void Board::setupEdges() {
    edges[0]->addNeighbouringVertex(vertices[0].get());
    edges[0]->addNeighbouringVertex(vertices[1].get());

    edges[1]->addNeighbouringVertex(vertices[0].get());
    edges[1]->addNeighbouringVertex(vertices[3].get());

    edges[2]->addNeighbouringVertex(vertices[1].get());
    edges[2]->addNeighbouringVertex(vertices[4].get());

    edges[3]->addNeighbouringVertex(vertices[2].get());
    edges[3]->addNeighbouringVertex(vertices[3].get());

    edges[4]->addNeighbouringVertex(vertices[4].get());
    edges[4]->addNeighbouringVertex(vertices[5].get());

    edges[5]->addNeighbouringVertex(vertices[2].get());
    edges[5]->addNeighbouringVertex(vertices[7].get());

    edges[6]->addNeighbouringVertex(vertices[3].get());
    edges[6]->addNeighbouringVertex(vertices[8].get());

    edges[7]->addNeighbouringVertex(vertices[4].get());
    edges[7]->addNeighbouringVertex(vertices[9].get());

    edges[8]->addNeighbouringVertex(vertices[5].get());
    edges[8]->addNeighbouringVertex(vertices[10].get());

    edges[9]->addNeighbouringVertex(vertices[6].get());
    edges[9]->addNeighbouringVertex(vertices[7].get());

    edges[10]->addNeighbouringVertex(vertices[8].get());
    edges[10]->addNeighbouringVertex(vertices[9].get());

    edges[11]->addNeighbouringVertex(vertices[10].get());
    edges[11]->addNeighbouringVertex(vertices[11].get());

    edges[12]->addNeighbouringVertex(vertices[6].get());
    edges[12]->addNeighbouringVertex(vertices[12].get());

    edges[13]->addNeighbouringVertex(vertices[7].get());
    edges[13]->addNeighbouringVertex(vertices[13].get());

    edges[14]->addNeighbouringVertex(vertices[8].get());
    edges[14]->addNeighbouringVertex(vertices[14].get());

    edges[15]->addNeighbouringVertex(vertices[9].get());
    edges[15]->addNeighbouringVertex(vertices[15].get());

    edges[16]->addNeighbouringVertex(vertices[10].get());
    edges[16]->addNeighbouringVertex(vertices[16].get());

    edges[17]->addNeighbouringVertex(vertices[11].get());
    edges[17]->addNeighbouringVertex(vertices[17].get());

    edges[18]->addNeighbouringVertex(vertices[13].get());
    edges[18]->addNeighbouringVertex(vertices[14].get());

    edges[19]->addNeighbouringVertex(vertices[15].get());
    edges[19]->addNeighbouringVertex(vertices[16].get());

    edges[20]->addNeighbouringVertex(vertices[12].get());
    edges[20]->addNeighbouringVertex(vertices[18].get());

    edges[21]->addNeighbouringVertex(vertices[13].get());
    edges[21]->addNeighbouringVertex(vertices[19].get());

    edges[22]->addNeighbouringVertex(vertices[14].get());
    edges[22]->addNeighbouringVertex(vertices[20].get());

    edges[23]->addNeighbouringVertex(vertices[15].get());
    edges[23]->addNeighbouringVertex(vertices[21].get());

    edges[24]->addNeighbouringVertex(vertices[16].get());
    edges[24]->addNeighbouringVertex(vertices[22].get());

    edges[25]->addNeighbouringVertex(vertices[17].get());
    edges[25]->addNeighbouringVertex(vertices[23].get());

    edges[26]->addNeighbouringVertex(vertices[18].get());
    edges[26]->addNeighbouringVertex(vertices[19].get());

    edges[27]->addNeighbouringVertex(vertices[20].get());
    edges[27]->addNeighbouringVertex(vertices[21].get());

    edges[28]->addNeighbouringVertex(vertices[22].get());
    edges[28]->addNeighbouringVertex(vertices[23].get());

    edges[29]->addNeighbouringVertex(vertices[18].get());
    edges[29]->addNeighbouringVertex(vertices[24].get());

    edges[30]->addNeighbouringVertex(vertices[19].get());
    edges[30]->addNeighbouringVertex(vertices[25].get());

    edges[31]->addNeighbouringVertex(vertices[20].get());
    edges[31]->addNeighbouringVertex(vertices[26].get());

    edges[32]->addNeighbouringVertex(vertices[21].get());
    edges[32]->addNeighbouringVertex(vertices[27].get());

    edges[33]->addNeighbouringVertex(vertices[22].get());
    edges[33]->addNeighbouringVertex(vertices[28].get());

    edges[34]->addNeighbouringVertex(vertices[23].get());
    edges[34]->addNeighbouringVertex(vertices[29].get());

    edges[35]->addNeighbouringVertex(vertices[25].get());
    edges[35]->addNeighbouringVertex(vertices[26].get());

    edges[36]->addNeighbouringVertex(vertices[27].get());
    edges[36]->addNeighbouringVertex(vertices[28].get());

    edges[37]->addNeighbouringVertex(vertices[24].get());
    edges[37]->addNeighbouringVertex(vertices[30].get());

    edges[38]->addNeighbouringVertex(vertices[25].get());
    edges[38]->addNeighbouringVertex(vertices[31].get());

    edges[39]->addNeighbouringVertex(vertices[26].get());
    edges[39]->addNeighbouringVertex(vertices[32].get());

    edges[40]->addNeighbouringVertex(vertices[27].get());
    edges[40]->addNeighbouringVertex(vertices[33].get());

    edges[41]->addNeighbouringVertex(vertices[28].get());
    edges[41]->addNeighbouringVertex(vertices[34].get());

    edges[42]->addNeighbouringVertex(vertices[29].get());
    edges[42]->addNeighbouringVertex(vertices[35].get());

    edges[43]->addNeighbouringVertex(vertices[30].get());
    edges[43]->addNeighbouringVertex(vertices[31].get());

    edges[44]->addNeighbouringVertex(vertices[32].get());
    edges[44]->addNeighbouringVertex(vertices[33].get());

    edges[45]->addNeighbouringVertex(vertices[34].get());
    edges[45]->addNeighbouringVertex(vertices[35].get());

    edges[46]->addNeighbouringVertex(vertices[30].get());
    edges[46]->addNeighbouringVertex(vertices[36].get());

    edges[47]->addNeighbouringVertex(vertices[31].get());
    edges[47]->addNeighbouringVertex(vertices[37].get());

    edges[48]->addNeighbouringVertex(vertices[32].get());
    edges[48]->addNeighbouringVertex(vertices[38].get());

    edges[49]->addNeighbouringVertex(vertices[33].get());
    edges[49]->addNeighbouringVertex(vertices[39].get());

    edges[50]->addNeighbouringVertex(vertices[34].get());
    edges[50]->addNeighbouringVertex(vertices[40].get());

    edges[51]->addNeighbouringVertex(vertices[35].get());
    edges[51]->addNeighbouringVertex(vertices[41].get());

    edges[52]->addNeighbouringVertex(vertices[37].get());
    edges[52]->addNeighbouringVertex(vertices[38].get());

    edges[53]->addNeighbouringVertex(vertices[39].get());
    edges[53]->addNeighbouringVertex(vertices[40].get());

    edges[54]->addNeighbouringVertex(vertices[36].get());
    edges[54]->addNeighbouringVertex(vertices[42].get());

    edges[55]->addNeighbouringVertex(vertices[37].get());
    edges[55]->addNeighbouringVertex(vertices[43].get());

    edges[56]->addNeighbouringVertex(vertices[38].get());
    edges[56]->addNeighbouringVertex(vertices[44].get());

    edges[57]->addNeighbouringVertex(vertices[39].get());
    edges[57]->addNeighbouringVertex(vertices[45].get());

    edges[58]->addNeighbouringVertex(vertices[40].get());
    edges[58]->addNeighbouringVertex(vertices[46].get());

    edges[59]->addNeighbouringVertex(vertices[41].get());
    edges[59]->addNeighbouringVertex(vertices[47].get());

    edges[60]->addNeighbouringVertex(vertices[42].get());
    edges[60]->addNeighbouringVertex(vertices[43].get());

    edges[61]->addNeighbouringVertex(vertices[44].get());
    edges[61]->addNeighbouringVertex(vertices[45].get());

    edges[62]->addNeighbouringVertex(vertices[46].get());
    edges[62]->addNeighbouringVertex(vertices[47].get());

    edges[63]->addNeighbouringVertex(vertices[43].get());
    edges[63]->addNeighbouringVertex(vertices[48].get());

    edges[64]->addNeighbouringVertex(vertices[44].get());
    edges[64]->addNeighbouringVertex(vertices[49].get());

    edges[65]->addNeighbouringVertex(vertices[45].get());
    edges[65]->addNeighbouringVertex(vertices[50].get());

    edges[66]->addNeighbouringVertex(vertices[46].get());
    edges[66]->addNeighbouringVertex(vertices[51].get());

    edges[67]->addNeighbouringVertex(vertices[48].get());
    edges[67]->addNeighbouringVertex(vertices[49].get());

    edges[68]->addNeighbouringVertex(vertices[50].get());
    edges[68]->addNeighbouringVertex(vertices[51].get());

    edges[69]->addNeighbouringVertex(vertices[49].get());
    edges[69]->addNeighbouringVertex(vertices[52].get());

    edges[70]->addNeighbouringVertex(vertices[50].get());
    edges[70]->addNeighbouringVertex(vertices[53].get());

    edges[71]->addNeighbouringVertex(vertices[52].get());
    edges[71]->addNeighbouringVertex(vertices[53].get());
}

void Board::setupTiles() {
    tiles[0]->addNeighbouringVertex(vertices[0].get());
    tiles[0]->addNeighbouringVertex(vertices[1].get());
    tiles[0]->addNeighbouringVertex(vertices[3].get());
    tiles[0]->addNeighbouringVertex(vertices[4].get());
    tiles[0]->addNeighbouringVertex(vertices[8].get());
    tiles[0]->addNeighbouringVertex(vertices[9].get());

    tiles[1]->addNeighbouringVertex(vertices[2].get());
    tiles[1]->addNeighbouringVertex(vertices[3].get());
    tiles[1]->addNeighbouringVertex(vertices[7].get());
    tiles[1]->addNeighbouringVertex(vertices[8].get());
    tiles[1]->addNeighbouringVertex(vertices[13].get());
    tiles[1]->addNeighbouringVertex(vertices[14].get());

    tiles[2]->addNeighbouringVertex(vertices[4].get());
    tiles[2]->addNeighbouringVertex(vertices[5].get());
    tiles[2]->addNeighbouringVertex(vertices[9].get());
    tiles[2]->addNeighbouringVertex(vertices[10].get());
    tiles[2]->addNeighbouringVertex(vertices[15].get());
    tiles[2]->addNeighbouringVertex(vertices[16].get());

    tiles[3]->addNeighbouringVertex(vertices[6].get());
    tiles[3]->addNeighbouringVertex(vertices[7].get());
    tiles[3]->addNeighbouringVertex(vertices[12].get());
    tiles[3]->addNeighbouringVertex(vertices[13].get());
    tiles[3]->addNeighbouringVertex(vertices[18].get());
    tiles[3]->addNeighbouringVertex(vertices[19].get());

    tiles[4]->addNeighbouringVertex(vertices[8].get());
    tiles[4]->addNeighbouringVertex(vertices[9].get());
    tiles[4]->addNeighbouringVertex(vertices[14].get());
    tiles[4]->addNeighbouringVertex(vertices[15].get());
    tiles[4]->addNeighbouringVertex(vertices[20].get());
    tiles[4]->addNeighbouringVertex(vertices[21].get());

    tiles[5]->addNeighbouringVertex(vertices[10].get());
    tiles[5]->addNeighbouringVertex(vertices[11].get());
    tiles[5]->addNeighbouringVertex(vertices[16].get());
    tiles[5]->addNeighbouringVertex(vertices[17].get());
    tiles[5]->addNeighbouringVertex(vertices[22].get());
    tiles[5]->addNeighbouringVertex(vertices[23].get());

    tiles[6]->addNeighbouringVertex(vertices[13].get());
    tiles[6]->addNeighbouringVertex(vertices[14].get());
    tiles[6]->addNeighbouringVertex(vertices[19].get());
    tiles[6]->addNeighbouringVertex(vertices[20].get());
    tiles[6]->addNeighbouringVertex(vertices[25].get());
    tiles[6]->addNeighbouringVertex(vertices[26].get());

    tiles[7]->addNeighbouringVertex(vertices[15].get());
    tiles[7]->addNeighbouringVertex(vertices[16].get());
    tiles[7]->addNeighbouringVertex(vertices[21].get());
    tiles[7]->addNeighbouringVertex(vertices[22].get());
    tiles[7]->addNeighbouringVertex(vertices[27].get());
    tiles[7]->addNeighbouringVertex(vertices[28].get());

    tiles[8]->addNeighbouringVertex(vertices[18].get());
    tiles[8]->addNeighbouringVertex(vertices[19].get());
    tiles[8]->addNeighbouringVertex(vertices[24].get());
    tiles[8]->addNeighbouringVertex(vertices[25].get());
    tiles[8]->addNeighbouringVertex(vertices[30].get());
    tiles[8]->addNeighbouringVertex(vertices[31].get());

    tiles[9]->addNeighbouringVertex(vertices[20].get());
    tiles[9]->addNeighbouringVertex(vertices[21].get());
    tiles[9]->addNeighbouringVertex(vertices[26].get());
    tiles[9]->addNeighbouringVertex(vertices[27].get());
    tiles[9]->addNeighbouringVertex(vertices[32].get());
    tiles[9]->addNeighbouringVertex(vertices[33].get());

    tiles[10]->addNeighbouringVertex(vertices[22].get());
    tiles[10]->addNeighbouringVertex(vertices[23].get());
    tiles[10]->addNeighbouringVertex(vertices[28].get());
    tiles[10]->addNeighbouringVertex(vertices[29].get());
    tiles[10]->addNeighbouringVertex(vertices[34].get());
    tiles[10]->addNeighbouringVertex(vertices[35].get());

    tiles[11]->addNeighbouringVertex(vertices[25].get());
    tiles[11]->addNeighbouringVertex(vertices[26].get());
    tiles[11]->addNeighbouringVertex(vertices[31].get());
    tiles[11]->addNeighbouringVertex(vertices[32].get());
    tiles[11]->addNeighbouringVertex(vertices[37].get());
    tiles[11]->addNeighbouringVertex(vertices[38].get());

    tiles[12]->addNeighbouringVertex(vertices[27].get());
    tiles[12]->addNeighbouringVertex(vertices[28].get());
    tiles[12]->addNeighbouringVertex(vertices[33].get());
    tiles[12]->addNeighbouringVertex(vertices[34].get());
    tiles[12]->addNeighbouringVertex(vertices[39].get());
    tiles[12]->addNeighbouringVertex(vertices[40].get());

    tiles[13]->addNeighbouringVertex(vertices[30].get());
    tiles[13]->addNeighbouringVertex(vertices[31].get());
    tiles[13]->addNeighbouringVertex(vertices[36].get());
    tiles[13]->addNeighbouringVertex(vertices[37].get());
    tiles[13]->addNeighbouringVertex(vertices[42].get());
    tiles[13]->addNeighbouringVertex(vertices[43].get());

    tiles[14]->addNeighbouringVertex(vertices[32].get());
    tiles[14]->addNeighbouringVertex(vertices[33].get());
    tiles[14]->addNeighbouringVertex(vertices[38].get());
    tiles[14]->addNeighbouringVertex(vertices[39].get());
    tiles[14]->addNeighbouringVertex(vertices[44].get());
    tiles[14]->addNeighbouringVertex(vertices[45].get());

    tiles[15]->addNeighbouringVertex(vertices[34].get());
    tiles[15]->addNeighbouringVertex(vertices[35].get());
    tiles[15]->addNeighbouringVertex(vertices[40].get());
    tiles[15]->addNeighbouringVertex(vertices[41].get());
    tiles[15]->addNeighbouringVertex(vertices[46].get());
    tiles[15]->addNeighbouringVertex(vertices[47].get());

    tiles[16]->addNeighbouringVertex(vertices[37].get());
    tiles[16]->addNeighbouringVertex(vertices[38].get());
    tiles[16]->addNeighbouringVertex(vertices[43].get());
    tiles[16]->addNeighbouringVertex(vertices[44].get());
    tiles[16]->addNeighbouringVertex(vertices[48].get());
    tiles[16]->addNeighbouringVertex(vertices[49].get());

    tiles[17]->addNeighbouringVertex(vertices[39].get());
    tiles[17]->addNeighbouringVertex(vertices[40].get());
    tiles[17]->addNeighbouringVertex(vertices[45].get());
    tiles[17]->addNeighbouringVertex(vertices[46].get());
    tiles[17]->addNeighbouringVertex(vertices[50].get());
    tiles[17]->addNeighbouringVertex(vertices[51].get());

    tiles[18]->addNeighbouringVertex(vertices[44].get());
    tiles[18]->addNeighbouringVertex(vertices[45].get());
    tiles[18]->addNeighbouringVertex(vertices[49].get());
    tiles[18]->addNeighbouringVertex(vertices[50].get());
    tiles[18]->addNeighbouringVertex(vertices[52].get());
    tiles[18]->addNeighbouringVertex(vertices[53].get());
}
