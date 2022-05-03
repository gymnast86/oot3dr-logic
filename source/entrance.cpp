#include "entrance.hpp"

Entrance::Entrance() {}

Entrance::Entrance(const AreaID& parentArea_, const AreaID& connectedArea_, Requirement& requirement_, World* world_) :
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

AreaID Entrance::GetConnectedAreaID() const
{
    return connectedArea;
}

std::string Entrance::GetOriginalName() const
{
    return originalName;
}

const Requirement& Entrance::GetRequirement() const
{
    return requirement;
}

World* Entrance::GetWorld() const
{
    return world;
}
