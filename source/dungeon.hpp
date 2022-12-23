#pragma once

#include "item.hpp"
#include "location.hpp"

#include <list>

class Dungeon {
public:
    Dungeon();
    virtual ~Dungeon();

    void SetBossKeyItemID(const ItemID& itemId);
    ItemID GetBossKeyItemID() const;
    void SetSmallKeyItemID(const ItemID& itemId);
    ItemID GetSmallKeyItemID() const;
    void SetSmallKeyCount(const int& keyCount_);
    virtual int GetSmallKeyCount() const;
    void SetMapItemID(const ItemID& itemId);
    ItemID GetMapItemID() const;
    void SetCompassItemID(const ItemID& itemId);
    ItemID GetCompassItemID() const;
    void AddLocation(Location* loc);

    int keyCount = -1;
    ItemID smallKey = NONE;
    ItemID bossKey = NONE;
    ItemID map = NONE;
    ItemID compass = NONE;
    std::list<Location*> locations = {};
    std::list<Location*> outsideDependentLocations = {}; // Locations which depend on beating the dungeon
    // std::string name = "";
};
