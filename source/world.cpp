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

void World::PlaceItemAtLocation(const LocationID& locationId, const Item& item)
{
    if (locations.count(locationId) == 0)
    {
        std::cout << "ERROR: Location \"" << LocationIDToName(locationId) << "\" is not a part of world " << std::to_string(worldId + 1) << " of type " << GetTypeString() << std::endl;
        return;
    }
    locations[locationId]->SetCurrentItem(item);
}

void World::PlaceItemAtLocation(const std::string& locationName, const std::string& itemName)
{
    auto locationId = NameToLocationID(locationName);
    auto itemId = NameToItemID(itemName);
    if (locationId == LocationID::INVALID)
    {
        std::cout << "ERROR: Unknown location \"" << locationName << "\"" << std::endl;
        return;
    }
    if (itemId == ItemID::INVALID)
    {
        std::cout << "ERROR: Unknown item \"" << itemName << "\"" << std::endl;
        return;
    }
    // Assume the item is for this world if it's a string
    Item item = Item(itemId, this);
    PlaceItemAtLocation(locationId, item);
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
