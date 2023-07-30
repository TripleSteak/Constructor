#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

enum Resource { BRICK, ENERGY, GLASS, HEAT, PARK, WIFI };

Resource resourceFromInt(int);
std::string resourceToString(Resource);

std::istream& operator>>(std::istream&, Resource&);
std::ostream& operator<<(std::ostream&, const Resource);

#endif
