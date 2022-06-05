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

bool World::EvaluateRequirement(const RequirementFn& req, Search* search, void* object, EvaluateType evalType /*= EvaluateType::NONE*/)
{
    std::cout << "Called Generic world evaluate requirement. Something is probably wrong." << std::endl;
    return false;
}

void World::ExpandAreaVariables()
{
    std::cout << "Called Generic world expand avriables. Something is probably wrong." << std::endl;
}

std::string World::GetTypeString() const
{
    return "generic (something is probably wrong)";
}

int TotalWorldEvals(const WorldPool& worlds)
{
    int sum = 0;
    for (const auto& world : worlds)
    {
        sum += world->numEvals;
    }
    return sum;
}

double TotalWorldEvalTime(const WorldPool& worlds)
{
    double sum = 0;
    for (const auto& world : worlds)
    {
        sum += world->evalTiming;
    }
    return sum;
}
