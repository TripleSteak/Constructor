#include "resource.h"
#include <algorithm>
#include <vector>

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
        case WIFI:
            return "WIFI";
        case PARK:
            return "PARK";
    }

    // Should never run
    throw std::invalid_argument("Error converting resource to string!");
}

// Converts a string to a Resource enum
Resource resourceFromString(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    if (str == "BRICK") {
        return BRICK;
    }
    else if (str == "ENERGY") {
        return ENERGY;
    }
    else if (str == "GLASS") {
        return GLASS;
    }
    else if (str == "HEAT") {
        return HEAT;
    }
    else if (str == "WIFI") {
        return WIFI;
    }
    else if (str == "PARK") {
        return PARK;
    }

    throw std::invalid_argument("Error converting string to resource!");
}

std::istream& operator>>(std::istream& in, Resource& resource) {
    unsigned int resourceInt;
    if (!(in >> resourceInt)) {
        return in;
    }
    if (resourceInt > 5) {
        throw std::invalid_argument("Invalid resource input!");
    }
    resource = static_cast<Resource>(resourceInt);

    return in;
}

// Output operator overload is needed, as C++ prints enums as integers by default
std::ostream& operator<<(std::ostream& out, const Resource resource) {
    out << resourceToString(resource);
    return out;
}
