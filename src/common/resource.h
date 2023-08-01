#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

enum Resource { BRICK, ENERGY, GLASS, HEAT, WIFI, PARK };

std::string resourceToString(Resource);
Resource resourceFromString(std::string);

std::istream& operator>>(std::istream&, Resource&);
std::ostream& operator<<(std::ostream&, const Resource);

#endif
