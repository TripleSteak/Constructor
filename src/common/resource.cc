#include "resource.h"
#include <algorithm>

// Converts string to a Resource enum
Resource resourceFromInt(int input) {
    switch (input) {
        case 0:
            return BRICK;
        case 1:
            return ENERGY;
        case 2:
            return GLASS;
        case 3:
            return HEAT;
        case 4:
            return WIFI;
        case 5:
            return PARK;
    }
    // Should never run
    throw std::invalid_argument("Received invalid Resource int from input!");
}

// Converts a Resource enum to a string
std::string resourceToString(Resource resource) {
    switch (resource) {
        case BRICK:
            return "BRICK";
        case ENERGY:
            return "ENERGY";
        case GLASS:
            return "GLASS";
        case HEAT:
            return "HEAT";
        case PARK:
            return "PARK";
        case WIFI:
            return "WIFI";
    }
    // Should never run
    throw std::invalid_argument("Error converting resource to string!");
}

// "PARK" is considered an invalid resource for input purposes, since the Builder will never have any reason to input "PARK."
std::istream& operator>>(std::istream& in, Resource& resource) {
    std::string str;
    in >> str;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    if (str == "BRICK") {
        resource = BRICK;
    }
    else if (str == "ENERGY") {
        resource = ENERGY;
    }
    else if (str == "GLASS") {
        resource = GLASS;
    }
    else if (str == "HEAT") {
        resource = HEAT;
    }
    else if (str == "WIFI") {
        resource = WIFI;
    }
    else {
        throw std::invalid_argument("Received invalid Resource from input!");
    }

    return in;
}

// Output operator overload is needed, as C++ prints enums as integers by default
std::ostream& operator<<(std::ostream& out, const Resource resource) {
    switch (resource) {
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
