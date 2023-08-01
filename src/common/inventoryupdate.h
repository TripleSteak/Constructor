#ifndef INVENTORYUPDATE_H
#define INVENTORYUPDATE_H

#include "resource.h"
#include <unordered_map>

struct BuilderInventoryUpdate {
    std::unordered_map<Resource, int> builder1Inventory;
    std::unordered_map<Resource, int> builder2Inventory;
    std::unordered_map<Resource, int> builder3Inventory;
    std::unordered_map<Resource, int> builder4Inventory;

    // Default constructor creates entry for each resource with value 0
    BuilderInventoryUpdate() {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            builder1Inventory[resource] = 0;
            builder2Inventory[resource] = 0;
            builder3Inventory[resource] = 0;
            builder4Inventory[resource] = 0;
        }
    }

    // Returns true if any builder gained a non-zero amount of any resource
    bool changed() {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            if (builder1Inventory[resource] != 0 || builder2Inventory[resource] != 0 || builder3Inventory[resource] != 0 || builder4Inventory[resource] != 0) {
                return true;
            }
        }
        return false;
    }

    // Overloaded subscript operator to index inventories by builderNumber
    std::unordered_map<Resource, int>& operator[](int i) {
        switch(i) {
            case 0: return builder1Inventory;
            case 1: return builder2Inventory;
            case 2: return builder3Inventory;
            case 3: return builder4Inventory;
            default: throw std::out_of_range("BuilderInventoryUpdate index out of range");
        }
    }

    // Overloaded += operator to combine BuilderInventoryUpdate objects
    BuilderInventoryUpdate& operator+=(const BuilderInventoryUpdate& rhs) {
        for (int i = 0; i < static_cast<int>(Resource::PARK); i++) {
            Resource resource = static_cast<Resource>(i);
            builder1Inventory[resource] += rhs.builder1Inventory.at(resource);
            builder2Inventory[resource] += rhs.builder2Inventory.at(resource);
            builder3Inventory[resource] += rhs.builder3Inventory.at(resource);
            builder4Inventory[resource] += rhs.builder4Inventory.at(resource);
        }
        return *this;
    }
};

#endif
