#include "world.hpp"

#include <iostream>

World::World() {}

World::World(SettingsMap settings_) : settings(std::move(settings_)) {}

World::~World() = default;

int World::GetWorldID() const
{
    return worldId;
}

void World::SetWorldID(int newWorldId)
{
    worldId = newWorldId;
}

const SettingsMap& World::GetSettings() const
{
    return settings;
}

WorldBuildingError World::Build()
{
    std::cout << "Building generic world. Something is probably wrong." << std::endl;
    return WorldBuildingError::NONE;
}
