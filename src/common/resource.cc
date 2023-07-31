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
        case PARK:
            return "PARK";
        case WIFI:
            return "WIFI";
    }

    // Should never run
    throw std::invalid_argument("Error converting resource to string!");
}

std::istream& operator>>(std::istream& in, Resource& resource) {
    std::string str;
    in >> str;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    // "PARK" is not considered a valid resource for input purposes, since the Builder will never have any reason to input "PARK."
    std::vector<Resource> possibleResources = { BRICK, ENERGY, GLASS, HEAT, WIFI };
    bool isPossibleResource = false;

    for(auto& possibleResource : possibleResources) {
        if(resourceToString(possibleResource) == str) {
	    resource = possibleResource;
	    isPossibleResource = true;
	}
    }

    if(!isPossibleResource) {
        throw std::invalid_argument("Received invalid Resource from input!");
    }

    return in;
}

// Output operator overload is needed, as C++ prints enums as integers by default
std::ostream& operator<<(std::ostream& out, const Resource resource) {
    out << resourceToString(resource);
    return out;
}
