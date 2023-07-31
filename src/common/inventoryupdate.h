#ifndef INVENTORYUPDATE_H
#define INVENTORYUPDATE_H

#include "resource.h"
#include <unordered_map>

struct BuilderInventoryUpdate {
    std::unordered_map<Resource, int> b1;
    std::unordered_map<Resource, int> b2;
    std::unordered_map<Resource, int> b3;
    std::unordered_map<Resource, int> b4;
    // Default constructor creates entry for each resource with value 0
    BuilderInventoryUpdate() {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            b1[resource] = 0;
            b2[resource] = 0;
            b3[resource] = 0;
            b4[resource] = 0;
        }
    }
    // Returns true if any builder gained a non-zero amount of any resource
    bool changed() {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            if (b1[resource] != 0 || b2[resource] != 0 || b3[resource] != 0 || b4[resource] != 0) {
                return true;
            }
        }
        return false;
    }
    // Overloaded subscript operator
    std::unordered_map<Resource, int>& operator[](int i) {
        if (i == 1) {
            return b1;
        }
        else if (i == 2) {
            return b2;
        }
        else if (i == 3) {
            return b3;
        }
        else {
            return b4;
        }
    }
    // Overloaded += operator
    BuilderInventoryUpdate& operator+=(const BuilderInventoryUpdate& rhs) {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            b1[resource] += rhs.b1.at(resource);
            b2[resource] += rhs.b2.at(resource);
            b3[resource] += rhs.b3.at(resource);
            b4[resource] += rhs.b4.at(resource);
        }
        return *this;
    }
};

#endif
