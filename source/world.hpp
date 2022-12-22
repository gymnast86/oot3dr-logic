#pragma once

#include "item.hpp"
#include "area.hpp"
#include "dungeon.hpp"
#include "location.hpp"
#include "general_item_pool.hpp"
#include "utility/log.hpp"

#include <string>
#include <list>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>

#define BUILD_ERROR_CHECK(func) err = func; if (err != WorldBuildingError::NONE) {return err;}

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
    BAD_ITEM_NAME,
    BAD_LOCATION_NAME,
    LOCATION_NOT_IN_WORLD,
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
    size_t GetNumWorldTypes() const;
    WorldBuildingError PlaceItemAtLocation(const LocationID& locationId, const Item& item);
    WorldBuildingError PlaceItemAtLocation(const std::string& location, const std::string& item);
    WorldBuildingError SetLocationAsVanilla(const std::string& location);
    WorldBuildingError SetLocationsWithVanillaItem(const std::string& itemName);
    LocationPool GetAllItemLocations();

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
    ItemPool startingInventory;
    int worldId = -1;
    size_t numWorlds = 1;
    size_t numWorldTypes = 1;
    WorldType worldType = WorldType::NONE;

    // Store playthroughs in world 0 for now
    std::list<std::set<Location*, PointerComparator<Location>>> playthroughSpheres = {};
    std::list<std::list<Entrance*>> entranceSpheres = {};

    // Takes a lambda function meant to evaluate locations to set as vanilla
    // based on arbitrary criteria
    template<typename Lambda>
    void SetTheseLocationsAsVanilla(Lambda locationCriteria)
    {
        for (auto& [id, loc] : locations)
        {
            if (locationCriteria(loc.get()))
            {
                loc->SetVanillaItemAsCurrentItem();
            }
        }
    }

    // Takes a lambda function which filters which locations to get based on
    // arbitrary criteria
    template<typename Lambda>
    LocationPool GetTheseLocations(Lambda locationCriteria, const bool& onlyItemLocations = true)
    {
        LocationPool pool = {};
        for (auto& [id, loc] : locations)
        {
            if (locationCriteria(loc.get()) && (loc->IsItemLocation() || !onlyItemLocations))
            {
                pool.push_back(loc.get());
            }
        }
        return pool;
    }
};
