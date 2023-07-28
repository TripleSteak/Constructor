#include "board.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "../game/builder.h"

const int NUM_TILES = 19;
const int NUM_EDGES = 72;
const int NUM_VERTICES = 54;

Board::Board() {}

Board::~Board() {
    for (auto tile : tiles) {
        delete tile;
    }
    for (auto edge : edges) {
        delete edge;
    }
    for (auto vertex : vertices) {
        delete vertex;
    }

    tiles.clear();
    edges.clear();
    vertices.clear();
}

AbstractTile* Board::getTile(int tileNumber) const {
    return tiles.at(tileNumber);
}

Vertex* Board::getVertex(int vertexNumber) const {
    return vertices.at(vertexNumber);
}

Edge* Board::getEdge(int edgeNumber) const {
    return edges.at(edgeNumber);
}

void Board::initBoard(std::vector<TileInitData> tileInitData) {
    for (int i = 0; i < NUM_TILES; i++) {
        tiles.push_back(new Tile(i, tileInitData.at(i).tileValue, tileInitData.at(i).resource));
        // TODO: If tileInitData.at(i) is a PARK, set the tile to geeseTile
    }

    for (int i = 0; i < NUM_EDGES; i++) {
        edges.push_back(new Edge(i));
    }
    for (int i = 0; i < NUM_VERTICES; i++) {
        vertices.push_back(new Vertex(i));
    }
}

bool Board::buildRoad (const Builder &builder, int edgeNumber, std::ostream &out) {
    Edge *edge = getEdge(edgeNumber);

    //check if can build road on edge
    if(!edge->canBuildRoad(builder.getBuilderNumber())) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    //check if builder has resources to build road
    std::shared_ptr<Road> road = builder.tryBuildRoad(*edge);

    if(road != nullptr) {
        edge->buildRoad(road);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}

bool Board::buildResidence(const Builder &builder, int vertexNumber, std::ostream &out) {
    Vertex *vertex = getVertex(vertexNumber);

    //check if can build residence on vertex
    if(!vertex->canBuildResidence(builder.getBuilderNumber())) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    //check if builder has resources to build residence
    std::shared_ptr<Residence> residence = builder.tryBuildResidence(*vertex);

    if(residence != nullptr) {
        vertex->buildResidence(residence);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}       

bool Board::buildInitialResidence(const Builder &builder, int vertexNumber, std::ostream &out) {
    Vertex *vertex = getVertex(vertexNumber);

    //check if can build residence on vertex
    if(!vertex->canBuildInitialResidence()) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    std::shared_ptr<Residence> residence = builder.tryBuildInitialResidence(*vertex); 
    vertex->buildResidence(residence);
    return true;
}

bool Board::upgradeResidence(const Builder &builder, int vertexNumber, std::ostream &out) {
    Vertex *vertex = getVertex(vertexNumber);

    //check if can upgrade residence on vertex
    if(!vertex->canUpgradeResidence(builder.getBuilderNumber())) {
        out << "You cannot build here." << std::endl;
        return false;
    }

    //check if builder has resources to upgrade residence
    std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(*vertex);

    if(residence != nullptr) {
        vertex->upgradeResidence(residence);
        return true;
    }

    out << "You do not have enough resources." << std::endl;
    return false;
}
