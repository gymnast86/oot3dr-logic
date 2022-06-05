
#pragma once

#include "requirement.hpp"
#include "area_id.hpp"
#include <memory>

class World;
class Area;
class Entrance {
public:

    Entrance();
    Entrance(const AreaID& parentArea_, const AreaID& connectedArea_, const RequirementFn& requirement_, World* world_);
    ~Entrance();

    AreaID GetParentAreaID() const;
    Area* GetParentArea() const;
    AreaID GetConnectedAreaID() const;
    Area* GetConnectedArea() const;
    std::string GetOriginalName() const;
    const RequirementFn& GetRequirement() const;
    World* GetWorld() const;

    bool IsShuffled() const;

    AreaID parentArea = AreaID::INVALID;
    AreaID connectedArea = AreaID::INVALID;
    std::string originalName = "";
    RequirementFn requirement = []{return false;};
    World* world = nullptr;
    bool shuffled = false;
};
