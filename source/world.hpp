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
    BAD_AREA_VALUE,
    LOCATION_NOT_DEFINED,
};

enum class WorldType
{
    NONE = 0,
    Oot3d,
    Mm3d,
};

enum class EvaluateType
{
    NONE,
    Event,
    Location,
    Exit,
};

class World;
using WorldPool = std::vector<std::unique_ptr<World>>;

class Search;
class World {
public:

    World();
    World(SettingsMap& settings_);

    virtual ~World();

    int GetWorldID() const;
    void SetWorldID(int newWorldId);
    WorldType GetType() const;
    const SettingsMap& GetSettings() const;
    Area* GetRootArea();

    virtual WorldBuildingError Build();
    // object is a pointer to the object the requirement belongs to (event, location, or exit)
    virtual bool EvaluateRequirement(const Requirement& req, Search* search, void* object, EvaluateType evalType = EvaluateType::NONE);
    virtual std::string GetTypeString() const;

    SettingsMap settings;
    std::unordered_map<LocationID, std::unique_ptr<Location>> locations;
    std::unordered_map<AreaID, std::unique_ptr<Area>> areas;
    LogicHelperMap logicHelpers;
    ItemPool itemPool;
    ItemPool startingItems;
    int worldId = -1;
    WorldType worldType = WorldType::NONE;

    int numEvals = 0;
};

int TotalWorldEvals(const WorldPool& worlds);
