#include "board.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"

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
