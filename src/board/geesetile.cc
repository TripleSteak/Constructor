#include "geesetile.h"
#include "abstracttile.h"
#include "tile.h"

GeeseTile::GeeseTile(std::unique_ptr<Tile> tile) : AbstractTile(), tile{std::move(tile)} {}

GeeseTile::~GeeseTile() {}

std::unique_ptr<Tile> GeeseTile::removeGoose() {
    return std::move(tile);
}

void GeeseTile::addNeighbouringVertex(Vertex* v) {
    tile->addNeighbouringVertex(v);
}

int GeeseTile::getTileNumber() const {
    return tile->getTileNumber();
}

int GeeseTile::getTileValue() const {
    return tile->getTileValue();
}

Resource GeeseTile::getResource() const {
    return tile->getResource();
}

void GeeseTile::giveResourcesToBuilders() const const {}

bool GeeseTile::hasGeese() const {}
