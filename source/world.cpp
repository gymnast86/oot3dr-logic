#include "world.hpp"
#include "search.hpp"

#include <iostream>

World::World() {}

World::World(SettingsMap& settings_) : settings(std::move(settings_)) {}

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
