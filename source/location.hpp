#pragma once

#include "location_id.hpp"
#include "item.hpp"

#include <memory>
#include <vector>
#include <unordered_set>

class World;
class Area;
class Location {
public:

    Location();
    Location(const LocationID& id_, std::string name_, World* world_);
    ~Location();

    LocationID GetID() const;
    std::string GetName() const;
    World* GetWorld() const;
    Item GetCurrentItem() const;

    virtual std::string TypeString() const;

    LocationID id = LocationID::INVALID;
    std::string name = "";
    World* world = nullptr;
    Item currentItem;

};

// inject specialization of std::hash<LocationID> into the std namespace
// taken from: https://en.cppreference.com/w/cpp/utility/hash
template<>
struct std::hash<LocationID>
{
    std::size_t operator()(LocationID const& locationId) const noexcept
    {
        return static_cast<std::underlying_type<LocationID>::type>(locationId);
    }
};

using LocationPool = std::vector<Location*>;
using LocationSet = std::unordered_set<Location*>;
