#pragma once

#include "item_id.hpp"

class World;
class Item {
public:

    Item();
    Item(const ItemID& id_, World* world_);
    ~Item();

    ItemID GetID() const;
    std::string GetName();
    World* GetWorld() const;
    int GetWorldID() const;
    void SetAsMajorItem();
    bool IsMajorItem() const;

    bool operator==(const Item& rhs) const;
    bool operator<(const Item& rhs) const;

    ItemID id = ItemID::NONE;
    std::string name = "";
    World* world = nullptr;
    int worldId = -1;
    bool isMajorItem;
};

// inject specialization of std::hash<Item> into the std namespace
// taken from: https://en.cppreference.com/w/cpp/utility/hash
template<>
struct std::hash<Item>
{
    size_t operator()(Item const& i) const noexcept
    {
        size_t h1 = std::hash<ItemID>{}(i.GetID());
        size_t h2 = std::hash<int>{}(i.GetWorldID());
        return h1 ^ (h2 << 16);
    }
};

// Template comparator for sets of pointers to be sorted by their data instead of the pointer address.
// Taken from stack overflow https://stackoverflow.com/questions/67620937/set-of-pointers-to-objects-with-custom-comparator
template <typename T>
struct PointerComparator
{
    bool operator()(const T * lhs, const T * rhs) const
    {
        return *lhs < *rhs;
    }
};
