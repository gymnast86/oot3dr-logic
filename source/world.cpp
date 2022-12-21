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
    auto locationId = NameToLocationID(GetTypeString() + " " + locationName);
    auto itemId = NameToItemID(GetTypeString() + " " + itemName);
    if (locationId == LocationID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown location \"" + locationName + "\"");
        return;
    }
    if (itemId == ItemID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown item \"" + itemName + "\"");
        return;
    }
    // Assume the item is for this world if it's a string
    Item item = Item(itemId, this);
    PlaceItemAtLocation(locationId, item);
}

void World::SetLocationAsVanilla(const std::string& locationName)
{
    auto locationId = NameToLocationID(GetTypeString() + " " + locationName);
    if (locationId == LocationID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown location \"" + locationName + "\"");
        return;
    }
    locations[locationId]->SetVanillaItemAsCurrentItem();
}

void World::SetLocationsWithVanillaItem(const std::string& itemName)
{
    auto itemId = NameToItemID(GetTypeString() + " " + itemName);
    if (itemId == ItemID::INVALID)
    {
        LOG_TO_ERROR("ERROR: Unknown item \"" + itemName + "\"");
        return;
    }
    for (auto& [id, location] : locations)
    {
        if (location->GetVanillaItemID() == itemId)
        {
            location->SetVanillaItemAsCurrentItem();
        }
    }
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
