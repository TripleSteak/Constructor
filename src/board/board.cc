#include "board.h"
#include "../game/builder.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"

const int NUM_TILES = 19;
const int NUM_EDGES = 72;
const int NUM_VERTICES = 54;

Board::Board(std::vector<TileInitData> tileInitData) {
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
    setupVertices();
    setupEdges();
    setupTiles();
}

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

bool Board::buildRoad(Builder& builder, int edgeNumber, std::ostream& out) {
    Edge* edge = getEdge(edgeNumber);

    // check if can build road on edge
    if (!edge->canBuildRoad(builder.getBuilderNumber())) {
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
    if (!vertex->canBuildResidence(builder.getBuilderNumber())) {
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
    if (!vertex->canUpgradeResidence(builder.getBuilderNumber())) {
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

void Board::setupVertices() {
    vertices[0]->addNeighbouringEdge(edges[0]);
    vertices[0]->addNeighbouringEdge(edges[1]);
    vertices[0]->addNeighbouringTile(tiles[0]);

    vertices[1]->addNeighbouringEdge(edges[0]);
    vertices[1]->addNeighbouringEdge(edges[2]);
    vertices[1]->addNeighbouringTile(tiles[0]);

    vertices[2]->addNeighbouringEdge(edges[3]);
    vertices[2]->addNeighbouringEdge(edges[5]);
    vertices[2]->addNeighbouringTile(tiles[1]);

    vertices[3]->addNeighbouringEdge(edges[1]);
    vertices[3]->addNeighbouringEdge(edges[3]);
    vertices[3]->addNeighbouringEdge(edges[6]);
    vertices[3]->addNeighbouringTile(tiles[0]);
    vertices[3]->addNeighbouringTile(tiles[1]);

    vertices[4]->addNeighbouringEdge(edges[2]);
    vertices[4]->addNeighbouringEdge(edges[4]);
    vertices[4]->addNeighbouringEdge(edges[7]);
    vertices[4]->addNeighbouringTile(tiles[0]);
    vertices[4]->addNeighbouringTile(tiles[2]);

    vertices[5]->addNeighbouringEdge(edges[4]);
    vertices[5]->addNeighbouringEdge(edges[8]);
    vertices[5]->addNeighbouringTile(tiles[2]);

    vertices[6]->addNeighbouringEdge(edges[9]);
    vertices[6]->addNeighbouringEdge(edges[12]);
    vertices[6]->addNeighbouringTile(tiles[3]);

    vertices[7]->addNeighbouringEdge(edges[5]);
    vertices[7]->addNeighbouringEdge(edges[9]);
    vertices[7]->addNeighbouringEdge(edges[13]);
    vertices[7]->addNeighbouringTile(tiles[1]);
    vertices[7]->addNeighbouringTile(tiles[3]);

    vertices[8]->addNeighbouringEdge(edges[6]);
    vertices[8]->addNeighbouringEdge(edges[10]);
    vertices[8]->addNeighbouringEdge(edges[14]);
    vertices[8]->addNeighbouringTile(tiles[0]);
    vertices[8]->addNeighbouringTile(tiles[1]);
    vertices[8]->addNeighbouringTile(tiles[4]);

    vertices[9]->addNeighbouringEdge(edges[7]);
    vertices[9]->addNeighbouringEdge(edges[10]);
    vertices[9]->addNeighbouringEdge(edges[15]);
    vertices[9]->addNeighbouringTile(tiles[0]);
    vertices[9]->addNeighbouringTile(tiles[2]);
    vertices[9]->addNeighbouringTile(tiles[4]);

    vertices[10]->addNeighbouringEdge(edges[8]);
    vertices[10]->addNeighbouringEdge(edges[11]);
    vertices[10]->addNeighbouringEdge(edges[16]);
    vertices[10]->addNeighbouringTile(tiles[2]);
    vertices[10]->addNeighbouringTile(tiles[5]);

    vertices[11]->addNeighbouringEdge(edges[11]);
    vertices[11]->addNeighbouringEdge(edges[17]);
    vertices[11]->addNeighbouringTile(tiles[5]);

    vertices[12]->addNeighbouringEdge(edges[12]);
    vertices[12]->addNeighbouringEdge(edges[20]);
    vertices[12]->addNeighbouringTile(tiles[3]);

    vertices[13]->addNeighbouringEdge(edges[13]);
    vertices[13]->addNeighbouringEdge(edges[18]);
    vertices[13]->addNeighbouringEdge(edges[21]);
    vertices[13]->addNeighbouringTile(tiles[1]);
    vertices[13]->addNeighbouringTile(tiles[3]);
    vertices[13]->addNeighbouringTile(tiles[6]);

    vertices[14]->addNeighbouringEdge(edges[14]);
    vertices[14]->addNeighbouringEdge(edges[18]);
    vertices[14]->addNeighbouringEdge(edges[22]);
    vertices[14]->addNeighbouringTile(tiles[1]);
    vertices[14]->addNeighbouringTile(tiles[4]);
    vertices[14]->addNeighbouringTile(tiles[6]);

    vertices[15]->addNeighbouringEdge(edges[15]);
    vertices[15]->addNeighbouringEdge(edges[19]);
    vertices[15]->addNeighbouringEdge(edges[23]);
    vertices[15]->addNeighbouringTile(tiles[2]);
    vertices[15]->addNeighbouringTile(tiles[4]);
    vertices[15]->addNeighbouringTile(tiles[7]);

    vertices[16]->addNeighbouringEdge(edges[16]);
    vertices[16]->addNeighbouringEdge(edges[19]);
    vertices[16]->addNeighbouringEdge(edges[24]);
    vertices[16]->addNeighbouringTile(tiles[2]);
    vertices[16]->addNeighbouringTile(tiles[5]);
    vertices[16]->addNeighbouringTile(tiles[7]);

    vertices[17]->addNeighbouringEdge(edges[17]);
    vertices[17]->addNeighbouringEdge(edges[25]);
    vertices[17]->addNeighbouringTile(tiles[5]);

    vertices[18]->addNeighbouringEdge(edges[20]);
    vertices[18]->addNeighbouringEdge(edges[26]);
    vertices[18]->addNeighbouringEdge(edges[29]);
    vertices[18]->addNeighbouringTile(tiles[3]);
    vertices[18]->addNeighbouringTile(tiles[8]);

    vertices[19]->addNeighbouringEdge(edges[21]);
    vertices[19]->addNeighbouringEdge(edges[26]);
    vertices[19]->addNeighbouringEdge(edges[30]);
    vertices[19]->addNeighbouringTile(tiles[3]);
    vertices[19]->addNeighbouringTile(tiles[6]);
    vertices[19]->addNeighbouringTile(tiles[8]);

    vertices[20]->addNeighbouringEdge(edges[22]);
    vertices[20]->addNeighbouringEdge(edges[27]);
    vertices[20]->addNeighbouringEdge(edges[31]);
    vertices[20]->addNeighbouringTile(tiles[4]);
    vertices[20]->addNeighbouringTile(tiles[6]);
    vertices[20]->addNeighbouringTile(tiles[9]);

    vertices[21]->addNeighbouringEdge(edges[23]);
    vertices[21]->addNeighbouringEdge(edges[27]);
    vertices[21]->addNeighbouringEdge(edges[32]);
    vertices[21]->addNeighbouringTile(tiles[4]);
    vertices[21]->addNeighbouringTile(tiles[7]);
    vertices[21]->addNeighbouringTile(tiles[9]);

    vertices[22]->addNeighbouringEdge(edges[24]);
    vertices[22]->addNeighbouringEdge(edges[28]);
    vertices[22]->addNeighbouringEdge(edges[33]);
    vertices[22]->addNeighbouringTile(tiles[5]);
    vertices[22]->addNeighbouringTile(tiles[7]);
    vertices[22]->addNeighbouringTile(tiles[10]);

    vertices[23]->addNeighbouringEdge(edges[25]);
    vertices[23]->addNeighbouringEdge(edges[28]);
    vertices[23]->addNeighbouringEdge(edges[34]);
    vertices[23]->addNeighbouringTile(tiles[5]);
    vertices[23]->addNeighbouringTile(tiles[10]);

    vertices[24]->addNeighbouringEdge(edges[29]);
    vertices[24]->addNeighbouringEdge(edges[37]);
    vertices[24]->addNeighbouringTile(tiles[8]);

    vertices[25]->addNeighbouringEdge(edges[30]);
    vertices[25]->addNeighbouringEdge(edges[35]);
    vertices[25]->addNeighbouringEdge(edges[38]);
    vertices[25]->addNeighbouringTile(tiles[6]);
    vertices[25]->addNeighbouringTile(tiles[8]);
    vertices[25]->addNeighbouringTile(tiles[11]);

    vertices[26]->addNeighbouringEdge(edges[31]);
    vertices[26]->addNeighbouringEdge(edges[35]);
    vertices[26]->addNeighbouringEdge(edges[39]);
    vertices[26]->addNeighbouringTile(tiles[6]);
    vertices[26]->addNeighbouringTile(tiles[9]);
    vertices[26]->addNeighbouringTile(tiles[11]);

    vertices[27]->addNeighbouringEdge(edges[32]);
    vertices[27]->addNeighbouringEdge(edges[36]);
    vertices[27]->addNeighbouringEdge(edges[40]);
    vertices[27]->addNeighbouringTile(tiles[7]);
    vertices[27]->addNeighbouringTile(tiles[9]);
    vertices[27]->addNeighbouringTile(tiles[12]);

    vertices[28]->addNeighbouringEdge(edges[33]);
    vertices[28]->addNeighbouringEdge(edges[36]);
    vertices[28]->addNeighbouringEdge(edges[41]);
    vertices[28]->addNeighbouringTile(tiles[7]);
    vertices[28]->addNeighbouringTile(tiles[10]);
    vertices[28]->addNeighbouringTile(tiles[12]);

    vertices[29]->addNeighbouringEdge(edges[34]);
    vertices[29]->addNeighbouringEdge(edges[42]);
    vertices[29]->addNeighbouringTile(tiles[10]);

    vertices[30]->addNeighbouringEdge(edges[37]);
    vertices[30]->addNeighbouringEdge(edges[43]);
    vertices[30]->addNeighbouringEdge(edges[46]);
    vertices[30]->addNeighbouringTile(tiles[8]);
    vertices[30]->addNeighbouringTile(tiles[13]);

    vertices[31]->addNeighbouringEdge(edges[38]);
    vertices[31]->addNeighbouringEdge(edges[43]);
    vertices[31]->addNeighbouringEdge(edges[47]);
    vertices[31]->addNeighbouringTile(tiles[8]);
    vertices[31]->addNeighbouringTile(tiles[11]);
    vertices[31]->addNeighbouringTile(tiles[13]);

    vertices[32]->addNeighbouringEdge(edges[39]);
    vertices[32]->addNeighbouringEdge(edges[44]);
    vertices[32]->addNeighbouringEdge(edges[48]);
    vertices[32]->addNeighbouringTile(tiles[9]);
    vertices[32]->addNeighbouringTile(tiles[11]);
    vertices[32]->addNeighbouringTile(tiles[14]);

    vertices[33]->addNeighbouringEdge(edges[40]);
    vertices[33]->addNeighbouringEdge(edges[44]);
    vertices[33]->addNeighbouringEdge(edges[49]);
    vertices[33]->addNeighbouringTile(tiles[9]);
    vertices[33]->addNeighbouringTile(tiles[12]);
    vertices[33]->addNeighbouringTile(tiles[14]);

    vertices[34]->addNeighbouringEdge(edges[41]);
    vertices[34]->addNeighbouringEdge(edges[45]);
    vertices[34]->addNeighbouringEdge(edges[50]);
    vertices[34]->addNeighbouringTile(tiles[10]);
    vertices[34]->addNeighbouringTile(tiles[12]);
    vertices[34]->addNeighbouringTile(tiles[15]);

    vertices[35]->addNeighbouringEdge(edges[42]);
    vertices[35]->addNeighbouringEdge(edges[45]);
    vertices[35]->addNeighbouringEdge(edges[51]);
    vertices[35]->addNeighbouringTile(tiles[10]);
    vertices[35]->addNeighbouringTile(tiles[15]);

    vertices[36]->addNeighbouringEdge(edges[46]);
    vertices[36]->addNeighbouringEdge(edges[54]);
    vertices[36]->addNeighbouringTile(tiles[13]);

    vertices[37]->addNeighbouringEdge(edges[47]);
    vertices[37]->addNeighbouringEdge(edges[52]);
    vertices[37]->addNeighbouringEdge(edges[55]);
    vertices[37]->addNeighbouringTile(tiles[11]);
    vertices[37]->addNeighbouringTile(tiles[13]);
    vertices[37]->addNeighbouringTile(tiles[16]);

    vertices[38]->addNeighbouringEdge(edges[48]);
    vertices[38]->addNeighbouringEdge(edges[52]);
    vertices[38]->addNeighbouringEdge(edges[56]);
    vertices[38]->addNeighbouringTile(tiles[11]);
    vertices[38]->addNeighbouringTile(tiles[14]);
    vertices[38]->addNeighbouringTile(tiles[16]);

    vertices[39]->addNeighbouringEdge(edges[49]);
    vertices[39]->addNeighbouringEdge(edges[53]);
    vertices[39]->addNeighbouringEdge(edges[57]);
    vertices[39]->addNeighbouringTile(tiles[12]);
    vertices[39]->addNeighbouringTile(tiles[14]);
    vertices[39]->addNeighbouringTile(tiles[17]);

    vertices[40]->addNeighbouringEdge(edges[50]);
    vertices[40]->addNeighbouringEdge(edges[53]);
    vertices[40]->addNeighbouringEdge(edges[58]);
    vertices[40]->addNeighbouringTile(tiles[12]);
    vertices[40]->addNeighbouringTile(tiles[15]);
    vertices[40]->addNeighbouringTile(tiles[17]);

    vertices[41]->addNeighbouringEdge(edges[51]);
    vertices[41]->addNeighbouringEdge(edges[59]);
    vertices[41]->addNeighbouringTile(tiles[15]);

    vertices[42]->addNeighbouringEdge(edges[54]);
    vertices[42]->addNeighbouringEdge(edges[60]);
    vertices[42]->addNeighbouringTile(tiles[13]);

    vertices[43]->addNeighbouringEdge(edges[55]);
    vertices[43]->addNeighbouringEdge(edges[60]);
    vertices[43]->addNeighbouringEdge(edges[63]);
    vertices[43]->addNeighbouringTile(tiles[13]);
    vertices[43]->addNeighbouringTile(tiles[16]);

    vertices[44]->addNeighbouringEdge(edges[56]);
    vertices[44]->addNeighbouringEdge(edges[61]);
    vertices[44]->addNeighbouringEdge(edges[64]);
    vertices[44]->addNeighbouringTile(tiles[14]);
    vertices[44]->addNeighbouringTile(tiles[16]);
    vertices[44]->addNeighbouringTile(tiles[18]);

    vertices[45]->addNeighbouringEdge(edges[57]);
    vertices[45]->addNeighbouringEdge(edges[61]);
    vertices[45]->addNeighbouringEdge(edges[65]);
    vertices[45]->addNeighbouringTile(tiles[14]);
    vertices[45]->addNeighbouringTile(tiles[17]);
    vertices[45]->addNeighbouringTile(tiles[18]);

    vertices[46]->addNeighbouringEdge(edges[58]);
    vertices[46]->addNeighbouringEdge(edges[62]);
    vertices[46]->addNeighbouringEdge(edges[66]);
    vertices[46]->addNeighbouringTile(tiles[15]);
    vertices[46]->addNeighbouringTile(tiles[17]);

    vertices[47]->addNeighbouringEdge(edges[59]);
    vertices[47]->addNeighbouringEdge(edges[62]);
    vertices[47]->addNeighbouringTile(tiles[15]);

    vertices[48]->addNeighbouringEdge(edges[63]);
    vertices[48]->addNeighbouringEdge(edges[67]);
    vertices[48]->addNeighbouringTile(tiles[16]);

    vertices[49]->addNeighbouringEdge(edges[64]);
    vertices[49]->addNeighbouringEdge(edges[67]);
    vertices[49]->addNeighbouringEdge(edges[69]);
    vertices[49]->addNeighbouringTile(tiles[16]);
    vertices[49]->addNeighbouringTile(tiles[18]);

    vertices[50]->addNeighbouringEdge(edges[65]);
    vertices[50]->addNeighbouringEdge(edges[68]);
    vertices[50]->addNeighbouringEdge(edges[70]);
    vertices[50]->addNeighbouringTile(tiles[17]);
    vertices[50]->addNeighbouringTile(tiles[18]);

    vertices[51]->addNeighbouringEdge(edges[66]);
    vertices[51]->addNeighbouringEdge(edges[68]);
    vertices[51]->addNeighbouringTile(tiles[17]);

    vertices[52]->addNeighbouringEdge(edges[69]);
    vertices[52]->addNeighbouringEdge(edges[71]);
    vertices[52]->addNeighbouringTile(tiles[18]);

    vertices[53]->addNeighbouringEdge(edges[70]);
    vertices[53]->addNeighbouringEdge(edges[71]);
    vertices[53]->addNeighbouringTile(tiles[18]);
}

void Board::setupEdges() {
    edges[0]->addNeighbouringVertex(vertices[0]);
    edges[0]->addNeighbouringVertex(vertices[1]);

    edges[1]->addNeighbouringVertex(vertices[0]);
    edges[1]->addNeighbouringVertex(vertices[3]);

    edges[2]->addNeighbouringVertex(vertices[1]);
    edges[2]->addNeighbouringVertex(vertices[4]);

    edges[3]->addNeighbouringVertex(vertices[2]);
    edges[3]->addNeighbouringVertex(vertices[3]);

    edges[4]->addNeighbouringVertex(vertices[4]);
    edges[4]->addNeighbouringVertex(vertices[5]);

    edges[5]->addNeighbouringVertex(vertices[2]);
    edges[5]->addNeighbouringVertex(vertices[7]);

    edges[6]->addNeighbouringVertex(vertices[3]);
    edges[6]->addNeighbouringVertex(vertices[8]);

    edges[7]->addNeighbouringVertex(vertices[4]);
    edges[7]->addNeighbouringVertex(vertices[9]);

    edges[8]->addNeighbouringVertex(vertices[5]);
    edges[8]->addNeighbouringVertex(vertices[10]);

    edges[9]->addNeighbouringVertex(vertices[6]);
    edges[9]->addNeighbouringVertex(vertices[7]);

    edges[10]->addNeighbouringVertex(vertices[8]);
    edges[10]->addNeighbouringVertex(vertices[9]);

    edges[11]->addNeighbouringVertex(vertices[10]);
    edges[11]->addNeighbouringVertex(vertices[11]);

    edges[12]->addNeighbouringVertex(vertices[6]);
    edges[12]->addNeighbouringVertex(vertices[12]);

    edges[13]->addNeighbouringVertex(vertices[7]);
    edges[13]->addNeighbouringVertex(vertices[13]);

    edges[14]->addNeighbouringVertex(vertices[8]);
    edges[14]->addNeighbouringVertex(vertices[14]);

    edges[15]->addNeighbouringVertex(vertices[9]);
    edges[15]->addNeighbouringVertex(vertices[15]);

    edges[16]->addNeighbouringVertex(vertices[10]);
    edges[16]->addNeighbouringVertex(vertices[16]);

    edges[17]->addNeighbouringVertex(vertices[11]);
    edges[17]->addNeighbouringVertex(vertices[17]);

    edges[18]->addNeighbouringVertex(vertices[13]);
    edges[18]->addNeighbouringVertex(vertices[14]);

    edges[19]->addNeighbouringVertex(vertices[15]);
    edges[19]->addNeighbouringVertex(vertices[16]);

    edges[20]->addNeighbouringVertex(vertices[12]);
    edges[20]->addNeighbouringVertex(vertices[18]);

    edges[21]->addNeighbouringVertex(vertices[13]);
    edges[21]->addNeighbouringVertex(vertices[19]);

    edges[22]->addNeighbouringVertex(vertices[14]);
    edges[22]->addNeighbouringVertex(vertices[20]);

    edges[23]->addNeighbouringVertex(vertices[15]);
    edges[23]->addNeighbouringVertex(vertices[21]);

    edges[24]->addNeighbouringVertex(vertices[16]);
    edges[24]->addNeighbouringVertex(vertices[22]);

    edges[25]->addNeighbouringVertex(vertices[17]);
    edges[25]->addNeighbouringVertex(vertices[23]);

    edges[26]->addNeighbouringVertex(vertices[18]);
    edges[26]->addNeighbouringVertex(vertices[19]);

    edges[27]->addNeighbouringVertex(vertices[20]);
    edges[27]->addNeighbouringVertex(vertices[21]);

    edges[28]->addNeighbouringVertex(vertices[22]);
    edges[28]->addNeighbouringVertex(vertices[23]);

    edges[29]->addNeighbouringVertex(vertices[18]);
    edges[29]->addNeighbouringVertex(vertices[24]);

    edges[30]->addNeighbouringVertex(vertices[19]);
    edges[30]->addNeighbouringVertex(vertices[25]);

    edges[31]->addNeighbouringVertex(vertices[20]);
    edges[31]->addNeighbouringVertex(vertices[26]);

    edges[32]->addNeighbouringVertex(vertices[21]);
    edges[32]->addNeighbouringVertex(vertices[27]);

    edges[33]->addNeighbouringVertex(vertices[22]);
    edges[33]->addNeighbouringVertex(vertices[28]);

    edges[34]->addNeighbouringVertex(vertices[23]);
    edges[34]->addNeighbouringVertex(vertices[29]);

    edges[35]->addNeighbouringVertex(vertices[25]);
    edges[35]->addNeighbouringVertex(vertices[26]);

    edges[36]->addNeighbouringVertex(vertices[27]);
    edges[36]->addNeighbouringVertex(vertices[28]);

    edges[37]->addNeighbouringVertex(vertices[24]);
    edges[37]->addNeighbouringVertex(vertices[30]);

    edges[38]->addNeighbouringVertex(vertices[25]);
    edges[38]->addNeighbouringVertex(vertices[31]);

    edges[39]->addNeighbouringVertex(vertices[26]);
    edges[39]->addNeighbouringVertex(vertices[32]);

    edges[40]->addNeighbouringVertex(vertices[27]);
    edges[40]->addNeighbouringVertex(vertices[33]);

    edges[41]->addNeighbouringVertex(vertices[28]);
    edges[41]->addNeighbouringVertex(vertices[34]);

    edges[42]->addNeighbouringVertex(vertices[29]);
    edges[42]->addNeighbouringVertex(vertices[35]);

    edges[43]->addNeighbouringVertex(vertices[30]);
    edges[43]->addNeighbouringVertex(vertices[31]);

    edges[44]->addNeighbouringVertex(vertices[32]);
    edges[44]->addNeighbouringVertex(vertices[33]);

    edges[45]->addNeighbouringVertex(vertices[34]);
    edges[45]->addNeighbouringVertex(vertices[35]);

    edges[46]->addNeighbouringVertex(vertices[30]);
    edges[46]->addNeighbouringVertex(vertices[36]);

    edges[47]->addNeighbouringVertex(vertices[31]);
    edges[47]->addNeighbouringVertex(vertices[37]);

    edges[48]->addNeighbouringVertex(vertices[32]);
    edges[48]->addNeighbouringVertex(vertices[38]);

    edges[49]->addNeighbouringVertex(vertices[33]);
    edges[49]->addNeighbouringVertex(vertices[39]);

    edges[50]->addNeighbouringVertex(vertices[34]);
    edges[50]->addNeighbouringVertex(vertices[40]);

    edges[51]->addNeighbouringVertex(vertices[35]);
    edges[51]->addNeighbouringVertex(vertices[41]);

    edges[52]->addNeighbouringVertex(vertices[37]);
    edges[52]->addNeighbouringVertex(vertices[38]);

    edges[53]->addNeighbouringVertex(vertices[39]);
    edges[53]->addNeighbouringVertex(vertices[40]);

    edges[54]->addNeighbouringVertex(vertices[36]);
    edges[54]->addNeighbouringVertex(vertices[42]);

    edges[55]->addNeighbouringVertex(vertices[37]);
    edges[55]->addNeighbouringVertex(vertices[43]);

    edges[56]->addNeighbouringVertex(vertices[38]);
    edges[56]->addNeighbouringVertex(vertices[44]);

    edges[57]->addNeighbouringVertex(vertices[39]);
    edges[57]->addNeighbouringVertex(vertices[45]);

    edges[58]->addNeighbouringVertex(vertices[40]);
    edges[58]->addNeighbouringVertex(vertices[46]);

    edges[59]->addNeighbouringVertex(vertices[41]);
    edges[59]->addNeighbouringVertex(vertices[47]);

    edges[60]->addNeighbouringVertex(vertices[42]);
    edges[60]->addNeighbouringVertex(vertices[43]);

    edges[61]->addNeighbouringVertex(vertices[44]);
    edges[61]->addNeighbouringVertex(vertices[45]);

    edges[62]->addNeighbouringVertex(vertices[46]);
    edges[62]->addNeighbouringVertex(vertices[47]);

    edges[63]->addNeighbouringVertex(vertices[43]);
    edges[63]->addNeighbouringVertex(vertices[48]);

    edges[64]->addNeighbouringVertex(vertices[44]);
    edges[64]->addNeighbouringVertex(vertices[49]);

    edges[65]->addNeighbouringVertex(vertices[45]);
    edges[65]->addNeighbouringVertex(vertices[50]);

    edges[66]->addNeighbouringVertex(vertices[46]);
    edges[66]->addNeighbouringVertex(vertices[51]);

    edges[67]->addNeighbouringVertex(vertices[48]);
    edges[67]->addNeighbouringVertex(vertices[49]);

    edges[68]->addNeighbouringVertex(vertices[50]);
    edges[68]->addNeighbouringVertex(vertices[51]);

    edges[69]->addNeighbouringVertex(vertices[49]);
    edges[69]->addNeighbouringVertex(vertices[52]);

    edges[70]->addNeighbouringVertex(vertices[50]);
    edges[70]->addNeighbouringVertex(vertices[53]);

    edges[71]->addNeighbouringVertex(vertices[52]);
    edges[71]->addNeighbouringVertex(vertices[53]);
}

void Board::setupTiles() {
    tiles[0]->addNeighbouringVertex(vertices[0]);
    tiles[0]->addNeighbouringVertex(vertices[1]);
    tiles[0]->addNeighbouringVertex(vertices[3]);
    tiles[0]->addNeighbouringVertex(vertices[4]);
    tiles[0]->addNeighbouringVertex(vertices[8]);
    tiles[0]->addNeighbouringVertex(vertices[9]);

    tiles[1]->addNeighbouringVertex(vertices[2]);
    tiles[1]->addNeighbouringVertex(vertices[3]);
    tiles[1]->addNeighbouringVertex(vertices[7]);
    tiles[1]->addNeighbouringVertex(vertices[8]);
    tiles[1]->addNeighbouringVertex(vertices[13]);
    tiles[1]->addNeighbouringVertex(vertices[14]);

    tiles[2]->addNeighbouringVertex(vertices[4]);
    tiles[2]->addNeighbouringVertex(vertices[5]);
    tiles[2]->addNeighbouringVertex(vertices[9]);
    tiles[2]->addNeighbouringVertex(vertices[10]);
    tiles[2]->addNeighbouringVertex(vertices[15]);
    tiles[2]->addNeighbouringVertex(vertices[16]);

    tiles[3]->addNeighbouringVertex(vertices[6]);
    tiles[3]->addNeighbouringVertex(vertices[7]);
    tiles[3]->addNeighbouringVertex(vertices[12]);
    tiles[3]->addNeighbouringVertex(vertices[13]);
    tiles[3]->addNeighbouringVertex(vertices[18]);
    tiles[3]->addNeighbouringVertex(vertices[19]);

    tiles[4]->addNeighbouringVertex(vertices[8]);
    tiles[4]->addNeighbouringVertex(vertices[9]);
    tiles[4]->addNeighbouringVertex(vertices[14]);
    tiles[4]->addNeighbouringVertex(vertices[15]);
    tiles[4]->addNeighbouringVertex(vertices[20]);
    tiles[4]->addNeighbouringVertex(vertices[21]);

    tiles[5]->addNeighbouringVertex(vertices[10]);
    tiles[5]->addNeighbouringVertex(vertices[11]);
    tiles[5]->addNeighbouringVertex(vertices[16]);
    tiles[5]->addNeighbouringVertex(vertices[17]);
    tiles[5]->addNeighbouringVertex(vertices[22]);
    tiles[5]->addNeighbouringVertex(vertices[23]);

    tiles[6]->addNeighbouringVertex(vertices[13]);
    tiles[6]->addNeighbouringVertex(vertices[14]);
    tiles[6]->addNeighbouringVertex(vertices[19]);
    tiles[6]->addNeighbouringVertex(vertices[20]);
    tiles[6]->addNeighbouringVertex(vertices[25]);
    tiles[6]->addNeighbouringVertex(vertices[26]);

    tiles[7]->addNeighbouringVertex(vertices[15]);
    tiles[7]->addNeighbouringVertex(vertices[16]);
    tiles[7]->addNeighbouringVertex(vertices[21]);
    tiles[7]->addNeighbouringVertex(vertices[22]);
    tiles[7]->addNeighbouringVertex(vertices[27]);
    tiles[7]->addNeighbouringVertex(vertices[28]);

    tiles[8]->addNeighbouringVertex(vertices[18]);
    tiles[8]->addNeighbouringVertex(vertices[19]);
    tiles[8]->addNeighbouringVertex(vertices[24]);
    tiles[8]->addNeighbouringVertex(vertices[25]);
    tiles[8]->addNeighbouringVertex(vertices[30]);
    tiles[8]->addNeighbouringVertex(vertices[31]);

    tiles[9]->addNeighbouringVertex(vertices[20]);
    tiles[9]->addNeighbouringVertex(vertices[21]);
    tiles[9]->addNeighbouringVertex(vertices[26]);
    tiles[9]->addNeighbouringVertex(vertices[27]);
    tiles[9]->addNeighbouringVertex(vertices[32]);
    tiles[9]->addNeighbouringVertex(vertices[33]);

    tiles[10]->addNeighbouringVertex(vertices[22]);
    tiles[10]->addNeighbouringVertex(vertices[23]);
    tiles[10]->addNeighbouringVertex(vertices[28]);
    tiles[10]->addNeighbouringVertex(vertices[29]);
    tiles[10]->addNeighbouringVertex(vertices[34]);
    tiles[10]->addNeighbouringVertex(vertices[35]);

    tiles[11]->addNeighbouringVertex(vertices[25]);
    tiles[11]->addNeighbouringVertex(vertices[26]);
    tiles[11]->addNeighbouringVertex(vertices[31]);
    tiles[11]->addNeighbouringVertex(vertices[32]);
    tiles[11]->addNeighbouringVertex(vertices[37]);
    tiles[11]->addNeighbouringVertex(vertices[38]);

    tiles[12]->addNeighbouringVertex(vertices[27]);
    tiles[12]->addNeighbouringVertex(vertices[28]);
    tiles[12]->addNeighbouringVertex(vertices[33]);
    tiles[12]->addNeighbouringVertex(vertices[34]);
    tiles[12]->addNeighbouringVertex(vertices[39]);
    tiles[12]->addNeighbouringVertex(vertices[40]);

    tiles[13]->addNeighbouringVertex(vertices[30]);
    tiles[13]->addNeighbouringVertex(vertices[31]);
    tiles[13]->addNeighbouringVertex(vertices[36]);
    tiles[13]->addNeighbouringVertex(vertices[37]);
    tiles[13]->addNeighbouringVertex(vertices[42]);
    tiles[13]->addNeighbouringVertex(vertices[43]);

    tiles[14]->addNeighbouringVertex(vertices[32]);
    tiles[14]->addNeighbouringVertex(vertices[33]);
    tiles[14]->addNeighbouringVertex(vertices[38]);
    tiles[14]->addNeighbouringVertex(vertices[39]);
    tiles[14]->addNeighbouringVertex(vertices[44]);
    tiles[14]->addNeighbouringVertex(vertices[45]);

    tiles[15]->addNeighbouringVertex(vertices[34]);
    tiles[15]->addNeighbouringVertex(vertices[35]);
    tiles[15]->addNeighbouringVertex(vertices[40]);
    tiles[15]->addNeighbouringVertex(vertices[41]);
    tiles[15]->addNeighbouringVertex(vertices[46]);
    tiles[15]->addNeighbouringVertex(vertices[47]);

    tiles[16]->addNeighbouringVertex(vertices[37]);
    tiles[16]->addNeighbouringVertex(vertices[38]);
    tiles[16]->addNeighbouringVertex(vertices[43]);
    tiles[16]->addNeighbouringVertex(vertices[44]);
    tiles[16]->addNeighbouringVertex(vertices[48]);
    tiles[16]->addNeighbouringVertex(vertices[49]);

    tiles[17]->addNeighbouringVertex(vertices[39]);
    tiles[17]->addNeighbouringVertex(vertices[40]);
    tiles[17]->addNeighbouringVertex(vertices[45]);
    tiles[17]->addNeighbouringVertex(vertices[46]);
    tiles[17]->addNeighbouringVertex(vertices[50]);
    tiles[17]->addNeighbouringVertex(vertices[51]);

    tiles[18]->addNeighbouringVertex(vertices[44]);
    tiles[18]->addNeighbouringVertex(vertices[45]);
    tiles[18]->addNeighbouringVertex(vertices[49]);
    tiles[18]->addNeighbouringVertex(vertices[50]);
    tiles[18]->addNeighbouringVertex(vertices[52]);
    tiles[18]->addNeighbouringVertex(vertices[53]);
}
