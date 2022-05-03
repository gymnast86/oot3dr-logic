
#pragma once

#include "requirement.hpp"
#include "area_id.hpp"

class World;
class Entrance {
public:

    Entrance();
    Entrance(const AreaID& parentArea_, const AreaID& connectedArea_, Requirement& requirement_, World* world_);
    ~Entrance();

    AreaID GetParentAreaID() const;
    AreaID GetConnectedAreaID() const;
    std::string GetOriginalName() const;
    const Requirement& GetRequirement() const;
    World* GetWorld() const;

private:
    AreaID parentArea = AreaID::INVALID;
    AreaID connectedArea = AreaID::INVALID;
    std::string originalName = "";
    Requirement requirement = {RequirementType::FALSE, {}};
    World* world = nullptr;
};
