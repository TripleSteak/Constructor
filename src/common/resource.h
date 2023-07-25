#ifndef RESOURCE_H
#define RESOURCE_H

enum Resource { BRICK, ENERGY, GLASS, HEAT, PARK, WIFI };

std::istream& operator>> (std::istream&, Resource&);
std::ostream& operator<< (std::ostream&, Resource&);

#endif
