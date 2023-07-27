#include "vertex.h"
#include "../structures/residence.h"

Vertex::Vertex(int vertexNumber) : vertexNumber{vertexNumber}, residence{nullptr} {}
Vertex::~Vertex() { delete residence; }
