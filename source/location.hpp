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
    std::string GetName();
    std::string GetDungeon();
    World* GetWorld() const;
    Item GetCurrentItem() const;
    void SetCurrentItem(Item item);
    void SetVanillaItemAsCurrentItem();
    void RemoveCurrentItem();
    ItemID GetVanillaItemID() const;

    virtual std::string TypeString() const;

    bool operator==(const Location& rhs) const;
    bool operator<(const Location& rhs) const;

    LocationID id = LocationID::INVALID;
    std::string name = "";
    std::string dungeon = "None";
    World* world = nullptr;
    Item currentItem;
    ItemID vanillaItemId = ItemID::NONE;
    bool hasKnownVanillaItem = false;

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
