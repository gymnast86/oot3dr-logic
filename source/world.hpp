#pragma once

#include "utility/debug.hpp"
#include "item.hpp"
#include "area.hpp"
#include "location.hpp"
#include "general_item_pool.hpp"

#include <string>
#include <list>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
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

enum class EvalSuccess
{
    NONE = 0,
    Partial,
    Complete,
    Unnecessary,
};

class World;
using WorldPool = std::vector<std::unique_ptr<World>>;

class Search;
class World {
public:

    World();
    World(SettingsMap& settings_, size_t numWorlds);

    virtual ~World();

    int GetWorldID() const;
    void SetWorldID(int newWorldId);
    WorldType GetType() const;
    const SettingsMap& GetSettings() const;
    Area* GetRootArea();
    size_t GetNumWorlds() const;
    void PlaceItemAtLocation(const LocationID& locationId, const Item& item);
    void PlaceItemAtLocation(const std::string& location, const std::string& item);

    virtual WorldBuildingError Build();
    virtual EvalSuccess EvaluateEventRequirement(Search* search, Event* exit);
    virtual EvalSuccess EvaluateLocationRequirement(Search* search, LocationAccess* locAccess);
    virtual EvalSuccess EvaluateExitRequirement(Search* search, Entrance* exit);
    virtual std::string GetTypeString() const;

    SettingsMap settings;
    std::map<LocationID, std::unique_ptr<Location>> locations;
    std::unordered_map<AreaID, std::unique_ptr<Area>> areas;
    LogicHelperMap logicHelpers;
    ItemPool itemPool;
    ItemPool startingItems;
    int worldId = -1;
    size_t numWorlds = -1;
    WorldType worldType = WorldType::NONE;

    // Store playthroughs in world 0 for now
    std::list<std::set<Location*, PointerComparator<Location>>> playthroughSpheres = {};
    std::list<std::list<Entrance*>> entranceSpheres = {};
};
