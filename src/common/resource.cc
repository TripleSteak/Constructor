#include "resource.h"
#include <algorithm>

// "PARK" is considered an invalid resource for input purposes, since the Builder will never have any reason to input "PARK."
std::istream& operator>> (std::istream& in, Resource& resource) {
    std::string str;
    in >> str;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    if(str == "BRICK") { resource = BRICK; }
    else if(str == "ENERGY") { resource = ENERGY; }
    else if(str == "GLASS") { resource = GLASS; }
    else if(str == "HEAT") { resource = HEAT; }
    else if(str == "WIFI") { resource = WIFI; }
    else { throw std::invalid_argument("Received invalid Resource from input!"); }

    return in;
}

// Output operator overload is needed, as C++ prints enums as integers by default
std::ostream& operator<< (std::ostream& out, const Resource resource) {
    switch(resource) {
        case BRICK:
            out << "BRICK";
            break;
        case ENERGY:
            out << "ENERGY";
            break;
        case GLASS:
            out << "GLASS";
            break;
        case HEAT:
            out << "HEAT";
            break;
        case PARK:
            out << "PARK";
            break;
        case WIFI:
            out << "WIFI";
            break;
    }

    return out;
}
