#include "entrance.hpp"
#include "world.hpp"

Entrance::Entrance() {}

Entrance::Entrance(const AreaID& parentArea_, const AreaID& connectedArea_, const RequirementFn& requirement_, World* world_) :
    parentArea(parentArea_),
    connectedArea(connectedArea_),
    requirement(requirement_),
    world(world_)
    {
        originalName = AreaIDToName(parentArea) + " -> " + AreaIDToName(connectedArea);
    }

Entrance::~Entrance() = default;

AreaID Entrance::GetParentAreaID() const
{
    return parentArea;
}

Area* Entrance::GetParentArea() const
{
    return world->areas[parentArea].get();
}

AreaID Entrance::GetConnectedAreaID() const
{
    return connectedArea;
}

Area* Entrance::GetConnectedArea() const
{
    return world->areas[connectedArea].get();
}

std::string Entrance::GetOriginalName() const
{
    return originalName;
}

const RequirementFn& Entrance::GetRequirement() const
{
    return requirement;
}

World* Entrance::GetWorld() const
{
    return world;
}

bool Entrance::IsShuffled() const
{
    return shuffled;
}
