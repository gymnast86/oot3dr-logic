#include "world.hpp"
#include "search.hpp"

#include <iostream>

World::World() {}

World::World(SettingsMap& settings_, size_t numWorlds_) : settings(std::move(settings_)), numWorlds(numWorlds_) {}

World::~World() = default;

int World::GetWorldID() const
{
    return worldId;
}

void World::SetWorldID(int newWorldId)
{
    worldId = newWorldId;
}

WorldType World::GetType() const
{
    return worldType;
}

const SettingsMap& World::GetSettings() const
{
    return settings;
}

Area* World::GetRootArea()
{
    return areas[AreaID::Root].get();
}

size_t World::GetNumWorlds() const
{
    return numWorlds;
}

size_t World::GetNumWorldTypes() const
{
    return numWorldTypes;
}

WorldBuildingError World::PlaceItemAtLocation(const LocationID& locationId, const Item& item)
{
    if (locations.count(locationId) == 0)
    {
        LOG_TO_ERROR("ERROR: Location \"" + LocationIDToName(locationId) + "\" is not a part of world " + std::to_string(worldId + 1) + " of type " + GetTypeString());
        return WorldBuildingError::LOCATION_NOT_IN_WORLD;
    }
    locations[locationId]->SetCurrentItem(item);
    return WorldBuildingError::NONE;
}

WorldBuildingError World::PlaceItemAtLocation(const std::string& locationName, const ItemID& itemId)
{
    WorldBuildingError err;
    auto locationId = NameToLocationID(GetTypeString() + " " + locationName);
    if (locationId == LocationID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown location \"" + locationName + "\"");
        return WorldBuildingError::BAD_LOCATION_NAME;
    }
    // Assume the item is for this world if it's a string
    Item item = Item(itemId, this);
    BUILD_ERROR_CHECK(PlaceItemAtLocation(locationId, item));
    return WorldBuildingError::NONE;
}

WorldBuildingError World::SetLocationAsVanilla(const std::string& locationName)
{
    auto locationId = NameToLocationID(GetTypeString() + " " + locationName);
    if (locationId == LocationID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown location \"" + locationName + "\"");
        return WorldBuildingError::BAD_LOCATION_NAME;
    }
    locations[locationId]->SetVanillaItemAsCurrentItem();
    return WorldBuildingError::NONE;
}

LocationPool World::GetAllItemLocations()
{
    return GetTheseLocations([](Location* loc){return true;});
}

WorldBuildingError World::Build()
{
    std::cout << "Building generic world. Something is probably wrong." << std::endl;
    return WorldBuildingError::NONE;
}

EvalSuccess World::EvaluateEventRequirement(Search* search, Event* event)
{
    std::cout << "Called Generic world evaluate event requirement. Something is probably wrong." << std::endl;
    return EvalSuccess::NONE;
}

EvalSuccess World::EvaluateLocationRequirement(Search* search, LocationAccess* locAccess)
{
    std::cout << "Called Generic world evaluate event requirement. Something is probably wrong." << std::endl;
    return EvalSuccess::NONE;
}

EvalSuccess World::EvaluateExitRequirement(Search* search, Entrance* exit)
{
    std::cout << "Called Generic world evaluate event requirement. Something is probably wrong." << std::endl;
    return EvalSuccess::NONE;
}

std::string World::GetTypeString() const
{
    return "generic (something is probably wrong)";
}
