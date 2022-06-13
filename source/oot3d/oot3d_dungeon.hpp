#pragma once

#include "oot3d_item.hpp"
#include "oot3d_location.hpp"

class Oot3dDungeon {
public:

    Oot3dDungeon();
    Oot3dDungeon(const std::string& name);
    ~Oot3dDungeon();

    std::string name = "";
    ItemID map = ItemID::NONE;
    ItemID compass = ItemID::NONE;
    ItemID smallKey = ItemID::NONE;
    ItemID smallKeyRing = ItemID::NONE;
    ItemID bossKey = ItemID::NONE;
    std::unordered_set<Location*> vanillaLocations = {};
    std::unordered_set<Location*> mqLocations = {};
    std::unordered_set<Location*> sharedLocations = {};

};
