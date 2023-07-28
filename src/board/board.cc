#include "board.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "../game/builder.h"   

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
    for (int i = 0; i < 19; i++) {
        tiles.push_back(new Tile(*this, i, tileInitData.at(i).tileValue,
                                 tileInitData.at(i).resource));
        // TODO: If tileInitData.at(i) is a PARK, set the tile to geeseTile
    }

    for (int i = 0; i < 72; i++) {
        edges.push_back(new Edge(*this, i));
    }
    for (int i = 0; i < 54; i++) {
        vertices.push_back(new Vertex(*this, i));
    }
}

void Board::buildRoad (const Builder &builder, int edgeNumber) {
    Edge *edge = getEdge(edgeNumber);
    //check if can build road on edge
    try { 
        edge->canBuildRoad(builder.getBuilderNumber()); 
    }
    catch(const std::logic_error& e){
        std::cout << "You cannot build here." << std::endl;
    }

    //check if builder has resources to build road 
    try { 
        std::shared_ptr<Road> road = builder.tryBuildRoad(*edge); 
        edge->buildRoad(road);
    }
    catch(const std::logic_error& e){
        std::cout << "You do not have enough resources." << std::endl;
    }
}

void Board::buildResidence(const Builder &builder, int vertexNumber) {
    Vertex *vertex = getVertex(vertexNumber);
    //check if can build residence on vertex
    try { 
        vertex->canBuildResidence(builder.getBuilderNumber()); 
    }
    catch(const std::logic_error& e){
        std::cout << "You cannot build here." << std::endl;
    }

    //check if builder has resources to build residence 
    try { 
        std::shared_ptr<Residence> residence = builder.tryBuildResidence(*vertex); 
        vertex->buildResidence(residence);
    }
    catch(const std::logic_error& e){
        std::cout << "You do not have enough resources." << std::endl;
    }
}       

void Board::buildInitialResidence(const Builder &builder, int vertexNumber) {
    Vertex *vertex = getVertex(vertexNumber);
    //check if can build residence on vertex
    try { 
        vertex->canBuildInitialResidence(); 
    }
    catch(const std::logic_error& e){
        std::cout << "You cannot build here." << std::endl;
    }

    std::shared_ptr<Residence> residence = builder.tryBuildInitialResidence(*vertex); 
    vertex->buildResidence(residence);
}

void Board::upgradeResidence(const Builder &builder, int vertexNumber) {
    Vertex *vertex = getVertex(vertexNumber);
    //check if can upgrade residence on vertex
    try { 
        vertex->canUpgradeResidence(builder.getBuilderNumber()); 
    }
    catch(const std::logic_error& e){
        std::cout << "You cannot upgrade here." << std::endl;
    }

    //check if builder has resources to upgrade residence 
    try { 
        std::shared_ptr<Residence> residence = builder.tryUpgradeResidence(*vertex); 
        vertex->upgradeResidence(residence);
    }
    catch(const std::logic_error& e){
        std::cout << "You do not have enough resources." << std::endl;
    }
}

