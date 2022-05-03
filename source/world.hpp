#pragma once

#include "debug.hpp"
#include "item.hpp"
#include "area.hpp"
#include "location.hpp"
#include "general_item_pool.hpp"

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <memory>

enum struct WorldBuildingError
{
    NONE = 0,
    BAD_REQUIREMENT,
    COULD_NOT_LOAD_FILE,
    MISSING_ITEM_FIELD,
    MISSING_LOCATION_FIELD,
    BAD_ITEM_VALUE,
    BAD_LOCATION_VALUE,
};

class World;
using WorldPool = std::vector<std::unique_ptr<World>>;

class World {
public:

    World();
    World(SettingsMap settings_);

    virtual ~World();

    int GetWorldID() const;
    void SetWorldID(int newWorldId);
    const SettingsMap& GetSettings() const;

    virtual WorldBuildingError Build();

    SettingsMap settings;
    std::unordered_map<LocationID, Location> locations;
    std::unordered_map<AreaID, Area> areas;
    LogicHelperMap logicHelpers;
    ItemPool itemPool;
    ItemPool startingItems;
    int worldId = -1;
};
